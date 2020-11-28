// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSHUD.h"
#include "Math/Color.h"
#include "FPSCharacter.h"
#include "Weapon.h"
#include "Fonts/SlateFontInfo.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();
    if (CrosshairTexture)
    {
        // Find the center of our canvas.
        FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);

        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
    ACharacter* mainPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (mainPlayer) {
        AFPSCharacter* mainPl = Cast<AFPSCharacter>(mainPlayer);
        int AmmunitionTotal = mainPl->EquippedItem->AmmunitionTotal;
        DrawText(FString::SanitizeFloat(AmmunitionTotal), FontColor, PositionXAmmunitionTotal, PositionYAmmunitionTotal, GEngine->GetSmallFont(), FontSizeAmmunitionTotal, bScalePosition);
        int AmmunitionMagazine = mainPl->EquippedItem->AmmunitionMagazine;
        DrawText(FString::SanitizeFloat(AmmunitionMagazine), FontColor, PositionXAmmunitionMagazine, PositionYAmmunitionMagazine, GEngine->GetSmallFont(), FontSizeAmmunitionMagazine, bScalePosition);
    }

    
}
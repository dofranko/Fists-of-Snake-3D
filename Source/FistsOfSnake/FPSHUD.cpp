// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSHUD.h"
#include "Math/Color.h"
#include "FPSCharacter.h"
#include "Weapon.h"
#include "Grenade.h"
#include "Fonts/SlateFontInfo.h"

void AFPSHUD::DrawHUD()
{
    Super::DrawHUD();
    // Find the center of our canvas.
    FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
    if (CrosshairTexture)
    {
        // Offset by half of the texture's dimensions so that the center of the texture aligns with the center of the Canvas.
        FVector2D CrossHairDrawPosition(Center.X - (CrosshairTexture->GetSurfaceWidth() * 0.5f), Center.Y - (CrosshairTexture->GetSurfaceHeight() * 0.5f));

        // Draw the crosshair at the centerpoint.
        FCanvasTileItem TileItem(CrossHairDrawPosition, CrosshairTexture->Resource, FLinearColor::White);
        TileItem.BlendMode = SE_BLEND_Translucent;
        Canvas->DrawItem(TileItem);
    }
    ACharacter *mainPlayer = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (mainPlayer)
    {
        AFPSCharacter *mainFpsPlayer = Cast<AFPSCharacter>(mainPlayer);
        if (mainFpsPlayer)
        {
            AWeapon *playerWeapon = Cast<AWeapon>(mainFpsPlayer->EquippedItem);
            if (playerWeapon)
            {
                int AmmunitionTotal = playerWeapon->AmmunitionTotal;
                DrawText(FString::FromInt(AmmunitionTotal), FontColor, PositionAmmunitionTotal.X, PositionAmmunitionTotal.Y, GEngine->GetSmallFont(), FontSizeAmmunitionTotal, bScalePosition);
                int AmmunitionMagazine = playerWeapon->AmmunitionMagazine;
                DrawText(FString::FromInt(AmmunitionMagazine), FontColor, PositionAmmunitionMagazine.X, PositionAmmunitionMagazine.Y, GEngine->GetSmallFont(), FontSizeAmmunitionMagazine, bScalePosition);
            }

            int playerHealth = mainFpsPlayer->GetHealth();
            if (playerHealth)
            {
                DrawText(FString::FromInt(playerHealth), FontColor, PositionHealth.X, PositionHealth.Y, GEngine->GetSmallFont(), FontSizeHealth, bScalePosition);
            }

            AGrenade *PlayerGrenade = Cast<AGrenade>(mainFpsPlayer->EquippedItem);
            if (PlayerGrenade)
            {
                int NumberOfGrenades = PlayerGrenade->NumberOfGrenades;
                DrawText(FString::FromInt(NumberOfGrenades), FontColor, PositionAmmunitionTotal.X, PositionAmmunitionTotal.Y, GEngine->GetSmallFont(), FontSizeAmmunitionTotal, bScalePosition);
            }

            // Draw slots of the inventory
            for (int i = 0; i < 5; i++)
            {
                FVector2D SlotPosition(PositionInventory.X, PositionInventory.Y - 60.0f * i);
                FCanvasTileItem TileItem(SlotPosition, FVector2D(50.0f, 50.0f), FLinearColor(0.0f, 0.0f, 0.0f, 0.5f));
                TileItem.BlendMode = SE_BLEND_Translucent;
                Canvas->DrawItem(TileItem);
                UTexture2D *ItemIcon = mainFpsPlayer->MyInventory->GetItemIcon(i);
                if (ItemIcon)
                {
                    FCanvasTileItem IconItem(SlotPosition, ItemIcon->Resource, FLinearColor(1.f, 1.f, 1.f, 1.f));
                    IconItem.BlendMode = SE_BLEND_Translucent;
                    Canvas->DrawItem(IconItem);
                }
                
            }
        }
    }
}
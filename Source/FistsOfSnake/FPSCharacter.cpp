// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "Weapon.h"
#include "Item.h"
#include "Inventory.h"

// Sets default values
AFPSCharacter::AFPSCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	check(FPSCameraComponent != nullptr);

	// Attach the camera component to our capsule component.
	FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	FPSMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
	check(FPSMesh != nullptr);

	// Only the owning player sees this mesh.
	FPSMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	FPSMesh->SetupAttachment(FPSCameraComponent);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	FPSMesh->bCastDynamicShadow = false;
	FPSMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	// Create player's inventory
	this->MyInventory = new Inventory();
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);

	// Display a debug message for five seconds.
	// The -1 "Key" value argument prevents the message from being updated or refreshed.
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("We are using FPSCharacter."));

	// Create an elementery weapon for player
	UWorld *World = GetWorld();
	if (World)
	{
		const TCHAR *SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4");
		TArray<UObject *> Array;
		EngineUtils::FindOrLoadAssetsByPath(SkeletalPath, Array, EngineUtils::ATL_Regular);
		USkeletalMesh *SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
		FVector SpawnLocation = this->GetActorLocation() + FVector(-140.0f, -30.0f, 90.0f);
		FRotator Rotation = this->GetActorRotation() + FRotator(0.0f, -90.0f, 0.0f);
		this->EquippedItem = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, Rotation);
		this->EquippedItem->SetActorTickEnabled(false);
		this->EquippedItem->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
		this->EquippedItem->SkeletalMesh->AttachToComponent(FPSCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
		this->EquippedItem->Players.Add(this); // in the future -> ArrayOfPlayers
		this->EquippedItem->ItemName = FString(TEXT("AR4"));
		TArray<UObject*> Array2;
		EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Icons") , Array2, EngineUtils::ATL_Regular);
		UTexture2D* texture = Cast<UTexture2D>(Array2[1]);
		this->EquippedItem->ItemIcon = texture;
		this->EquippedItemIndex = 0;
		this->MyInventory->AddItem(this->EquippedItem);
	}
	Health = 100;
	bAlive = true;
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFPSCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFPSCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFPSCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPSCharacter::AddControllerPitchInput);

	// Set up "Fire" binding
	PlayerInputComponent->BindAction("UseItem", IE_Pressed, this, &AFPSCharacter::UseItem);

	// Set up "action" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFPSCharacter::PlayerJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPSCharacter::PlayerJump);

	// Set up "PickUp" binding.
	PlayerInputComponent->BindAction("PickUp", IE_Pressed, this, &AFPSCharacter::SetWantToPickUp);
	PlayerInputComponent->BindAction("PickUp", IE_Released, this, &AFPSCharacter::SetWantToPickUp);

	// Set up "ThrowItem" binding.
	PlayerInputComponent->BindAction("ThrowItem", IE_Pressed, this, &AFPSCharacter::ThrowItem);

	// Set up "ChooseItem" binding.
	// To invoke ChooseItem with parameter in BindAction<>()
	DECLARE_DELEGATE_OneParam(FCustomInputDelegate, int);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ChooseItem1", IE_Pressed, this, &AFPSCharacter::ChooseItem, 0);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ChooseItem2", IE_Pressed, this, &AFPSCharacter::ChooseItem, 1);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ChooseItem3", IE_Pressed, this, &AFPSCharacter::ChooseItem, 2);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ChooseItem4", IE_Pressed, this, &AFPSCharacter::ChooseItem, 3);
	PlayerInputComponent->BindAction<FCustomInputDelegate>("ChooseItem5", IE_Pressed, this, &AFPSCharacter::ChooseItem, 4);

	// Set up "Reload" binding.
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPSCharacter::Reload);
}

void AFPSCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFPSCharacter::UseItem()
{
	check(GEngine != nullptr);
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Using Item"));
	// Attempt to fire a projectile.
	if (EquippedItem)
	{
		// Get the camera transform.
		FVector CameraLocation;
		FRotator CameraRotation;
		GetActorEyesViewPoint(CameraLocation, CameraRotation);

		// Set MuzzleOffset to spawn projectiles slightly in front of the camera.
		MuzzleOffset.Set(120.0f, 0.0f, 45.0f);

		// Transform MuzzleOffset from camera space to world space.
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

		// Skew the aim to be slightly upwards.
		FRotator MuzzleRotation = CameraRotation;

		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		SpawnParams.Instigator = GetInstigator();
		this->EquippedItem->Use(MuzzleLocation, MuzzleRotation, SpawnParams);
	}
}

void AFPSCharacter::PlayerJump()
{
	this->bPressedJump = !this->bPressedJump;
}

void AFPSCharacter::SetWantToPickUp()
{
	this->bWantToPickUp = !this->bWantToPickUp;
}

void AFPSCharacter::ThrowItem()
{
	if (this->EquippedItem)
	{
		this->MyInventory->RemoveItem(this->EquippedItemIndex);
		this->EquippedItem->ThrowMe(this);
		this->EquippedItem = nullptr;
		this->EquippedItemIndex = -1;
	}
}

void AFPSCharacter::ChooseItem(int Index)
{
	if (Index == this->EquippedItemIndex)		// not to change the same item
		return;
	if (EquippedItem)
	{
		this->EquippedItem->SkeletalMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		this->EquippedItem->SetActorHiddenInGame(true);
		this->EquippedItemIndex = -1;
	}
	this->EquippedItem = this->MyInventory->GetItem(Index);
	if (EquippedItem)
	{
		this->EquippedItemIndex = Index;
		FVector CameraLocation;
		FRotator CameraRotation;
		this->GetActorEyesViewPoint(CameraLocation, CameraRotation);
		FVector OffSet;
		OffSet.Set(120.0f, 30.0f, 30.0f);
		FVector Location = CameraLocation + FTransform(CameraRotation).TransformVector(OffSet);
		FRotator Rotation = this->GetActorRotation() + FRotator(0.0f, -90.0f, 10.0f);
		this->EquippedItem->SetActorLocation(Location);
		this->EquippedItem->SetActorRotation(Rotation);
		this->EquippedItem->SetActorHiddenInGame(false);
		this->EquippedItem->SkeletalMesh->AttachToComponent(this->FPSCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AFPSCharacter::Reload()
{
	this->EquippedItem->Reload();
}

void AFPSCharacter::DamageMe(int damage)
{
	if (Health > 0) {
		Health -= damage;
	}
	if (Health > 100)
		Health = 100;
	if (Health <= 0) {
		bAlive = false;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Yellow, TEXT("Im dead"));
		Destroy();

	}
}

int AFPSCharacter::GetHealth() {
	return this->Health;
}


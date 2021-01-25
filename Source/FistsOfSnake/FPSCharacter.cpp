// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include <Runtime\Engine\Public\EngineUtils.h>
#include "Weapon.h"
#include "Item.h"
#include "Inventory.h"
#include "Grenade.h"
#include "Net/UnrealNetwork.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include <FistsOfSnake/FoSPlayerState.h>

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

	// Player's health
	MaxHealth = 100.0f;
	CurrentHealth = MaxHealth;
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine != nullptr);


	// Create an elementery weapon for player
	UWorld *World = GetWorld();
	if (World)
	{
		// Iterate through player's CameraManager (multiplayer)
		for (FConstPlayerControllerIterator Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			APlayerController *PlayerController = Iter->Get();

			if (PlayerController && PlayerController->IsLocalPlayerController())
			{
				this->ManagerCamera = Cast<APlayerCameraManager>(PlayerController->PlayerCameraManager);
			}
		}
	}

	bAlive = true;
	
	if (IsLocallyControlled())
	{
		// Display a debug message for five seconds.
		// The -1 "Key" value argument prevents the message from being updated or refreshed.
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("Nowy gracz dołącza do serwera"));
	}
}

void AFPSCharacter::SpawnFirstWeapon_Implementation()
{
	UWorld *World = GetWorld();
	const TCHAR *SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4");
	TArray<UObject *> Array;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath, Array, EngineUtils::ATL_Regular);
	USkeletalMesh *SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
	FVector SpawnLocation = this->FPSCameraComponent->GetComponentLocation() + FVector(-120.0f, -30.0f, 85.0f);
	FRotator Rotation = this->FPSCameraComponent->GetComponentRotation() + FRotator(0.0f, -90.0f, 0.0f);
	this->EquippedItem = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, Rotation);
	this->EquippedItem->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
	this->EquippedItem->SetActorTickEnabled(false);
	this->EquippedItem->Players.Add(this); // in the future -> ArrayOfPlayers
	this->EquippedItem->ItemName = FString(TEXT("AR4"));
	this->EquippedItem->SetOwner(this);
	TArray<UObject *> Array2;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Icons"), Array2, EngineUtils::ATL_Regular);
	UTexture2D *texture = Cast<UTexture2D>(Array2[2]);
	this->EquippedItem->ItemIcon = texture;
	this->EquippedItemIndex = 0;
	this->MyInventory->AddItem(this->EquippedItem);
	///

	const TCHAR* SkeletalPath2 = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47");
	TArray<UObject*> Array3;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath2, Array3, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh2 = Cast<USkeletalMesh>(Array3[0]);
	this->EquippedItem = World->SpawnActor<AWeapon>(AWeapon::StaticClass(), SpawnLocation, Rotation);
	this->EquippedItem->SkeletalMesh->SetSkeletalMesh(SkeletalMesh2);
	this->EquippedItem->SetActorTickEnabled(false);
	this->EquippedItem->Players.Add(this); // in the future -> ArrayOfPlayers
	this->EquippedItem->ItemName = FString(TEXT("Ka47"));
	this->EquippedItem->SetOwner(this);
	TArray<UObject*> Array4;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Icons"), Array4, EngineUtils::ATL_Regular);
	texture = Cast<UTexture2D>(Array2[1]);
	this->EquippedItem->ItemIcon = texture;
	this->EquippedItemIndex = 1;
	this->MyInventory->AddItem(this->EquippedItem);

	//

	const TCHAR* SkeletalPath3 = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade");
	TArray<UObject*> Array5;
	EngineUtils::FindOrLoadAssetsByPath(SkeletalPath3, Array5, EngineUtils::ATL_Regular);
	USkeletalMesh* SkeletalMesh3 = Cast<USkeletalMesh>(Array5[0]);
	this->EquippedItem = World->SpawnActor<AGrenade>(AGrenade::StaticClass(), SpawnLocation, Rotation);
	this->EquippedItem->SkeletalMesh->SetSkeletalMesh(SkeletalMesh3);
	this->EquippedItem->SetActorTickEnabled(false);
	this->EquippedItem->Players.Add(this); // in the future -> ArrayOfPlayers
	this->EquippedItem->ItemName = FString(TEXT("G67"));
	this->EquippedItem->SetOwner(this);
	TArray<UObject*> Array6;
	EngineUtils::FindOrLoadAssetsByPath(TEXT("/Game/FPS_Weapon_Bundle/Icons"), Array6, EngineUtils::ATL_Regular);
	texture = Cast<UTexture2D>(Array6[0]);
	this->EquippedItem->ItemIcon = texture;
	this->EquippedItemIndex = 0;
	this->MyInventory->AddItem(this->EquippedItem);


	ChooseItem(4);
	ChooseItem(0);
	OnRep_WeaponSwitch();
}

void AFPSCharacter::OnRep_WeaponSwitch()
{
	if (EquippedItem)
	{
		UWorld *World = GetWorld();
		const TCHAR *SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/AR4");
		if (EquippedItem->ItemName.Equals(FString(TEXT("Ka47")))) {
			SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/Ka47");
		}
		else if (EquippedItem->ItemName.Equals(FString(TEXT("G67")))) {
			SkeletalPath = TEXT("/Game/FPS_Weapon_Bundle/Weapons/Meshes/G67_Grenade");
		}
		TArray<UObject *> Array;
		EngineUtils::FindOrLoadAssetsByPath(SkeletalPath, Array, EngineUtils::ATL_Regular);
		USkeletalMesh *SkeletalMesh = Cast<USkeletalMesh>(Array[0]);
		this->EquippedItem->SetActorTickEnabled(false);
		this->EquippedItem->SkeletalMesh->SetSkeletalMesh(SkeletalMesh);
		this->EquippedItem->SkeletalMesh->AttachToComponent(FPSCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
		this->EquippedItem->SkeletalMesh->SetIsReplicated(true);
	}
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

void AFPSCharacter::UseItem_Implementation()
{
	if (this->MyInventory->GetItem(0)==nullptr)
		SpawnFirstWeapon();
	check(GEngine != nullptr);
	// Attempt to fire a projectile.
	if (EquippedItem == nullptr)
		return;
	FVector muzzleLocation = this->FPSCameraComponent->GetComponentLocation();
	FRotator muzzleRotation = this->FPSCameraComponent->GetComponentRotation();
	FVector OffSet(120.0f, 0,0);
	muzzleLocation = FTransform(muzzleRotation, muzzleLocation).TransformPosition(OffSet);
	FActorSpawnParameters spawnParameters;
	spawnParameters.Owner = this;
	this->EquippedItem->Use(muzzleLocation, muzzleRotation);
	if (!this->EquippedItem->bAlive)
	{
		this->MyInventory->RemoveItem(this->EquippedItemIndex);
		this->EquippedItem = nullptr;
		this->EquippedItemIndex = -1;
	}
}

void AFPSCharacter::PlayerJump()
{
	this->bPressedJump = !this->bPressedJump;
}

void AFPSCharacter::SetWantToPickUp()
{
	if (this->bHasCollisionWithItem)
		this->bWantToPickUp = true;
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
	EquipItem(Index);
}

void AFPSCharacter::EquipItem_Implementation(int Index)
{
	if (false) {
		FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString());
	}
	if (Index == this->EquippedItemIndex) // not to change the same item
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
		FVector CameraLocation = this->FPSCameraComponent->GetComponentLocation();
		FRotator CameraRotation = this->FPSCameraComponent->GetComponentRotation();
		FVector OffSet(120.0f, 30.0f, -30.0f);
		FRotator OffSet2(0.0f, -90.0f, 0.0f);
		FVector Location = FTransform(CameraRotation, CameraLocation).TransformPosition(OffSet);
		FQuat Rotation = FTransform(CameraRotation).TransformRotation(OffSet2.Quaternion());
		this->EquippedItem->SetActorLocation(Location);
		this->EquippedItem->SetActorRotation(Rotation);
		this->EquippedItem->SetActorHiddenInGame(false);
		this->EquippedItem->SkeletalMesh->AttachToComponent(this->FPSCameraComponent, FAttachmentTransformRules::KeepWorldTransform);
	}
}

void AFPSCharacter::Reload_Implementation()
{
	if (EquippedItem)
	{
		AWeapon *weapon = Cast<AWeapon>(this->EquippedItem);
		if (weapon)
			weapon->StartReloading();
	}
}

void AFPSCharacter::DamageMe(int damage)
{
}

float AFPSCharacter::GetHealth()
{
	return this->CurrentHealth;
}

//////////////////////////////////////////////////////////////////////////
// Replicated Properties

void AFPSCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> &OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//Replicate current health.
	DOREPLIFETIME(AFPSCharacter, CurrentHealth);
	DOREPLIFETIME(AFPSCharacter, EquippedItem);
}

void AFPSCharacter::OnHealthUpdate(AActor *DamageCauser)
{
	//Client-specific functionality
	if (IsLocallyControlled())
	{

		
	}

	//Server-specific functionality
	if (GetLocalRole() == ROLE_Authority && IsLocallyControlled())
	{
		//FString healthMessage = FString::Printf(TEXT("%s now has %f health remaining."), *GetFName().ToString(), CurrentHealth);
		//GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, healthMessage);

	}
	if (HasAuthority()) {
		if (CurrentHealth <= 0)
		{
			if (AFoSPlayerState *playerState = GetPlayerState<AFoSPlayerState>()) {
				playerState->deaths += 1;
			}
			if (AFPSCharacter* damager = Cast<AFPSCharacter>(DamageCauser->GetOwner())) {
				if (AFoSPlayerState* playerState = damager->GetPlayerState<AFoSPlayerState>()) {
					playerState->kills += 1;
				}
			}
			this->TeleportTo(FVector(3480.0f, -9620.0f, 140.0f), FRotator(0.0f, -90.0f, 0.0f), false, false);
			MyInventory->DestroyItems();
			SpawnFirstWeapon();
			CurrentHealth = 100;
		}
		
	}

	//Functions that occur on all machines.
	/*
		Any special functionality that should occur as a result of damage or death should be placed here.
	*/
}

void AFPSCharacter::OnRep_CurrentHealth()
{
	OnHealthUpdate(NULL);
}

void AFPSCharacter::SetCurrentHealth(float healthValue, AActor *DamageCauser)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		CurrentHealth = FMath::Clamp(healthValue, 0.f, MaxHealth);
		OnHealthUpdate(DamageCauser);
	}
}

float AFPSCharacter::TakeDamage(float DamageTaken, struct FDamageEvent const &DamageEvent, AController *EventInstigator, AActor *DamageCauser)
{
	float damageApplied = CurrentHealth - DamageTaken;
	SetCurrentHealth(damageApplied, DamageCauser);
	return damageApplied;
}

AItem *AFPSCharacter::GetEquippedItem()
{
	return this->EquippedItem;
}
#include "MyCharacter.h"

AMyCharacter::AMyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	myCamera = FindComponentByClass<UCameraComponent>();
	onShoot = false;
	playerLife = maxPlayerLife;
	rifleTimer = rifleCoolDown;
	poisonTimer = 0;
	internalPoisonDamage = 0;

	CheckWeaponSetUp();
}

void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MovePlayer(movementDirection);
	Shooting(DeltaTime);
	AutomaticShooting(DeltaTime);
	ShotGunShooting(DeltaTime);
	PlayerPoisoned(DeltaTime);
	PlayerIsFreeze(DeltaTime);
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Vertical", this, &AMyCharacter::MoveFront);
	PlayerInputComponent->BindAxis("Horizontal", this, &AMyCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Rotation", this, &AMyCharacter::RotatePlayer);
	PlayerInputComponent->BindAxis("RotationY", this, &AMyCharacter::RotateCameraPlayer);
}

void AMyCharacter::MoveFront(float vertical)
{
	movementDirection.Y = vertical;
}

void AMyCharacter::MoveRight(float horizontal)
{
	movementDirection.X = horizontal;
}

void AMyCharacter::MovePlayer(FVector2D movementDirection)
{
	if (onFreeze) return;

	AddMovementInput(GetActorForwardVector(), movementDirection.Y);
	AddMovementInput(GetActorRightVector(), movementDirection.X);
}

void AMyCharacter::RotatePlayer(float rotation)
{
	if (onFreeze) return;

	AddControllerYawInput(rotation);
}

void AMyCharacter::RotateCameraPlayer(float rotation)
{
	if (onFreeze) return;

	FRotator rot = myCamera->RelativeRotation;

	float verticalRotation = rot.Pitch + rotation;
	verticalRotation = FMath::ClampAngle(verticalRotation, -60, 45);

	FRotator setRotation = FRotator(verticalRotation, rot.Yaw, rot.Roll);
	myCamera->SetRelativeRotation(setRotation);
}

void AMyCharacter::StartShoot()
{
	switch (current)
	{
		case EBehavioursShoot::Gun:
		onShoot = true;
		break;

		case EBehavioursShoot::Automatic:
		onAutomaticShoot = true;
		break;

		case EBehavioursShoot::Shotgun:
		onShotGunShoot = true;
		break;

	}
}

void AMyCharacter::StopShoot()
{
	switch (current)
	{
	case EBehavioursShoot::Gun:
		onShoot = false;
		break;

	case EBehavioursShoot::Automatic:
		onAutomaticShoot = false;
		break;

	case EBehavioursShoot::Shotgun:
		onShotGunShoot = false;
		break;

	}
}

void AMyCharacter::CheckWeaponSetUp()
{
	switch (current)
	{
	case EBehavioursShoot::Gun:
		SetUpGunWeapon();
		break;

	case EBehavioursShoot::Automatic:
		SetUpAutomaticWeapon();
		break;

	case EBehavioursShoot::Shotgun:
		SetUpShotGunWeapon();
		break;
	}

	onShoot = false;
	onAutomaticShoot = false;
	onShotGunShoot = false;
}

void AMyCharacter::SetUpGunWeapon()
{
	myRifle->SetVisibility(true);
	myAutomaticWeapon->SetVisibility(false);
	myShotGun->SetVisibility(false);
	rifleTimer = rifleCoolDown;
}

void AMyCharacter::SetUpAutomaticWeapon()
{	
	myAutomaticWeapon->SetVisibility(true);
	myRifle->SetVisibility(false);
	myShotGun->SetVisibility(false);
	rifleTimer = automaticGunCoolDown;
}

void AMyCharacter::SetUpShotGunWeapon()
{
	myShotGun->SetVisibility(true);
	myRifle->SetVisibility(false);
	myAutomaticWeapon->SetVisibility(false);
	rifleTimer = shotgunCoolDown;
}

void AMyCharacter::Shooting(float deltaTime)
{
	if (current != EBehavioursShoot::Gun) return;

	if (onShoot)
	{
		rifleTimer += deltaTime;
		if (rifleTimer >= rifleCoolDown)
		{
			makeARaycast = true;

			rifleSocketLocation = myRifle->GetSocketLocation("Spawner");
			rifleSocketRotation = myRifle->GetSocketRotation("Spawner");

			UParticleSystemComponent* myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), rifleMuzzle->Template, rifleSocketLocation, rifleSocketRotation, rifleMuzzle->GetComponentScale(), true);

			rifleTimer = 0;
		}
	}
}

void AMyCharacter::AutomaticShooting(float deltaTime)
{
	if (current != EBehavioursShoot::Automatic) return;

	if (onAutomaticShoot)
	{
		rifleTimer += deltaTime;
		if (rifleTimer >= automaticGunCoolDown)
		{
			makeARaycast = true;

			rifleSocketLocation = myAutomaticWeapon->GetSocketLocation("Spawner");
			rifleSocketRotation = myAutomaticWeapon->GetSocketRotation("Spawner");

			UParticleSystemComponent* myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), automaticMuzzle->Template, rifleSocketLocation, rifleSocketRotation, rifleMuzzle->GetComponentScale(), true);

			rifleTimer = 0;
		}
	}
}

void AMyCharacter::ShotGunShooting(float deltaTime)
{
	if (current != EBehavioursShoot::Shotgun) return;

	if (onShotGunShoot)
	{
		rifleTimer += deltaTime;
		if (rifleTimer >= shotgunCoolDown)
		{
			makeAShotGunRaycast = true;

			rifleSocketLocation = myShotGun->GetSocketLocation("Spawner");
			rifleSocketRotation = myShotGun->GetSocketRotation("Spawner");

			UParticleSystemComponent* myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), shotGunMuzzle->Template, rifleSocketLocation, rifleSocketRotation, rifleMuzzle->GetComponentScale(), true);

			rifleTimer = 0;
		}
	}
}

void AMyCharacter::SwitchToAutomaticWeapon()
{
	current = EBehavioursShoot::Automatic;
	CheckWeaponSetUp();
}

void AMyCharacter::SwitchToShotGunWeapon()
{
	current = EBehavioursShoot::Shotgun;
	CheckWeaponSetUp();
}

void AMyCharacter::PlayerTakeDamage(float damage)
{
	playerLife = playerLife - damage;
	UpdatePlayerHUDLife();

	auto myUI = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
	if (myUI)
		myUI->PlayerOnDamage();


	if (playerLife <= 0)
		PlayerDead();
}

void AMyCharacter::UpdatePlayerHUDLife()
{
	auto life = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
	float updateLifeValue = playerLife / maxPlayerLife;
	if (life)
		life->UpdatePlayerHUDLife(updateLifeValue);
}

void AMyCharacter::PlayerDead()
{
	auto myUI = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
	if (myUI)
		myUI->PlayerGameOver();
}

void AMyCharacter::HealCharacter()
{
	playerLife = maxPlayerLife;
	UpdatePlayerHUDLife();
}

void AMyCharacter::PlayerPoisoned(float deltaTimer)
{
	if (!onPoison) return;

	if (!poisonAlreadyPlayed)
	{
		poisonSound->Play();
		poisonAlreadyPlayed = true;
	}

	auto myUI = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
	if (myUI)
		myUI->PlayerOnPoison(true);

	poisonTimer += deltaTimer;
	internalPoisonDamage += deltaTimer;

	if (internalPoisonDamage >= 1)
	{
		PlayerTakeDamage(1);
		internalPoisonDamage = 0;
	}
	if (poisonTimer >= poisonEffectTime)
	{
		internalPoisonDamage = 0;
		poisonTimer = 0;
		onPoison = false;
		poisonAlreadyPlayed = false;

		if (myUI)
			myUI->PlayerOnPoison(false);
	}


}

void AMyCharacter::PlayerIsFreeze(float deltaTimer)
{
	if (!onFreeze) return;
	
	if (!frozenAlreadyPlayed)
	{
		frozenSound->Play();
		frozenAlreadyPlayed = true;
	}

	auto myUI = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
	if (myUI)
		myUI->PlayerFrozen(true);

	frozenTimer += deltaTimer;
	if (frozenTimer >= frozenEffectTime)
	{
		frozenTimer = 0;
		onFreeze = false;
		frozenAlreadyPlayed = false;

		auto myUI = Cast<AMyLevelUI>(GetWorld()->GetFirstPlayerController());
		if (myUI)
			myUI->PlayerFrozen(false);
	}
}


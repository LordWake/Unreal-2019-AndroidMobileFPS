#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "MyLevelUI.h"
#include "MyCharacter.generated.h"

UENUM(BlueprintType)
enum class EBehavioursShoot :uint8
{
	Gun UMETA(DisplayName = "Gun"),
	Automatic UMETA(DisplayName = "Automatic"),
	Shotgun UMETA(DisplayName = "Shotgun"),
};


UCLASS()
class BERKELYUM_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AMyCharacter();

	UPROPERTY(EditAnywhere, Category = Enum)
	EBehavioursShoot current;

	UPROPERTY(EditAnywhere)
	float rifleCoolDown;
	UPROPERTY(EditAnywhere)
	float automaticGunCoolDown;
	UPROPERTY(EditAnywhere)
	float shotgunCoolDown;
	UPROPERTY(EditAnywhere)
	float poisonEffectTime;
	UPROPERTY(EditAnywhere)
	float frozenEffectTime;

	float internalPoisonDamage;
	float frozenTimer;
	float poisonTimer;
	float rifleTimer;
	float playerLife;
	UPROPERTY(EditAnywhere)
	float maxPlayerLife;
	
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* rifleMuzzle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* automaticMuzzle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* shotGunMuzzle;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent * myRifle;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent * myAutomaticWeapon;
	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent * myShotGun;

	FVector2D movementDirection;

	FVector rifleSocketLocation;
	
	FRotator rifleSocketRotation;
	
	bool onShoot;
	bool onAutomaticShoot;
	bool onShotGunShoot;
	bool frozenAlreadyPlayed;
	bool poisonAlreadyPlayed;

	UPROPERTY(BlueprintReadWrite)
	bool onFreeze;
	UPROPERTY(BlueprintReadWrite)
	bool onPoison;
	UPROPERTY(BlueprintReadWrite)
	bool makeARaycast;
	UPROPERTY(BlueprintReadWrite)
	bool makeAShotGunRaycast;


	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* frozenSound;
	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* poisonSound;

protected:
	virtual void BeginPlay() override;

	UCameraComponent* myCamera;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveFront(float vertical);
	void MoveRight(float horizontal);
	void MovePlayer(FVector2D myDirection);

	void RotatePlayer(float rotation);
	void RotateCameraPlayer(float rotation);

	UFUNCTION(BlueprintCallable)
		void StartShoot();
	UFUNCTION(BlueprintCallable)
		void StopShoot();
		
	void Shooting(float deltaTime);
	void AutomaticShooting(float deltaTime);
	void ShotGunShooting(float deltaTime);
	
	UFUNCTION(BlueprintCallable)
	void PlayerTakeDamage(float damage);
	void UpdatePlayerHUDLife();

	UFUNCTION(BlueprintCallable)
	void HealCharacter();
	UFUNCTION(BlueprintCallable)
	void SwitchToAutomaticWeapon();
	UFUNCTION(BlueprintCallable)
	void SwitchToShotGunWeapon();

	void PlayerDead();
	void PlayerPoisoned(float deltaTimer);
	void PlayerIsFreeze(float deltaTimer);

	void CheckWeaponSetUp();
	void SetUpGunWeapon();
	void SetUpAutomaticWeapon();
	void SetUpShotGunWeapon();

};

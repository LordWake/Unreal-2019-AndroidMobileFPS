#pragma once

#include "Engine.h"
#include "BossAnim.h"
#include "DiamondCell.h"
#include "TurretBullet.h"
#include "GameFramework/Actor.h"
#include "Boss.generated.h"

UCLASS()
class BERKELYUM_API ABoss : public AActor
{
	GENERATED_BODY()
	
public:	

	ABoss();

	UPROPERTY(EditAnywhere)
	TArray<AActor *> myWaypoints;

	UPROPERTY(EditAnywhere)
	ADiamondCell * diamondCell;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent * fireParticle;

	UPROPERTY(BlueprintReadWrite)
	UBoxComponent* boxTrigger;

	UPROPERTY(BlueprintReadWrite)
	UStaticMeshComponent* myWeapon;
	USkeletalMeshComponent* myMesh;
	UBossAnim* anim;

	UPROPERTY(EditAnywhere)
	float shotCoolDown;
	UPROPERTY(EditAnywhere)
	float runCoolDown;
	float restFireCoolDown;
	float runInternalTimer;
	UPROPERTY(EditAnywhere)
	int maxShotAmount;
	UPROPERTY(EditAnywhere)
	float speed;
	float internalShotTimer;
	
	UPROPERTY(EditAnywhere)
	float maxLife;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATurretBullet> prefabBullet;

	FVector socketLocation;
	FRotator socketRotation;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* bossDamageSound;
	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* fireSound;

protected:

	virtual void BeginPlay() override;

	AActor* target;
	bool canShot;
	bool dontCheckDistance;
	bool onDeadBoss;
	float life;

	int shotCount;
	int currentWaypoint;
	bool restFire;
	bool onRun;
	bool canRun;

public:	

	virtual void Tick(float DeltaTime) override;
	void ShootPlayer(float delatimer);
	void CheckDistanceToPlayer();
	void PullTrigger();
	void LookToPlayer();
	void HitPlayer();
	void MoveToNextPosition(float deltaTimer);
	void CheckRunState(float deltaTimer);
	void ResetFireTime(float deltaTimer);
	
	UFUNCTION(BlueprintCallable)
	void TakeBossDamage(float damage);
	void BossDead();
	
};

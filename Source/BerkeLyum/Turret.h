#pragma once

#include "Engine.h"
#include "Engine/World.h"
#include "TurretBullet.h"
#include "GameFramework/Actor.h"
#include "DiamondCell.h"
#include "Turret.generated.h"

UCLASS()
class BERKELYUM_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	ATurret();

	AActor* target;
	UPROPERTY(EditAnywhere)
	ADiamondCell * diamondCell;

	bool isNear;
	UPROPERTY(EditAnywhere)
	bool finalTurret;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* fireSound;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAudioComponent* explosionSound;

	UPROPERTY(EditAnywhere)
	float shootCoolDown;
	float shotTimer;
	UPROPERTY(EditAnywhere)
	float maxLife;
	float life;

	FVector socketLocation;
	FRotator socketRotation;
	UStaticMeshComponent * myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent * fireParticle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent * deadParticle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ATurretBullet> prefabBullet;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void LookToTarget();
	void CheckDistanteToPlayer();
	void ShootPlayer(float deltaTimer);

	UFUNCTION(BlueprintCallable)
	void TakeTurretDamage(float damage);
	void DeadTurret();
	
	
};

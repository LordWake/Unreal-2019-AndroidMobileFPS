#pragma once

#include "Engine.h"
#include "DroneBullet.h"
#include "GameFramework/Actor.h"
#include "FreezeDrone.generated.h"

UCLASS()
class BERKELYUM_API AFreezeDrone : public AActor
{
	GENERATED_BODY()
	
public:	

	AFreezeDrone();

	UPROPERTY(EditAnywhere)
	TArray<AActor *> myWaypoints;

	AActor* target;

	bool isNear;
	int currentWaypoint;

	UPROPERTY(EditAnywhere)
	float shootCoolDown;
	float shotTimer;
	UPROPERTY(EditAnywhere)
	float life;
	UPROPERTY(EditAnywhere)
	float speed;

	FVector socketLocation;
	FRotator socketRotation;
	UStaticMeshComponent * myMesh;

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent *fireParticle;
	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent *deadParticle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADroneBullet> prefabBullet;

	UPROPERTY(BlueprintReadWrite)
	UAudioComponent* fireSound;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	void MoveThisDrone(float deltaTimer);
	void LookToTarget();
	void CheckDistanceToPlayer();
	void ShootPlayer(float delaTimer);

	UFUNCTION(BlueprintCallable)
	void TakeDroneDamage(float damage);
	void DeadDrone();

	
	
};

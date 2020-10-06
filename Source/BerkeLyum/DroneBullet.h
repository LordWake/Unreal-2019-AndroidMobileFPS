#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "DroneBullet.generated.h"

UCLASS()
class BERKELYUM_API ADroneBullet : public AActor
{
	GENERATED_BODY()
	
public:	
	ADroneBullet();

	UPROPERTY(BlueprintReadWrite)
	UParticleSystemComponent* deadParticle;

	UPROPERTY(EditAnywhere)
	float bulletSpeed;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void MoveThisBullet(float deltaTimer);
	UFUNCTION(BlueprintCallable)
	void DestroyThisBullet();

	
	
};

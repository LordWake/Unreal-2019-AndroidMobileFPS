#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Laser.generated.h"

UCLASS()
class BERKELYUM_API ALaser : public AActor
{
	GENERATED_BODY()
	
public:	
	ALaser();

protected:
	virtual void BeginPlay() override;
	bool firstWaypointCompleted;


public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	AActor* firstWaypoint;
	UPROPERTY(EditAnywhere)
	AActor* secondWaypoint;
	UPROPERTY(EditAnywhere)
	float speed;

	void MoveThisLaser(float deltaTimer);
	
};

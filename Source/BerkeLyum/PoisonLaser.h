#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "PoisonLaser.generated.h"

UCLASS()
class BERKELYUM_API APoisonLaser : public AActor
{
	GENERATED_BODY()
	
public:	

	APoisonLaser();

protected:

	virtual void BeginPlay() override;
	bool firstWaypointCompleted;

public:	

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		AActor * firstWaypoint;
	UPROPERTY(EditAnywhere)
		AActor * secondWaypoint;
	UPROPERTY(EditAnywhere)
		float speed;

	void MoveThisLaser(float deltaTimer);

	
	
};

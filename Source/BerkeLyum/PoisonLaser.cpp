#include "PoisonLaser.h"

APoisonLaser::APoisonLaser()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APoisonLaser::BeginPlay()
{
	Super::BeginPlay();
	firstWaypointCompleted = false;
	
}

void APoisonLaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisLaser(DeltaTime);
}

void APoisonLaser::MoveThisLaser(float deltaTimer)
{
	if (firstWaypointCompleted == false)
	{
		if (GetActorLocation().Z <= firstWaypoint->GetActorLocation().Z)
			SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTimer);
		else
			firstWaypointCompleted = true;
	}

	else
	{
		if (GetActorLocation().Z >= secondWaypoint->GetActorLocation().Z)
			SetActorLocation(GetActorLocation() - GetActorForwardVector() * speed * deltaTimer);
		else
			firstWaypointCompleted = false;
	}
}


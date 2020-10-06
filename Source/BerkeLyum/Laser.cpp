#include "Laser.h"

ALaser::ALaser()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ALaser::BeginPlay()
{
	Super::BeginPlay();
	firstWaypointCompleted = false;
}

void ALaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisLaser(DeltaTime);
}

void ALaser::MoveThisLaser(float deltaTimer)
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


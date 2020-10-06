#include "FreezeDrone.h"

AFreezeDrone::AFreezeDrone()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFreezeDrone::BeginPlay()
{
	Super::BeginPlay();
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	currentWaypoint = 0;

}

void AFreezeDrone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisDrone(DeltaTime);
	LookToTarget();
	CheckDistanceToPlayer();
	ShootPlayer(DeltaTime);
}

void AFreezeDrone::MoveThisDrone(float deltaTimer)
{
	auto myTransform = GetActorLocation();
	auto waypointTransform = Cast<AActor>(myWaypoints[currentWaypoint])->GetActorLocation();

	auto distanceToTarget = (myTransform - waypointTransform).Size();

	if (distanceToTarget > 50)
	{
		auto myLerp = FMath::Lerp(myTransform, waypointTransform, speed * deltaTimer);
		SetActorLocation(myLerp);
	}
	else
	{
		currentWaypoint++;

		if (currentWaypoint >= myWaypoints.Num())
			currentWaypoint = 0;
	}
}

void AFreezeDrone::LookToTarget()
{
	if (!target) return;

	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rotationVector = dir.Rotation();
	SetActorRotation(FRotator(rotationVector.Pitch, rotationVector.Yaw, 0));
}

void AFreezeDrone::CheckDistanceToPlayer()
{
	FVector distanceToPlayer = target->GetActorLocation() - GetActorLocation();
	if (distanceToPlayer.Size() < 1500)
	{
		isNear = true;
	}

	else
	{
		isNear = false;
	}
}

void AFreezeDrone::ShootPlayer(float delaTimer)
{
	if (!isNear) return;

	shotTimer += delaTimer;
	if (shotTimer >= shootCoolDown)
	{
		socketLocation = myMesh->GetSocketLocation("Spawner");
		socketRotation = myMesh->GetSocketRotation("Spawner");

		FActorSpawnParameters parameters;
		parameters.Owner = this;

		fireSound->Play();
		GetWorld()->SpawnActor<ADroneBullet>(prefabBullet, socketLocation, socketRotation, parameters);
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireParticle->Template, socketLocation, GetActorRotation(), fireParticle->GetComponentScale(), true);

		shotTimer = 0;
	}
}

void AFreezeDrone::TakeDroneDamage(float damage)
{
	life = life - damage;
	if (life <= 0)
		DeadDrone();
}

void AFreezeDrone::DeadDrone()
{
	UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), deadParticle->Template, GetActorLocation(), GetActorRotation(), deadParticle->GetComponentScale(), true);
	Destroy();

}


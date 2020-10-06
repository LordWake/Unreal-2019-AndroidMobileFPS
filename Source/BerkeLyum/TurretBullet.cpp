#include "TurretBullet.h"

ATurretBullet::ATurretBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATurretBullet::BeginPlay()
{
	Super::BeginPlay();	
}

void ATurretBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisBullet(DeltaTime);
}

void ATurretBullet::MoveThisBullet(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector()* - 1 * bulletSpeed * deltaTimer);
}

void ATurretBullet::DestroyThisBullet()
{
	UParticleSystemComponent* myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), deadParticle->Template, GetActorLocation(), GetActorRotation(), deadParticle->GetComponentScale(), true);

	Destroy(true);
}


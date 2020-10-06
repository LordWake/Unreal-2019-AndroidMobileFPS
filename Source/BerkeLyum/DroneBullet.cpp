
#include "DroneBullet.h"


ADroneBullet::ADroneBullet()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ADroneBullet::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADroneBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveThisBullet(DeltaTime);
}

void ADroneBullet::MoveThisBullet(float deltaTimer)
{
	SetActorLocation(GetActorLocation() + GetActorForwardVector()* -1 * bulletSpeed * deltaTimer);
}

void ADroneBullet::DestroyThisBullet()
{
	UParticleSystemComponent* myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), deadParticle->Template, GetActorLocation(), GetActorRotation(), deadParticle->GetComponentScale(), true);

	Destroy(true);
}


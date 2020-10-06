#include "Turret.h"

ATurret::ATurret()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATurret::BeginPlay()
{
	Super::BeginPlay();
	target = GetWorld()->GetFirstPlayerController()->GetPawn();
	myMesh = FindComponentByClass<UStaticMeshComponent>();
	life = maxLife;
}

void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LookToTarget();
	CheckDistanteToPlayer();
	ShootPlayer(DeltaTime);
}

void ATurret::LookToTarget()
{
	if (!target) return;

	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rotationVector = dir.Rotation();
	SetActorRotation(FRotator(0, rotationVector.Yaw, 0));
}

void ATurret::CheckDistanteToPlayer()
{
	FVector distanteToPlayer = target->GetActorLocation() - GetActorLocation();
	if (distanteToPlayer.Size() < 1500)
	{
		isNear = true;
	}
	else
	{
		isNear = false;
	}
}

void ATurret::ShootPlayer(float deltatimer)
{
	if (!isNear) return;
	shotTimer += deltatimer;
	socketLocation = myMesh->GetSocketLocation("Spawner");
	socketRotation = myMesh->GetSocketRotation("Spawner");

	if (shotTimer >= shootCoolDown)
	{
		FActorSpawnParameters parameters;
		parameters.Owner = this;
		GetWorld()->SpawnActor<ATurretBullet>(prefabBullet, socketLocation, socketRotation, parameters);

		fireSound->Play();
		UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireParticle->Template, socketLocation, GetActorRotation(), fireParticle->GetComponentScale(), true);
		shotTimer = 0;
	}

}

void ATurret::TakeTurretDamage(float damage)
{
	life = life - damage;
	if (life <= 0)
	{
		DeadTurret();
	}
}

void ATurret::DeadTurret()
{
	explosionSound->Play();

	if(finalTurret)
	{
		if(diamondCell)
		diamondCell->TakeLifeDamage(1);
	}

	UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), deadParticle->Template, GetActorLocation(), GetActorRotation(), deadParticle->GetComponentScale(), true);
	Destroy();
}


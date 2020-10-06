#include "Boss.h"


ABoss::ABoss()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABoss::BeginPlay()
{
	Super::BeginPlay();
	canShot = false;
	life = maxLife;
	currentWaypoint = 0;

	boxTrigger->SetGenerateOverlapEvents(false);

	myMesh = FindComponentByClass<USkeletalMeshComponent>();
	if (myMesh)
		anim = Cast<UBossAnim>(myMesh->GetAnimInstance());

	target = GetWorld()->GetFirstPlayerController()->GetPawn();

}

void ABoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CheckRunState(DeltaTime);
	MoveToNextPosition(DeltaTime);
	if (onRun == false)
	{
		CheckDistanceToPlayer();
		LookToPlayer();
		PullTrigger();
		HitPlayer();
		ShootPlayer(DeltaTime);
		ResetFireTime(DeltaTime);
	}
}

void ABoss::ShootPlayer(float delatimer)
{
	if (canShot == false || restFire || onDeadBoss) return;

	internalShotTimer += delatimer;
	if (internalShotTimer >= shotCoolDown)
	{
		anim->fireAnimation = true;
		internalShotTimer = 0;
	}
}

void ABoss::PullTrigger()
{
	if (restFire || onDeadBoss) return;
	if (anim)
	{
		if (anim->fireTrigger)
		{
			socketLocation = myWeapon->GetSocketLocation("Spawner");
			socketRotation = myWeapon->GetSocketRotation("Spawner");

			UParticleSystemComponent * myParticle = UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), fireParticle->Template, fireParticle->GetComponentLocation(), fireParticle->GetComponentRotation(), fireParticle->GetComponentScale(), true);

			fireSound->Play();
			FActorSpawnParameters parameters;
			parameters.Owner = this;
			GetWorld()->SpawnActor<ATurretBullet>(prefabBullet, socketLocation, FRotator(0, GetActorRotation().Yaw + 180, 0), parameters);

			shotCount++;
			if (shotCount >= maxShotAmount)
				restFire = true;

			anim->fireTrigger = false;
		}
	}
}

void ABoss::HitPlayer()
{
	if (anim->dontPunch || onDeadBoss) return;

	FVector distanteToPlayer = target->GetActorLocation() - GetActorLocation();
	if (distanteToPlayer.Size() <= 140)
	{
		if (anim)
			anim->hitPlayer = true;

		anim->dontPunch = true;
	}
}

void ABoss::LookToPlayer()
{
	if (!target || onDeadBoss) return;

	FVector dir = target->GetActorLocation() - GetActorLocation();
	FRotator rotationVector = dir.Rotation();
	SetActorRotation(FRotator(0, rotationVector.Yaw, 0));
}

void ABoss::CheckDistanceToPlayer()
{
	if (dontCheckDistance) return;
	FVector distanteToPlayer = target->GetActorLocation() - GetActorLocation();

	if (distanteToPlayer.Size() < 800)
	{
		canShot = true;
		canRun = true;
		dontCheckDistance = true;
	}
}

void ABoss::TakeBossDamage(float damage)
{
	if (onDeadBoss) return;

	bossDamageSound->Play();
	canShot = true;
	canRun = true;
	dontCheckDistance = true;

	life = life - damage;

	if (life <= 0)
		BossDead();
}

void ABoss::BossDead()
{
	if (diamondCell)
		diamondCell->TakeLifeDamage(1);
	if (anim)
		anim->bossIsDead = true;

	onDeadBoss = true;
}

void ABoss::ResetFireTime(float deltaTimer)
{
	if (!restFire || onDeadBoss) return;

	if (anim)
		anim->isWaiting = true;

	restFireCoolDown += deltaTimer;
	if (restFireCoolDown >= 7)
	{
		anim->isWaiting = false;
		restFireCoolDown = 0;
		shotCount = 0;
		restFire = false;
	}

}

void ABoss::CheckRunState(float deltaTimer)
{
	if (!canRun || onDeadBoss) return;

	runInternalTimer += deltaTimer;
	if (runInternalTimer >= runCoolDown)
	{
		onRun = true;
	}
}

void ABoss::MoveToNextPosition(float deltaTimer)
{
	if (!onRun || onDeadBoss) return;

	auto myTransform = GetActorLocation();
	auto waypointTransform = Cast<AActor>(myWaypoints[currentWaypoint])->GetActorLocation();
	auto distanceToTarget = (myTransform - waypointTransform).Size();

	if (distanceToTarget > 50)
	{
		if (anim)
			anim->isRunning = true;
		FVector dir = waypointTransform - myTransform;
		SetActorRotation(dir.Rotation());
		SetActorLocation(GetActorLocation() + GetActorForwardVector() * speed * deltaTimer);

		if (anim)
			anim->isRunning = true;
	}
	else
	{
		currentWaypoint++;
		if (currentWaypoint >= myWaypoints.Num())
			currentWaypoint = 0;

		onRun = false;
		runInternalTimer = 0;

		if (anim)
			anim->isRunning = false;

	}
}




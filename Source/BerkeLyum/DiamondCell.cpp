
#include "DiamondCell.h"


ADiamondCell::ADiamondCell()
{
	PrimaryActorTick.bCanEverTick = false;

}

void ADiamondCell::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADiamondCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADiamondCell::TakeLifeDamage(float damage)
{
	life = life - damage;
	CheckMyLife();
}

void ADiamondCell::CheckMyLife()
{
	if (life <= 0)
		Destroy(true);
}


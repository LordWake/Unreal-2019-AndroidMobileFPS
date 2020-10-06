#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "DiamondCell.generated.h"

UCLASS()
class BERKELYUM_API ADiamondCell : public AActor
{
	GENERATED_BODY()
	
public:	
	ADiamondCell();

	UPROPERTY(EditAnywhere)
	int life;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	void TakeLifeDamage(float damage);
	void CheckMyLife();

	
	
};

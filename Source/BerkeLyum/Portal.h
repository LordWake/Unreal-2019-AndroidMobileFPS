#pragma once

#include "Engine.h"
#include "GameFramework/Actor.h"
#include "Portal.generated.h"

UCLASS()
class BERKELYUM_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	

	APortal();
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString nextLevel;

protected:

	virtual void BeginPlay() override;

public:	

	virtual void Tick(float DeltaTime) override;
	
};

#pragma once

#include "Engine.h"
#include "Animation/AnimInstance.h"
#include "BossAnim.generated.h"


UCLASS()
class BERKELYUM_API UBossAnim : public UAnimInstance
{
	GENERATED_BODY()

public:

		UPROPERTY(BlueprintReadWrite)
		bool fireAnimation;

		UPROPERTY(BlueprintReadWrite)
		bool fireTrigger;

		UPROPERTY(BlueprintReadOnly)
		bool bossIsDead;

		UPROPERTY(BlueprintReadWrite)
		bool hitPlayer;

		UPROPERTY(BlueprintReadWrite)
		bool dontPunch;

		UPROPERTY(BlueprintReadOnly)
		bool isWaiting;

		UPROPERTY(BlueprintReadOnly)
		bool isRunning;

		UFUNCTION(BlueprintCallable)
		void OnActivatedBoxTrigger();
		UFUNCTION(BlueprintCallable)
		void OnDeactivatedBoxTrigger();
};

#pragma once

#include "Engine.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"


UCLASS()
class BERKELYUM_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
		UPROPERTY(BlueprintReadWrite)
		float playerHUDlife;
	
		UPROPERTY(BlueprintReadOnly)
		bool gameOver;

		UPROPERTY(BlueprintReadWrite)
		bool onDamage;

		UPROPERTY(BlueprintReadWrite)
		bool onPoison;

		UPROPERTY(BlueprintReadWrite)
		bool onFrozen;
};

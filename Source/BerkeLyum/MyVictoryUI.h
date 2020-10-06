#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyVictoryUI.generated.h"

UCLASS()
class BERKELYUM_API AMyVictoryUI : public APlayerController
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget* canvas;

	void virtual BeginPlay() override;
	
	
};

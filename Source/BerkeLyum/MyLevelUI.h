#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyLevelUI.generated.h"

UCLASS()
class BERKELYUM_API AMyLevelUI : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget* canvas;

	void virtual BeginPlay() override;

	void UpdatePlayerHUDLife(float life);
	void PlayerGameOver();
	void PlayerOnDamage();
	void PlayerOnPoison(bool isUnderEffect);
	void PlayerFrozen(bool isUnderEffect);
		
};

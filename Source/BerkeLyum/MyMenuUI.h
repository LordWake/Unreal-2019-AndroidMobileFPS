#pragma once

#include "Engine.h"
#include "MyUserWidget.h"
#include "GameFramework/PlayerController.h"
#include "MyMenuUI.generated.h"


UCLASS()
class BERKELYUM_API AMyMenuUI : public APlayerController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMyUserWidget> prefabCanvas;

	UMyUserWidget * canvas;

	void virtual BeginPlay() override;
	
	
};

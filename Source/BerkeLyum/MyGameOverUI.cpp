
#include "MyGameOverUI.h"

void AMyGameOverUI::BeginPlay()
{
	Super::BeginPlay();
	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);

	if (canvas)
		canvas->AddToViewport();
}





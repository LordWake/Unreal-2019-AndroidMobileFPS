#include "MyVictoryUI.h"

void AMyVictoryUI::BeginPlay()
{
	Super::BeginPlay();

	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);

	if (canvas)
		canvas->AddToViewport();
}





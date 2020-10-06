#include "MyMenuUI.h"

void AMyMenuUI::BeginPlay()
{
	Super::BeginPlay();
	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);

	if (canvas)
		canvas->AddToViewport();
}




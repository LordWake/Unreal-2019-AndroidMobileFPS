#include "MyLevelUI.h"

void AMyLevelUI::BeginPlay()
{
	Super::BeginPlay();
	canvas = CreateWidget<UMyUserWidget>(this, prefabCanvas);

	if (canvas)
		canvas->AddToViewport();
}

void AMyLevelUI::UpdatePlayerHUDLife(float life)
{
	if(canvas)
	canvas->playerHUDlife = life;
}

void AMyLevelUI::PlayerGameOver()
{
	if (canvas)
	canvas->gameOver = true;
}

void AMyLevelUI::PlayerOnDamage()
{
	if (canvas)
	canvas->onDamage = true;
}

void AMyLevelUI::PlayerOnPoison(bool isUnderEffect)
{
	if (canvas)
		canvas->onPoison = isUnderEffect;
}

void AMyLevelUI::PlayerFrozen(bool isUnderEffect)
{
	if (canvas)
		canvas->onFrozen = isUnderEffect;
}




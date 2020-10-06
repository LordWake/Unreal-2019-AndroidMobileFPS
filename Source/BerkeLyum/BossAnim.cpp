#include "BossAnim.h"
#include "Boss.h"


void UBossAnim::OnActivatedBoxTrigger()
{
	ABoss* myBoss = Cast<ABoss>(GetOwningActor());
	myBoss->boxTrigger->SetGenerateOverlapEvents(true);
}

void UBossAnim::OnDeactivatedBoxTrigger()
{
	ABoss* myBoss = Cast<ABoss>(GetOwningActor());
	myBoss->boxTrigger->SetGenerateOverlapEvents(false);
}

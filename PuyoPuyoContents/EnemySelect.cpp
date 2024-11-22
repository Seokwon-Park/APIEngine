#include "aepch.h"
#include "EnemySelect.h"

AEnemySelect::AEnemySelect()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("EnemySelectOn");
	Sr->SetComponentScale({ 48,48 });
	Sr->SetRemoveBackground(true);
	Sr->SetRemoveColor({2,2});
	Sr->SetPivot(EPivotType::TopLeft);
}

AEnemySelect::~AEnemySelect()
{
}


void AEnemySelect::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AEnemySelect::BeginPlay()
{
	Super::BeginPlay();
}

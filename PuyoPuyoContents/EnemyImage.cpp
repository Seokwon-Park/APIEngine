#include "aepch.h"
#include "EnemyImage.h"

AEnemyImage::AEnemyImage()
{
	Sr = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr->SetSprite("FaceIdle");
	Sr->SetComponentScale({ 160,112 });
	Sr->SetPivot(EPivotType::TopLeft);
}

AEnemyImage::~AEnemyImage()
{
}


void AEnemyImage::SetLose()
{
	Sr->SetSprite("FaceLose", GameSettings::GetInstance().EnemyIndex);
	Sr->SetRemoveBackground(true);
	Sr->SetRemoveColor({ 2,2 });
}

void AEnemyImage::SetWin()
{
	Sr->SetSprite("FaceWin", GameSettings::GetInstance().EnemyIndex);
	Sr->SetRemoveBackground(true);
	Sr->SetRemoveColor({ 2,2 });
}

void AEnemyImage::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AEnemyImage::BeginPlay()
{
	Super::BeginPlay();
	Sr->SetSprite("FaceIdle",GameSettings::GetInstance().EnemyIndex);
	Sr->SetRemoveBackground(true);
	Sr->SetRemoveColor({ 2,2 });


}

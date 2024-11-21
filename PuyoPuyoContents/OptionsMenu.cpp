#include "aepch.h"
#include "OptionsMenu.h"

#include <EngineCore/ImageManager.h>

AOptionsMenu::AOptionsMenu()
{
	UEngineSprite* Sprite = UImageManager::GetInstance().FindSprite("OPTMENU");
	
	OptMenuSr.resize(7, nullptr);
	OptMenuTitle = CreateDefaultSubobject<USpriteRendererComponent>("");
	OptMenuTitle->SetSprite("OPTMENU");
	OptMenuTitle->SetComponentScale(Sprite->GetSpriteData(0).Transform.Scale);
	OptMenuTitle->SetComponentLocation({176, 16});
	OptMenuTitle->SetRemoveBackground(true);
	OptMenuTitle->SetPivot(EPivotType::TopLeft);
	
	
	for (int i = 0; i < 7; i++)
	{
		OptMenuSr[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		OptMenuSr[i]->SetSprite("OPTMENU", i+1);
		OptMenuSr[i]->SetComponentScale(Sprite->GetSpriteData(i+1).Transform.Scale);
		OptMenuSr[i]->SetComponentLocation({ 32, 64 + 48*i });
		OptMenuSr[i]->SetRemoveBackground(true);
		OptMenuSr[i]->SetPivot(EPivotType::TopLeft);
	}
}

AOptionsMenu::~AOptionsMenu()
{
}


void AOptionsMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOptionsMenu::BeginPlay()
{
	Super::BeginPlay();
}

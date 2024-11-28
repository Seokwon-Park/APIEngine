#include "aepch.h"
#include "OptionsItem.h"

#include <EngineCore/ImageManager.h>

AOptionsItem::AOptionsItem()
{
	UEngineSprite* Sprite = UImageManager::GetInstance().FindSprite("OPTMENU");

	OptItemRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	OptItemRenderer->SetSprite("OPTMENU");
	OptItemRenderer->SetComponentScale(Sprite->GetSpriteData(0).Transform.Scale);
	OptItemRenderer->SetRemoveBackground(true);
	OptItemRenderer->SetPivot(EPivotType::TopLeft);
}

AOptionsItem::~AOptionsItem()
{
}


void AOptionsItem::SetupItem(std::string_view _SpriteName, int _Index)
{
	UEngineSprite* Sprite = UImageManager::GetInstance().FindSprite(_SpriteName);

	OptItemRenderer->SetSprite(_SpriteName, _Index);
	OptItemRenderer->SetComponentScale(Sprite->GetSpriteData(_Index).Transform.Scale);
}

void AOptionsItem::Select()
{
	if (!SelectActions.empty())
	{
		UAudioManager::SoundPlay("PuyoSelect.wav");
		for (auto Action : SelectActions)
		{
			Action();
		}
	}
}

void AOptionsItem::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOptionsItem::BeginPlay()
{
	Super::BeginPlay();
}

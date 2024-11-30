#include "aepch.h"
#include "VSMenuMap.h"

AVSMenuMap::AVSMenuMap()
{
	Frame.resize(8, nullptr);
	for (int i = 0; i < Frame.size(); i++)
	{
		Frame[i] = CreateDefaultSubobject<USpriteRendererComponent>("VSFrame");
		Frame[i]->SetSprite("VSMenuFrameOn", i);
		Frame[i]->SetComponentScale(FrameScale[i]);
		Frame[i]->SetComponentLocation(FrameLoc[i]);
		Frame[i]->SetRemoveColor(UColor(136, 102, 102, 0));
		Frame[i]->SetPivot(EPivotType::TopLeft);
	}

	MapRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	MapRenderer->SetSprite("VSBG", 0);
	MapRenderer->SetComponentScale({ 320, 240 });
	MapRenderer->SetComponentLocation({ 8,8 });
	MapRenderer->SetPivot(EPivotType::TopLeft);

	BlackRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	BlackRenderer->SetSprite("Black");
	BlackRenderer->SetComponentScale({ 320, 240 });
	BlackRenderer->SetComponentLocation({ 8,8 });
	BlackRenderer->SetPivot(EPivotType::TopLeft);
	BlackRenderer->SetAlphaRate(0.5f);
	BlackRenderer->SetActive(false);

}

AVSMenuMap::~AVSMenuMap()
{
}


void AVSMenuMap::SetOn()
{
	for (int i = 0; i < Frame.size(); i++)
	{
		Frame[i]->SetSprite("VSMenuFrameOn", i);
	}
	BlackRenderer->SetActive(false);
}

void AVSMenuMap::SetOff()
{
	for (int i = 0; i < Frame.size(); i++)
	{
		Frame[i]->SetSprite("VSMenuFrameOff", i);
	}
	BlackRenderer->SetActive(true);
}

void AVSMenuMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AVSMenuMap::BeginPlay()
{
	Super::BeginPlay();
}

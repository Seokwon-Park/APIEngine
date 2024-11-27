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

}

AVSMenuMap::~AVSMenuMap()
{
}


void AVSMenuMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AVSMenuMap::BeginPlay()
{
	Super::BeginPlay();
}

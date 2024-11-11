#include "aepch.h"
#include "PlayBackground.h"
#include <EngineCore/EngineAPICore.h>

APlayBackground::APlayBackground()
{
	SetActorScale({100,100});

	HeadSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	HeadSr->SetOrder(1);
	HeadSr->SetSprite("LVHEAD", 0);
	HeadSr->SetComponentScale({640, 32});
	HeadSr->SetPivot(PivotType::TopLeft);

	CenterSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	CenterSr->SetOrder(1);
	CenterSr->SetSprite("LVCenter", 0);
	CenterSr->SetComponentScale({ 32, 128 });
	CenterSr->SetComponentLocation({ 304, 64 });
	CenterSr->SetPivot(PivotType::TopLeft);

	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	Sr->SetOrder(-1);
	Sr->SetSprite("L1_F.CNS.bmp", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(PivotType::TopLeft);
}

APlayBackground::~APlayBackground()
{
}

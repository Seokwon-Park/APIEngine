#include "aepch.h"
#include "PlayBackground.h"
#include <EngineCore/EngineAPICore.h>

APlayBackground::APlayBackground()
{
	SetActorScale({100,100});

	HeadSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	HeadSr->SetOrder(1);
	HeadSr->SetSprite("VSHEAD", 0);
	HeadSr->SetComponentScale({640, 32});
	HeadSr->SetPivot(EPivotType::TopLeft);

	CenterSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	CenterSr->SetOrder(1);
	CenterSr->SetSprite("VSCenter", 0);
	CenterSr->SetComponentScale({ 32, 128 });
	CenterSr->SetComponentLocation({ 304, 64 });
	CenterSr->SetPivot(EPivotType::TopLeft);

	Sr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	Sr->SetOrder(-1);
	Sr->SetSprite("VSBOARD", 0);
	Sr->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
	Sr->SetPivot(EPivotType::TopLeft);
}

APlayBackground::~APlayBackground()
{
}

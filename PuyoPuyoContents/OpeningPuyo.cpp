#include "aepch.h"
#include "OpeningPuyo.h"

AOpeningPuyo::AOpeningPuyo()
{
	OPPuyoBot = CreateDefaultSubobject<USpriteRendererComponent>("OPPuyoBot");
	OPPuyoBot->SetSprite("OPPUYOBOT");
	OPPuyoBot->SetComponentScale({640,240});
	OPPuyoBot->SetComponentLocation({ 640,480 });
	OPPuyoBot->SetPivot(EPivotType::BottomRight);
	OPPuyoBot->SetRemoveBackground(true);

	OPPuyoTop = CreateDefaultSubobject<USpriteRendererComponent>("OPPuyoTop");
	OPPuyoTop->SetSprite("OPPUYOTOP");
	OPPuyoTop->SetComponentScale({ 480,240 });
	OPPuyoTop->SetComponentLocation({ 640,240 });
	OPPuyoTop->SetPivot(EPivotType::BottomRight);
	OPPuyoTop->SetRemoveBackground(true);
}

AOpeningPuyo::~AOpeningPuyo()
{
}


void AOpeningPuyo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void AOpeningPuyo::BeginPlay()
{
	Super::BeginPlay();
}

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

	OPPuyoEyeL= CreateDefaultSubobject<USpriteRendererComponent>("OPPuyoEyeL");
	OPPuyoEyeL->SetSprite("OPPUYOEYE");
	OPPuyoEyeL->SetComponentScale({ 144,144 });
	OPPuyoEyeL->SetComponentLocation({ 448, 416 });
	OPPuyoEyeL->SetPivot(EPivotType::BottomRight);
	OPPuyoEyeL->SetRemoveBackground(true);

	OPPuyoEyeR = CreateDefaultSubobject<USpriteRendererComponent>("OPPuyoEyeR");
	OPPuyoEyeR->SetSprite("OPPUYOEYE");
	OPPuyoEyeR->SetComponentScale({ 144,144 });
	OPPuyoEyeR->SetComponentLocation({ 624,464 });
	OPPuyoEyeR->SetRemoveBackground(true);
}

AOpeningPuyo::~AOpeningPuyo()
{
}


void AOpeningPuyo::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (Time / 0.5f >= 1.0f)return;
	Time += _DeltaTime;
	OPPuyoEyeL->SetComponentLocation(FVector2D::Lerp({448,416}, {368,336}, Time/0.5f));
	OPPuyoEyeR->SetComponentLocation(FVector2D::Lerp({ 624,464 }, { 544,384 }, Time / 0.5f));

}
void AOpeningPuyo::BeginPlay()
{
	Super::BeginPlay();
}

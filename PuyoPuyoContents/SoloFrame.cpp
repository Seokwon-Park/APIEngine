#include "aepch.h"
#include "SoloFrame.h"

ASoloFrame::ASoloFrame()
{
	HeadSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	HeadSr->SetOrder(ERenderLayer::FRAME);
	HeadSr->SetSprite("LVHEAD", 0);
	HeadSr->SetComponentScale({ 640, 32 });
	HeadSr->SetPivot(EPivotType::TopLeft);

	CenterSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	CenterSr->SetOrder(ERenderLayer::FRAME);
	CenterSr->SetSprite("LVCenter", 0);
	CenterSr->SetComponentScale({ 32, 128 });
	CenterSr->SetComponentLocation({ 304, 64 });
	CenterSr->SetPivot(EPivotType::TopLeft);

	LeftSideSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	LeftSideSr->SetOrder(ERenderLayer::FRAME);
	LeftSideSr->SetSprite("LVL", 0);
	LeftSideSr->SetComponentScale({ 32, 384 });
	LeftSideSr->SetComponentLocation({ 0, 32 });
	LeftSideSr->SetPivot(EPivotType::TopLeft);

	InnerLeftSideSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	InnerLeftSideSr->SetOrder(ERenderLayer::FRAME);
	InnerLeftSideSr->SetSprite("LVIL", 0);
	InnerLeftSideSr->SetComponentScale({ 16, 384 });
	InnerLeftSideSr->SetComponentLocation({ 224, 32 });
	InnerLeftSideSr->SetPivot(EPivotType::TopLeft);

	RightSideSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	RightSideSr->SetOrder(ERenderLayer::FRAME);
	RightSideSr->SetSprite("LVR", 0);
	RightSideSr->SetComponentScale({ 32, 384 });
	RightSideSr->SetComponentLocation({ 608, 32 });
	RightSideSr->SetPivot(EPivotType::TopLeft);

	InnerRightSideSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	InnerRightSideSr->SetOrder(ERenderLayer::FRAME);
	InnerRightSideSr->SetSprite("LVIR", 0);
	InnerRightSideSr->SetComponentScale({ 16, 384 });
	InnerRightSideSr->SetComponentLocation({ 400, 32 });
	InnerRightSideSr->SetPivot(EPivotType::TopLeft);

	TailSr = CreateDefaultSubobject<USpriteRendererComponent>("PlayBackground");
	TailSr->SetOrder(ERenderLayer::FRAME);
	TailSr->SetSprite("LVtail", 0);
	TailSr->SetComponentScale({ 640, 64 });
	TailSr->SetComponentLocation({ 0, 416 });
	TailSr->SetPivot(EPivotType::TopLeft);
}

ASoloFrame::~ASoloFrame()
{
}


void ASoloFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ASoloFrame::BeginPlay()
{
	Super::BeginPlay();
}

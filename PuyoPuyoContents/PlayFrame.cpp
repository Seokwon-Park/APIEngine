#include "aepch.h"
#include "PlayFrame.h"

APlayFrame::APlayFrame()
{
	FrameSr.resize(7, nullptr);

	for (int i = 0; i < 7; i++)
	{
		FrameSr[i] = CreateDefaultSubobject<USpriteRendererComponent>("PlayFrame" + std::to_string(i));
		FrameSr[i]->SetOrder(ERenderLayer::Frame);
		FrameSr[i]->SetComponentScale(FrameScale[i]);
		FrameSr[i]->SetComponentLocation(FrameLocation[i]);
		FrameSr[i]->SetPivot(EPivotType::TopLeft);
	}

	HeadSr->SetOrder(ERenderLayer::Frame);
	HeadSr->SetSprite("LVHEAD", 0);
	HeadSr->SetComponentScale({ 640, 32 });

	CenterSr->SetOrder(ERenderLayer::Frame);
	CenterSr->SetSprite("LVCenter", 0);
	CenterSr->SetComponentScale({ 32, 128 });
	CenterSr->SetComponentLocation({ 304, 64 });
	CenterSr->SetPivot(EPivotType::TopLeft);

	LeftSideSr->SetOrder(ERenderLayer::Frame);
	LeftSideSr->SetSprite("LVL", 0);
	LeftSideSr->SetComponentScale({ 32, 384 });
	LeftSideSr->SetComponentLocation({ 0, 32 });
	LeftSideSr->SetPivot(EPivotType::TopLeft);

	InnerLeftSideSr->SetOrder(ERenderLayer::Frame);
	InnerLeftSideSr->SetSprite("LVIL", 0);
	InnerLeftSideSr->SetComponentScale({ 16, 384 });
	InnerLeftSideSr->SetComponentLocation({ 224, 32 });
	InnerLeftSideSr->SetPivot(EPivotType::TopLeft);

	RightSideSr->SetOrder(ERenderLayer::Frame);
	RightSideSr->SetSprite("LVR", 0);
	RightSideSr->SetComponentScale({ 32, 384 });
	RightSideSr->SetComponentLocation({ 608, 32 });
	RightSideSr->SetPivot(EPivotType::TopLeft);

	InnerRightSideSr->SetOrder(ERenderLayer::Frame);
	InnerRightSideSr->SetSprite("LVIR", 0);
	InnerRightSideSr->SetComponentScale({ 16, 384 });
	InnerRightSideSr->SetComponentLocation({ 400, 32 });
	InnerRightSideSr->SetPivot(EPivotType::TopLeft);

	TailSr->SetOrder(ERenderLayer::Frame);
	TailSr->SetSprite("LVtail", 0);
	TailSr->SetComponentScale({ 640, 64 });
	TailSr->SetComponentLocation({ 0, 416 });
	TailSr->SetPivot(EPivotType::TopLeft);
}

APlayFrame::~APlayFrame()
{
}


void APlayFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void APlayFrame::SetFrame(EPuyoGameMode _Mode, int _StageIndex)
{
	switch (_Mode)
	{
	case EPuyoGameMode::Solo:

		break;
	case EPuyoGameMode::Versus:
		break;
	case EPuyoGameMode::Training:
		break;
	default:
		break;
	}
}
void APlayFrame::BeginPlay()
{
	Super::BeginPlay();
}

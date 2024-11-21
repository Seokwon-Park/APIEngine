#include "aepch.h"
#include "PlayFrame.h"

APlayFrame::APlayFrame()
{
	FrameSr.resize(7, nullptr);

	for (int i = 0; i < 7; i++)
	{
		FrameSr[i] = CreateDefaultSubobject<USpriteRendererComponent>("PlayFrame" + std::to_string(i));
		FrameSr[i]->SetSprite("LV"+FramePartName[i], 0);
		FrameSr[i]->SetOrder(ERenderLayer::Frame);
		FrameSr[i]->SetComponentScale(FrameScale[i]);
		FrameSr[i]->SetComponentLocation(FrameLocation[i]);
		FrameSr[i]->SetPivot(EPivotType::TopLeft);
	}

	Sr1 = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr2 = CreateDefaultSubobject<USpriteRendererComponent>("");
	Sr1->SetSprite("TOKO_1A.CNS.BMP");
	Sr1->SetComponentScale({ 640, 480 });
	Sr1->SetPivot(EPivotType::TopLeft);
	Sr1->SetRemoveBackground(true);
	Sr1->SetOrder(ERenderLayer::Frame);
	Sr1->SetActive(false);


	Sr2->SetSprite("TOKO_2A.CNS.BMP");
	Sr2->SetRemoveBackground(true);
	Sr2->SetRemoveColor({ 64,64 });
	Sr2->SetComponentScale({ 640, 480 });
	Sr2->SetPivot(EPivotType::TopLeft);
	Sr2->SetRemoveBackground(true);
	Sr2->SetOrder(ERenderLayer::Frame);
	Sr2->SetActive(false);
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
		for (int i = 0; i < 7; i++)
		{
			FrameSr[i]->SetSprite("LV" + FramePartName[i], _StageIndex);
		}
		break;
	case EPuyoGameMode::Versus:
		for (int i = 0; i < 7; i++)
		{
			FrameSr[i]->SetSprite("VS" + FramePartName[i], _StageIndex);
		}
		break;
	case EPuyoGameMode::Training:
		for (int i = 0; i < 7; i++)
		{
			FrameSr[i]->SetActive(false);
		}
		Sr1->SetActive(true);
		Sr2->SetActive(true);
		break;
	default:
		break;
	}
}
void APlayFrame::BeginPlay()
{
	Super::BeginPlay();
}

#include "aepch.h"
#include "OpeningTitle.h"

#include <EngineCore/ImageManager.h>
AOpeningTitle::AOpeningTitle()
{
	Sr.resize(4, nullptr);
	for (int i = 0; i < 4; i++)
	{
		Sr[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
		if (i % 2 == 0)
		{
			Sr[i]->SetSprite("Pu");
			Sr[i]->SetComponentScale({ 108,96 });
		}
		else
		{
			Sr[i]->SetSprite("Yo");
			Sr[i]->SetComponentScale({ 116,96 });
		}
		Sr[i]->SetComponentLocation(StartPos);
		Sr[i]->SetRemoveBackground(true);
		Sr[i]->SetActive(false);
		Sr[i]->SetPivot(EPivotType::TopLeft);
		Sr[i]->SetOrder(ERenderLayer::BottomCover);
	}

	TsuRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	TsuRenderer->SetSprite("Tsu");
	TsuRenderer->SetComponentScale({ 176,144 });
	TsuRenderer->SetComponentLocation({ 224,80 });
	TsuRenderer->SetPivot(EPivotType::TopLeft);
	TsuRenderer->SetOrder(ERenderLayer::Frame);
	TsuRenderer->SetRemoveBackground(true);
	TsuRenderer->SetActive(false);

	TitleAnim = CreateDefaultSubobject<UAnimatorComponent>("");
	TitleAnim->CreateAnimation("Idle", "TitlePuyoR", {0,2,0,1,0}, 0.1f, false);
	TitleAnim2 = CreateDefaultSubobject<UAnimatorComponent>("");
	TitleAnim2->CreateAnimation("Idle", "TitlePuyoG", { 0,2,0,1,0 }, 0.1f, false);


	TitlePuyo1 = CreateDefaultSubobject<USpriteRendererComponent>("");
	TitlePuyo1->SetSprite("TitlePuyoR");
	TitlePuyo1->SetComponentScale({ 48,32 });
	TitlePuyo1->SetComponentLocation({ 96.0f,-32.0f });
	TitlePuyo1->SetPivot(EPivotType::TopLeft);
	TitlePuyo1->SetOrder(ERenderLayer::TitlePuyo);
	TitlePuyo1->SetRemoveBackground(true);
	TitlePuyo1->SetActive(false);
	TitlePuyo1->SetAnimator(TitleAnim);

	TitlePuyo2 = CreateDefaultSubobject<USpriteRendererComponent>("");
	TitlePuyo2->SetSprite("TitlePuyoR");
	TitlePuyo2->SetComponentScale({ 48,32 });
	TitlePuyo2->SetComponentLocation({ 320.0f,-32.0f });
	TitlePuyo2->SetPivot(EPivotType::TopLeft);
	TitlePuyo2->SetOrder(ERenderLayer::TitlePuyo);
	TitlePuyo2->SetRemoveBackground(true);
	TitlePuyo2->SetActive(false);
	TitlePuyo2->SetAnimator(TitleAnim);


	TitlePuyo3 = CreateDefaultSubobject<USpriteRendererComponent>("");
	TitlePuyo3->SetSprite("TitlePuyoG");
	TitlePuyo3->SetComponentScale({48,48});
	TitlePuyo3->SetComponentLocation({ 464.0f,-48.0f });
	TitlePuyo3->SetPivot(EPivotType::TopLeft);
	TitlePuyo3->SetOrder(ERenderLayer::TitlePuyo);
	TitlePuyo3->SetRemoveBackground(true);
	TitlePuyo3->SetActive(false);
	TitlePuyo3->SetAnimator(TitleAnim2);
}

AOpeningTitle::~AOpeningTitle()
{
}


void AOpeningTitle::Init()
{
	Timer = 0.0f;
}

void AOpeningTitle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Timer += _DeltaTime;
	for (int i = 0; i < 4; i++)
	{
		float LocalTime = Timer - Delays[i];
		if (LocalTime < 0.0f) continue;
		Sr[i]->SetActive(true);
		FVector2D NewPosition;

		if (LocalTime < Duration) // 초기에서 중간 위치 이동
		{
			float Alpha = LocalTime / Duration; // 0 ~ 1 보간 값
			NewPosition = FVector2D::Lerp(StartPos, MidPos[i], Alpha);
		}
		else if (LocalTime < 2 * Duration) // 중간에서 최종 위치 이동
		{
			Sr[i]->SetOrder(ERenderLayer::Warn);
			float Alpha = (LocalTime - Duration) / Duration; // 0 ~ 1 보간 값
			NewPosition = FVector2D::Lerp(MidPos[i], TargetPos[i], Alpha);
		}
		else
		{
			NewPosition = TargetPos[i]; // 최종 위치에 고정
			if (i == 3)
				IsLocated = true;
		}
		Sr[i]->SetComponentLocation(NewPosition);
	}

	if (true == IsLocated)
	{
		Timer2 += _DeltaTime;
		if (Timer2 < Duration2)
		{
			TsuRenderer->SetComponentLocation(FVector2D::Lerp({ 224,80 }, { 464,80 }, Timer2 / Duration2));
		}
		else
		{
			IsMoveEnd = true;
		}
	}

	if (IsMoveEnd == true)
	{
		Timer3 += _DeltaTime;
		if (Timer3 < Duration3)
		{
			TitlePuyo1->SetComponentLocation(FVector2D::Lerp({ 96.0f,-32.0f }, { 96.0f,132.0f }, Timer3 / Duration3));
			TitlePuyo2->SetComponentLocation(FVector2D::Lerp({ 320.0f,-32.0f }, { 320.0f,132.0f }, Timer3 / Duration3));
			TitlePuyo3->SetComponentLocation(FVector2D::Lerp({ 464.0f, -48.0f }, { 464.0f,80.0f }, Timer3 / Duration3));
		}
		else
		{
			TitleAnim->ChangeAnimation("Idle");
			TitleAnim2->ChangeAnimation("Idle");
		}
	}
}
void AOpeningTitle::BeginPlay()
{
	Super::BeginPlay();
}

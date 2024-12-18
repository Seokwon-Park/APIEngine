#include "aepch.h"
#include "CarbuncleMenu.h"

ACarbuncleMenu::ACarbuncleMenu()
{
	LArrowAnimator = CreateDefaultSubobject<UAnimatorComponent>("CarLArrowAnim");
	RArrowAnimator = CreateDefaultSubobject<UAnimatorComponent>("CarRArrowAnim");
	JewelAnimator = CreateDefaultSubobject<UAnimatorComponent>("CarJewelAnim");

	HeadRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarHead");
	HeadRenderer->SetSprite("carHead");
	HeadRenderer->SetComponentScale({ 160,152 });
	HeadRenderer->SetComponentLocation({ 0,0 });
	HeadRenderer->SetRemoveBackground(true);
	HeadRenderer->SetPivot(EPivotType::TopCenter);

	UBodyRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarUBody");
	UBodyRenderer->SetSprite("CARUBODY");
	UBodyRenderer->SetComponentScale({ 144,48 });
	UBodyRenderer->SetComponentLocation({ 0,152 });
	UBodyRenderer->SetRemoveBackground(true);
	UBodyRenderer->SetPivot(EPivotType::TopCenter);

	DBodyRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarDBody");
	DBodyRenderer->SetSprite("CARDBODY");
	DBodyRenderer->SetComponentScale({ 144,40 });
	DBodyRenderer->SetComponentLocation({ 0, 200 });
	DBodyRenderer->SetRemoveBackground(true);
	DBodyRenderer->SetPivot(EPivotType::TopCenter);

	LHandRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarLHand");
	LHandRenderer->SetSprite("CARLEFT");
	LHandRenderer->SetComponentScale({ 24,72 });
	LHandRenderer->SetComponentLocation({ -72, 152 });
	LHandRenderer->SetRemoveBackground(true);
	LHandRenderer->SetPivot(EPivotType::TopRight);

	RHandRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarRHand");
	RHandRenderer->SetSprite("CARRIGHT");
	RHandRenderer->SetComponentScale({ 24, 72 });
	RHandRenderer->SetComponentLocation({ 72, 152 });
	RHandRenderer->SetRemoveBackground(true);
	RHandRenderer->SetPivot(EPivotType::TopLeft);

	LegRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarLeg");
	LegRenderer->SetSprite("CARLEG");
	LegRenderer->SetComponentScale({ 176, 32 });
	LegRenderer->SetComponentLocation({ 0, 240 });
	LegRenderer->SetRemoveBackground(true);
	LegRenderer->SetPivot(EPivotType::TopCenter);

	LArrowRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarLArrow");
	LArrowRenderer->SetSprite("CARLEFTARROW");
	LArrowRenderer->SetComponentScale({ 16, 24 });
	LArrowRenderer->SetComponentLocation({ -100, 124 }); // 72 + 24
	LArrowRenderer->SetRemoveBackground(true);
	LArrowRenderer->SetPivot(EPivotType::MiddleRight);
	LArrowRenderer->SetAnimator(LArrowAnimator);
	LArrowAnimator->CreateAnimation("CarFlicker", "CARLEFTARROW", 0, 1, 0.1f);
	LArrowAnimator->CreateAnimation("CarArrowIdle", "CARLEFTARROW", 1, 1, 0.0f);
	LArrowAnimator->ChangeAnimation("CarFlicker");


	RArrowRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarRArrow");
	RArrowRenderer->SetSprite("CARRIGHTARROW");
	RArrowRenderer->SetComponentScale({ 16, 24 });
	RArrowRenderer->SetComponentLocation({ 100, 124 }); // 72 + 24
	RArrowRenderer->SetRemoveBackground(true);
	RArrowRenderer->SetPivot(EPivotType::MiddleLeft);
	RArrowRenderer->SetAnimator(RArrowAnimator);
	RArrowAnimator->CreateAnimation("CarFlicker", "CARRIGHTARROW", 0, 1, 0.1f);
	RArrowAnimator->CreateAnimation("CarArrowIdle", "CARRIGHTARROW", 1, 1, 0.0f);
	RArrowAnimator->ChangeAnimation("CarFlicker");

	JewelRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarJewel");
	JewelRenderer->SetSprite("CARJEWEL");
	JewelRenderer->SetComponentScale({ 24, 24 });
	JewelRenderer->SetComponentLocation({ 0, 112 }); // 72 + 24
	JewelRenderer->SetPivot(EPivotType::TopCenter);
	JewelRenderer->SetAnimator(JewelAnimator);
	JewelAnimator->CreateAnimation("CarTwinkle", "CARJEWEL", 0, 3, .05f);
	JewelRenderer->SetActive(false);
	//JewelAnimator->ChangeAnimation("CarTwinkle");
}

ACarbuncleMenu::~ACarbuncleMenu()
{
}

void ACarbuncleMenu::BeginPlay()
{
	Super::BeginPlay();

	//GetWorld()->BindAction(EKey::Mouseleft, KeyEvent::Down, std::bind(&ACarbuncleMenu::Test, this));
}

void ACarbuncleMenu::Test()
{
	MenuIndex = (MenuIndex + 1) % 5;
	UBodyRenderer->SetSprite("CARUBODY", MenuIndex);
	DBodyRenderer->SetSprite("CARDBODY", MenuIndex);
	LHandRenderer->SetSprite("CARLEFT", MenuIndex % 3);
	RHandRenderer->SetSprite("CARRIGHT", MenuIndex % 3);
	LArrowAnimator->ChangeAnimation("CarArrowIdle");
	RArrowAnimator->ChangeAnimation("CarArrowIdle");
	SetMenuInactive();

}

void ACarbuncleMenu::SetMenuInactive()
{
	int Index = 5 + MenuIndex;
	HeadRenderer->SetSprite("CARHEAD", 1);
	UBodyRenderer->SetSprite("CARUBODY", Index);
	DBodyRenderer->SetSprite("CARDBODY", Index);
	LHandRenderer->SetSprite("CARLEFT", 3);
	RHandRenderer->SetSprite("CARRIGHT", 3);
	LegRenderer->SetSprite("CARLEG", 1);
	JewelRenderer->SetActive(false);
	LArrowAnimator->ChangeAnimation("CarArrowIdle");
	RArrowAnimator->ChangeAnimation("CarArrowIdle");
}

void ACarbuncleMenu::SetMenuActive()
{
	HeadRenderer->SetSprite("CARHEAD", 0);
	UBodyRenderer->SetSprite("CARUBODY", MenuIndex);
	DBodyRenderer->SetSprite("CARDBODY", MenuIndex);
	LHandRenderer->SetSprite("CARLEFT", 0);
	RHandRenderer->SetSprite("CARRIGHT", 0);
	LegRenderer->SetSprite("CARLEG", 0);
	LArrowAnimator->ChangeAnimation("CarFlicker");
	RArrowAnimator->ChangeAnimation("CarFlicker");
}

void ACarbuncleMenu::PlayCloseAnimation()
{
	IsPlaying = true;
}



void ACarbuncleMenu::SetupCarbuncleMenu(int _MenuIndex)
{
	MenuIndex = _MenuIndex;
	if (MenuIndex == 0)
	{
		LArrowRenderer->SetActive(false);
	}
	if (MenuIndex == MaxMenuSize - 1)
	{
		RArrowRenderer->SetActive(false);
	}
	UBodyRenderer->SetSprite("CARUBODY", MenuIndex);
	DBodyRenderer->SetSprite("CARDBODY", MenuIndex);
}

void ACarbuncleMenu::MoveTo(float _Amount, int _Dir)
{
	if (IsMoving == false)
	{
		IsMoving = true;
		MoveAmount = _Amount;
		Dir = _Dir;
	}
}

void ACarbuncleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	if (IsPlaying)
	{
		Timer += _DeltaTime;
		if (Timer < 0.1f)
		{
			int Index = 10 + MenuIndex;
			HeadRenderer->SetSprite("CARHEAD", 1);
			UBodyRenderer->SetSprite("CARUBODY", Index);
			UBodyRenderer->SetComponentScale({ 144,40 });
			UBodyRenderer->SetPivot(EPivotType::TopCenter);
			DBodyRenderer->SetSprite("CARDBODY", Index);
			DBodyRenderer->SetComponentScale({ 144,48 });
			DBodyRenderer->SetComponentLocation({ 0, 192 });
			DBodyRenderer->SetPivot(EPivotType::TopCenter);
			LHandRenderer->SetSprite("CARLEFT", 3);
			RHandRenderer->SetSprite("CARRIGHT", 3);
			LegRenderer->SetSprite("CARLEG", 1);
			JewelRenderer->SetActive(false);
		}
		else if(Timer < 0.2f)
		{
			int Index = 15 + MenuIndex;
			HeadRenderer->SetSprite("CARHEAD", 1);
			UBodyRenderer->SetSprite("CARUBODY", Index);
			UBodyRenderer->SetComponentScale({ 144,56 });
			UBodyRenderer->SetPivot(EPivotType::TopCenter);
			DBodyRenderer->SetSprite("CARDBODY", Index);
			DBodyRenderer->SetComponentScale({ 144,32 });
			DBodyRenderer->SetComponentLocation({ 0, 208 });
			DBodyRenderer->SetPivot(EPivotType::TopCenter);
			LHandRenderer->SetSprite("CARLEFT", 3);
			RHandRenderer->SetSprite("CARRIGHT", 3);
			LegRenderer->SetSprite("CARLEG", 1);
		}
		else if (Timer < .3f)
		{
			int Index = 20;
			HeadRenderer->SetSprite("CARHEAD", 1);
			UBodyRenderer->SetSprite("CARUBODY", Index);
			UBodyRenderer->SetComponentScale({ 144,88 });
			UBodyRenderer->SetPivot(EPivotType::TopCenter);
			DBodyRenderer->SetActive(false);
			LHandRenderer->SetSprite("CARLEFT", 3);
			RHandRenderer->SetSprite("CARRIGHT", 3);
			LegRenderer->SetSprite("CARLEG", 1);
		}
		return;
	}

	if (MoveAmount > 0)
	{
		MoveAmount -= _DeltaTime*1000.0f;
		SetActorLocation(GetActorLocation() + FVector2D(Dir * _DeltaTime * 1000.0f, 0.0f));
		return;
	}

	
	IsMoving = false;

}

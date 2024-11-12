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
	LArrowRenderer->SetComponentLocation({ -104, 124 }); // 72 + 24
	LArrowRenderer->SetRemoveBackground(true);
	LArrowRenderer->SetPivot(EPivotType::MiddleRight);
	LArrowRenderer->SetAnimator(LArrowAnimator);
	LArrowAnimator->CreateAnimation("CarFlicker", "CARLEFTARROW", 0, 1, .05f);
	LArrowAnimator->CreateAnimation("CarArrowIdle", "CARLEFTARROW", 1, 1, 0.0f);
	LArrowAnimator->ChangeAnimation("CarFlicker");


	RArrowRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarRArrow");
	RArrowRenderer->SetSprite("CARRIGHTARROW");
	RArrowRenderer->SetComponentScale({ 16, 24 });
	RArrowRenderer->SetComponentLocation({ 104, 124 }); // 72 + 24
	RArrowRenderer->SetRemoveBackground(true);
	RArrowRenderer->SetPivot(EPivotType::MiddleLeft);
	RArrowRenderer->SetAnimator(RArrowAnimator);
	RArrowAnimator->CreateAnimation("CarFlicker", "CARRIGHTARROW", 0, 1, .05f);
	RArrowAnimator->CreateAnimation("CarArrowIdle", "CARRIGHTARROW", 1, 1, 0.0f);
	RArrowAnimator->ChangeAnimation("CarFlicker");

	JewelRenderer = CreateDefaultSubobject<USpriteRendererComponent>("CarJewel");
	JewelRenderer->SetSprite("CARJEWEL");
	JewelRenderer->SetComponentScale({ 24, 24 });
	JewelRenderer->SetComponentLocation({ 0, 112 }); // 72 + 24
	JewelRenderer->SetPivot(EPivotType::TopCenter);
	JewelRenderer->SetAnimator(JewelAnimator);
	JewelAnimator->CreateAnimation("CarTwinkle", "CARJEWEL", 0, 3, .05f);
	JewelAnimator->ChangeAnimation("CarTwinkle");


}

ACarbuncleMenu::~ACarbuncleMenu()
{
}

void ACarbuncleMenu::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetInputSystem().BindAction(EKey::Mouseleft, KeyEvent::Down, std::bind(&ACarbuncleMenu::Test, this));

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
	SetInacitve();

}

void ACarbuncleMenu::SetInacitve()
{
	HeadRenderer->SetSprite("CARHEAD", 1);

}

void ACarbuncleMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	/*static int i = 0;
	BodyRenderer->SetSprite("CARBODY", 0);*/
}

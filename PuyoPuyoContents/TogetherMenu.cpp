#include "aepch.h"
#include "TogetherMenu.h"

#include "TogetherMenuGameMode.h"
#include "TogetherPlayGameMode.h"

ATogetherMenu::ATogetherMenu()
{
	//MapRenderer.resize(5, nullptr);
	//for (int i = 0; i < 5; i++)
	//{
	//	MapRenderer[i] = CreateDefaultSubobject<USpriteRendererComponent>("");
	//	MapRenderer[i]->SetSprite("VSBG", i);
	//	MapRenderer[i]->SetComponentLocation(Locations[i]);
	//	MapRenderer[i]->SetComponentScale({ 304, 224 });
	//}

	TextRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	TextRenderer->SetSprite("VSMenuText");
	TextRenderer->SetComponentLocation({ UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X, 416.0f });
	TextRenderer->SetComponentScale({ 512, 32 });
	TextRenderer->SetRemoveBackground(true);

	LArrowAnim = CreateDefaultSubobject<UAnimatorComponent>("");
	LArrowRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	LArrowRenderer->SetSprite("VSMenuLArrow", 0);
	LArrowRenderer->SetRemoveBackground(true);
	LArrowRenderer->SetRemoveColor(UColor(136, 102, 102, 0));
	LArrowRenderer->SetComponentScale({ 16, 24 });
	LArrowRenderer->SetComponentLocation({ 128.0f, 224.0f });
	LArrowRenderer->SetAnimator(LArrowAnim);

	LArrowAnim->CreateAnimation("Flick", "VSMenuLArrow", { 0,1 }, 0.1f);
	LArrowAnim->ChangeAnimation("Flick");

	RArrowAnim = CreateDefaultSubobject<UAnimatorComponent>("");
	RArrowRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	RArrowRenderer->SetSprite("VSMenuRArrow", 0);
	RArrowRenderer->SetRemoveBackground(true);
	RArrowRenderer->SetRemoveColor(UColor(136, 102, 102, 0));
	RArrowRenderer->SetComponentScale({ 16, 24 });
	RArrowRenderer->SetComponentLocation({ 512.0f, 224.0f });
	RArrowRenderer->SetAnimator(RArrowAnim);

	RArrowAnim->CreateAnimation("Flick", "VSMenuRArrow", { 0,1 }, 0.1f);
	RArrowAnim->ChangeAnimation("Flick");

	MenuInput = CreateDefaultSubobject<UInputComponent>("");
}

ATogetherMenu::~ATogetherMenu()
{
}

void ATogetherMenu::StartPlay()
{
	GameSettings::GetInstance().GameMode = EPuyoGameMode::Versus;
	GameSettings::GetInstance().MapIndex = CurIndex;
	GameSettings::GetInstance().DestroyRule = DestroyRule[CurIndex];

	UEngineAPICore::GetCore()->ResetLevel<ATogetherPlayGameMode, ADummyPawn>("TogetherPlay");
	UEngineAPICore::GetCore()->OpenLevel("TogetherPlay");//
}

void ATogetherMenu::MoveMenu(int _Dir)
{
	if (MoveAmount > 0) return;
	TextRenderer->SetActive(false);
	RArrowRenderer->SetActive(false);
	LArrowRenderer->SetActive(false);
	CurIndex += _Dir;
	if (CurIndex < 0)
	{
		CurIndex += 5;
	}
	CurIndex %= 5;

	TextRenderer->SetSprite("VSMenuText", CurIndex);

	MoveAmount = 384;
	Dir = _Dir;
	//오른쪽 키 눌렀을 때
	float HalfX = UEngineAPICore::GetEngineWindow().GetWindowSize().Half().X;
	if (_Dir == 1)
	{
		MenuItems[(CurIndex + 2) % 5]->SetActorLocation({ 152.0f + 384.0f * 3.0f, 96.0f });
		//MapRenderer[(CurIndex + 2) % 5]->SetComponentLocation({ HalfX + 1200.0f,224.0f });
	}
	else
	{
		MenuItems[(CurIndex + 3) % 5]->SetActorLocation({ 152.0f - 384.0f * 3.0f, 96.0f });
		//MapRenderer[(CurIndex + 3) % 5]->SetComponentLocation({ HalfX - 1200.0f, 224.0f });
	}

}

void ATogetherMenu::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (MoveAmount > 0)
	{
		MoveAmount -= _DeltaTime * 1000.0f;
		for (int i = 0; i < 5; i++)
		{
			//MapRenderer[i]->SetComponentLocation(MapRenderer[i]->GetComponentLocation() + FVector2D(_DeltaTime * -Dir, 0.0f) * 1000.0f);
			MenuItems[i]->SetActorLocation(MenuItems[i]->GetActorLocation() + FVector2D(_DeltaTime * -Dir, 0.0f) * 1000.0f);
		}
		if (MoveAmount <= 0)
		{
			TextRenderer->SetActive(true);
			RArrowRenderer->SetActive(true);
			LArrowRenderer->SetActive(true);
		}
	}

}
void ATogetherMenu::BeginPlay()
{
	Super::BeginPlay();
	MenuInput->BindAction(EKey::Right, KeyEvent::Press, std::bind(&ATogetherMenu::MoveMenu, this, 1));
	MenuInput->BindAction(EKey::Left, KeyEvent::Press, std::bind(&ATogetherMenu::MoveMenu, this, -1));
	MenuInput->BindAction(EKey::Enter, KeyEvent::Down, std::bind(&ATogetherMenu::StartPlay, this));

	MenuItems.resize(5, nullptr);
	for (int i = 0; i < 5; i++)
	{
		MenuItems[i] = GetWorld()->SpawnActor<AVSMenuMap>();
		MenuItems[i]->SetActorLocation(Locations[i]);
		MenuItems[i]->Setup(i);
	}

}

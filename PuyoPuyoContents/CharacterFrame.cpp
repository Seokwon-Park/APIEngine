#include "aepch.h"
#include "CharacterFrame.h"

ACharacterFrame::ACharacterFrame()
{
	FrameRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	FrameRenderer->SetSprite("Frame");
	FrameRenderer->SetRemoveBackground(true);
	FrameRenderer->SetComponentScale({ 176,128 });
	FrameRenderer->SetPivot(EPivotType::TopLeft);

	CharacterImage = CreateDefaultSubobject<USpriteRendererComponent>("");
	CharacterImage->SetSprite("ARLE");
	CharacterImage->SetRemoveBackground(true);
	CharacterImage->SetRemoveColor(UColor(6, 7, 6, 0));
	CharacterImage->SetComponentScale({ 160,112 });
	CharacterImage->SetComponentLocation({ 8,8});
	CharacterImage->SetPivot(EPivotType::TopLeft);

	InfoFrameRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	InfoFrameRenderer->SetSprite("Frame", 1);
	InfoFrameRenderer->SetRemoveBackground(true);
	InfoFrameRenderer->SetComponentScale({ 176,128 });
	InfoFrameRenderer->SetComponentLocation({ 0, 112 });
	InfoFrameRenderer->SetPivot(EPivotType::TopLeft);

	Text.resize(3);
}

ACharacterFrame::~ACharacterFrame()
{
}


void ACharacterFrame::SetFrameState(std::string_view _SpriteName, int _Index)
{
	CharacterImage->SetSprite(_SpriteName, _Index);
	CharacterImage->SetRemoveColor(UColor(6, 7, 6, 0));
	int StartIndex = LevelEnemiesPfsum[GameSettings::GetInstance().CurLevel-1];
	std::vector<std::string> EnemyName = EnemyNameData[StartIndex+_Index];
	for (int i = 0; i < EnemyName.size(); i++)
	{
		Text[i]->SetText(EnemyName[i]);
	}
}

void ACharacterFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ACharacterFrame::BeginPlay()
{
	Super::BeginPlay();

	for (int i = 0; i < 3; i++)
	{
		Text[i] = GetWorld()->SpawnActor<APuyoText>();
		Text[i]->SetupText(8, EPuyoBoardColor::Black);
		Text[i]->SetActorLocation(InfoFrameRenderer->GetWorldTransform().Location + FVector2D(24,16 + 32*i));
	}
}

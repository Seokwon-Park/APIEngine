#include "aepch.h"
#include "CharacterFrame.h"

ACharacterFrame::ACharacterFrame()
{
	FrameRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	FrameRenderer->SetSprite("Frame");
	FrameRenderer->SetRemoveBackground(true);
	FrameRenderer->SetComponentScale({176,128});
	FrameRenderer->SetPivot(EPivotType::TopLeft);
	
	CharacterImage = CreateDefaultSubobject<USpriteRendererComponent>("");
	CharacterImage->SetSprite("ARLE");
	CharacterImage->SetRemoveBackground(true);
	CharacterImage->SetRemoveColor(UColor(6, 7, 6, 255)); 
	CharacterImage->SetComponentScale({ 160,112 });
	CharacterImage->SetComponentLocation({ 8,8});
	CharacterImage->SetPivot(EPivotType::TopLeft);

	InfoFrameRenderer = CreateDefaultSubobject<USpriteRendererComponent>("");
	InfoFrameRenderer->SetSprite("Frame", 1);
	InfoFrameRenderer->SetRemoveBackground(true);
	InfoFrameRenderer->SetComponentScale({ 176,128 });
	InfoFrameRenderer->SetComponentLocation({ 0, 112 });
	InfoFrameRenderer->SetPivot(EPivotType::TopLeft);
}

ACharacterFrame::~ACharacterFrame()
{
}


void ACharacterFrame::SetSprite(std::string_view SpriteName, int Index)
{
	CharacterImage->SetSprite(SpriteName, Index);
	

}

void ACharacterFrame::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
void ACharacterFrame::BeginPlay()
{
	Super::BeginPlay();
}

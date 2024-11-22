#include "aepch.h"
#include "ThunderBackground.h"

AThunderBackground::AThunderBackground()
{
	YellowSr = CreateDefaultSubobject<USpriteRendererComponent>("ThunderBg");
	YellowSr->SetSprite("Yellow");
	YellowSr->SetComponentScale({ 640,480 });
	YellowSr->SetPivot(EPivotType::TopLeft);

	Sr = CreateDefaultSubobject<USpriteRendererComponent>("ThunderBg");
	Sr->SetSprite("OP_Back.CNS.BMP");
	Sr->SetComponentScale({ 640,480 });
	Sr->SetPivot(EPivotType::TopLeft);
	Sr->SetRemoveColor({ 639,479 });
	Sr->SetRemoveBackground(true);

}

AThunderBackground::~AThunderBackground()
{
}


void AThunderBackground::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	Timer -= _DeltaTime;
	
	if (Timer < 0.0f)
	{
		if (Temp)
		{
			Sr->SetRemoveColor({ 639,479 });
		}
		else
		{

			Sr->SetRemoveColor({ 0,0 });
		}
		Temp = !Temp;
		Timer = 0.2f;
	}
}
void AThunderBackground::BeginPlay()
{
	Super::BeginPlay();
}

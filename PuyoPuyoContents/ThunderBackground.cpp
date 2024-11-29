#include "aepch.h"
#include "ThunderBackground.h"

AThunderBackground::AThunderBackground()
{
	ColorSr = CreateDefaultSubobject<USpriteRendererComponent>("ThunderBg");
	ColorSr->SetSprite("Yellow");
	ColorSr->SetComponentScale({ 640,480 });
	ColorSr->SetPivot(EPivotType::TopLeft);
	ColorSr->SetActive(false);

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
		if (Counter < 4)
		{
			if (Counter %2 ==0)
			{
				Sr->SetSprite("OP_Back.CNS.BMP");
				Sr->SetRemoveColor({ 639,479 });
				ColorSr->SetActive(true);
			}
			else
			{
				Sr->SetRemoveColor(UColor(255, 0, 0, 0));
			}
		}
		else
		{
			if (Temp)
			{
				Sr->SetSprite("OP_Back.CNS.BMP");
				Sr->SetRemoveColor({ 639,479 });
				ColorSr->SetActive(true);
			}
			else
			{
				Sr->SetSprite("OPBackInv");
				Sr->SetRemoveColor({ 0,0 });
				ColorSr->SetActive(false);
			}
			Counter = 0;
			Temp = !Temp;
		}
		Counter++;
		Timer = 0.1f;
	}
}
void AThunderBackground::BeginPlay()
{
	Super::BeginPlay();
}

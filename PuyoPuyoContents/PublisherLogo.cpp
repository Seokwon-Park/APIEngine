#include "aepch.h"
#include "PublisherLogo.h"

APublisherLogo::APublisherLogo()
{
	SetActorLocation(UEngineAPICore::GetEngineWindow().GetWindowSize().Half());

	CKLogo = CreateDefaultSubobject<USpriteRendererComponent>("CompileKorea");
	CKLogo->SetSprite("AAA.CNS.BMP", 0);
	CKLogo->SetComponentScale(UEngineAPICore::GetEngineWindow().GetWindowSize());
}

APublisherLogo::~APublisherLogo()
{
}

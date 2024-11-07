#include "aepch.h"
#include "CarbuncleMenu.h"

ACarbuncleMenu::ACarbuncleMenu()
{
	HeadRenderer = CreateDefaultSubobject<USpriteRendererComponent>("Head");
	BodyRenderer = CreateDefaultSubobject<USpriteRendererComponent>("Head");
	TailRenderer = CreateDefaultSubobject<USpriteRendererComponent>("Head");
}

ACarbuncleMenu::~ACarbuncleMenu()
{
}

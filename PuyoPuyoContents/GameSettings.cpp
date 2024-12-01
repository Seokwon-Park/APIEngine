#include "aepch.h"
#include "GameSettings.h"

GameSettings::GameSettings()
{
	IsCleared.resize(28, false);
}

GameSettings::~GameSettings()
{
}

void GameSettings::Init()
{
	GetInstance().GameMode = EPuyoGameMode::Solo;
	//1인용
	GetInstance().EnemyIndex = 0;
	GetInstance().CurLevel = 1;
	GetInstance().CurStage = 1;
	//현재까지의 경험치
	GetInstance().CurExp = 0;
	//다음 레벨 가는데 남은 경험치량
	GetInstance().RestToNextLevel = ScoreToNextLevel[1];
	//다음 레벨 가는데 필요한 경험치량
	GetInstance().NeedToNextLevel = ScoreToNextLevel[1];
	GetInstance().IsCleared.clear();
	GetInstance().IsCleared.resize(28, false);

	//2인용
	GetInstance().MapIndex = 0;
	GetInstance().DestroyRule = 4;
}

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
	//1�ο�
	GetInstance().EnemyIndex = 0;
	GetInstance().CurLevel = 1;
	GetInstance().CurStage = 1;
	//��������� ����ġ
	GetInstance().CurExp = 0;
	//���� ���� ���µ� ���� ����ġ��
	GetInstance().RestToNextLevel = ScoreToNextLevel[1];
	//���� ���� ���µ� �ʿ��� ����ġ��
	GetInstance().NeedToNextLevel = ScoreToNextLevel[1];
	GetInstance().IsCleared.clear();
	GetInstance().IsCleared.resize(28, false);

	//2�ο�
	GetInstance().MapIndex = 0;
	GetInstance().DestroyRule = 4;
}

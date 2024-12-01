#pragma once

// ���� :
class GameSettings
{
public:
	// constrcuter destructer
	~GameSettings();

	// delete Function
	GameSettings(const GameSettings& _Other) = delete;
	GameSettings(GameSettings&& _Other) noexcept = delete;
	GameSettings& operator=(const GameSettings& _Other) = delete;
	GameSettings& operator=(GameSettings&& _Other) noexcept = delete;

	static GameSettings& GetInstance()
	{
		static GameSettings Instance;
		return Instance;
	}

	static void Init();

	EPuyoGameMode GameMode = EPuyoGameMode::Solo;
	//1�ο�
	int EnemyIndex = 0;
	int CurLevel = 1;
	int CurStage = 1;
	//��������� ����ġ
	long long CurExp = 0;
	//���� ���� ���µ� ���� ����ġ��
	long long RestToNextLevel = ScoreToNextLevel[1];
	//���� ���� ���µ� �ʿ��� ����ġ��
	long long NeedToNextLevel = ScoreToNextLevel[1];
	std::vector<bool> IsCleared;

	//2�ο�
	int MapIndex = 0;
	int DestroyRule = 4;

	std::vector<std::string> PickSound;
protected:

private:
	GameSettings();

};


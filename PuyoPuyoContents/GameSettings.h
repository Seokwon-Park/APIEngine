#pragma once

// 설명 :
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
	//1인용
	int EnemyIndex = 0;
	int CurLevel = 1;
	int CurStage = 1;
	//현재까지의 경험치
	long long CurExp = 0;
	//다음 레벨 가는데 남은 경험치량
	long long RestToNextLevel = ScoreToNextLevel[1];
	//다음 레벨 가는데 필요한 경험치량
	long long NeedToNextLevel = ScoreToNextLevel[1];
	std::vector<bool> IsCleared;

	//2인용
	int MapIndex = 0;
	int DestroyRule = 4;

	std::vector<std::string> PickSound;
protected:

private:
	GameSettings();

};


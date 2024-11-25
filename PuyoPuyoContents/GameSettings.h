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

	EPuyoGameMode GameMode;
	//1인용
	int EnemyIndex = 0;
	int CurLevel = 1;
	int CurStage = 1;
	int CurExp = 0;
	int RestToNextLevel = ScoreToNextLevel[1];

	//2인용
	int MapIndex = 0;
	int DestroyRule = 4;
	std::vector<std::vector<bool>> ClearState;
protected:

private:
	GameSettings();

};


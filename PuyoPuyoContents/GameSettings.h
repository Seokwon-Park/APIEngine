#pragma once

// Ό³Έν :
class GameSettings
{
public:
	// constrcuter destructer
	GameSettings();
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
	int MapIndex = 0;
	

protected:

private:

};


#pragma once

// Ό³Έν :
class APuzzleGameMode : public AGameMode
{
public:
	// constrcuter destructer
	APuzzleGameMode();
	~APuzzleGameMode();

	// delete Function
	APuzzleGameMode(const APuzzleGameMode& _Other) = delete;
	APuzzleGameMode(APuzzleGameMode&& _Other) noexcept = delete;
	APuzzleGameMode& operator=(const APuzzleGameMode& _Other) = delete;
	APuzzleGameMode& operator=(APuzzleGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};


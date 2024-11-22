#pragma once

// Ό³Έν :
class AOptionsGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AOptionsGameMode();
	~AOptionsGameMode();

	// delete Function
	AOptionsGameMode(const AOptionsGameMode& _Other) = delete;
	AOptionsGameMode(AOptionsGameMode&& _Other) noexcept = delete;
	AOptionsGameMode& operator=(const AOptionsGameMode& _Other) = delete;
	AOptionsGameMode& operator=(AOptionsGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	class AOptionsList* OptionsList;
	class AOptionsList* SoundOptionsList;
};


#pragma once
#include <EngineCore/SpriteRendererComponent.h>



// Ό³Έν :
class APlayBackground : public AActor
{
public:
	// constrcuter destructer
	APlayBackground();
	~APlayBackground();

	// delete Function
	APlayBackground(const APlayBackground& _Other) = delete;
	APlayBackground(APlayBackground&& _Other) noexcept = delete;
	APlayBackground& operator=(const APlayBackground& _Other) = delete;
	APlayBackground& operator=(APlayBackground&& _Other) noexcept = delete;

	void SetBackground(EPuyoGameMode _Mode, int _StageIndex = 0);
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
};


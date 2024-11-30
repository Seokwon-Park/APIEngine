#pragma once
#include <EngineCore/SpriteRendererComponent.h>


// 클래스 설명 :
class ABottomBackground : public AActor
{
public:
	// Constrcuter Destructer
	ABottomBackground();
	~ABottomBackground();

	// Delete Function
	ABottomBackground(const ABottomBackground& _Other) = delete;
	ABottomBackground(ABottomBackground&& _Other) noexcept = delete;
	ABottomBackground& operator=(const ABottomBackground& _Other) = delete;
	ABottomBackground& operator=(ABottomBackground&& _Other) noexcept = delete;
	void SetBackground(EPuyoGameMode _Mode, int _StageIndex = 0, bool _IsLeft = true);
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	USpriteRendererComponent* Sr;
};

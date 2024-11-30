#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 클래스 설명 :
class ABottomFrame : public AActor
{
public:
	// Constrcuter Destructer
	ABottomFrame();
	~ABottomFrame();

	// Delete Function
	ABottomFrame(const ABottomFrame& _Other) = delete;
	ABottomFrame(ABottomFrame&& _Other) noexcept = delete;
	ABottomFrame& operator=(const ABottomFrame& _Other) = delete;
	ABottomFrame& operator=(ABottomFrame&& _Other) noexcept = delete;
	
	void SetFrame(EPuyoGameMode _Mode, int _StageIndex = 0);
	void Tick(float _DeltaTime)override;
protected:
	void BeginPlay()override;
private:
	USpriteRendererComponent* Sr;

};

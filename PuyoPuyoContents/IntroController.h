#pragma once
#include <EngineCore/PlayerController.h>

// 클래스 설명 :
class AIntroController :public APlayerController
{
public:
	// Constrcuter Destructer
	AIntroController();
	~AIntroController();

	// Delete Function
	AIntroController(const AIntroController& _Other) = delete;
	AIntroController(AIntroController&& _Other) noexcept = delete;
	AIntroController& operator=(const AIntroController& _Other) = delete;
	AIntroController& operator=(AIntroController&& _Other) noexcept = delete;

	void SkipIntro();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	float Timer = 0.0f;
};

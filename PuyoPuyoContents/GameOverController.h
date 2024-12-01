#pragma once
#include <EngineCore/PlayerController.h>

#include "GameOverCounter.h"

// 클래스 설명 :
class AGameOverController : public APlayerController
{
public:
	// Constrcuter Destructer
	AGameOverController();
	~AGameOverController();

	// Delete Function
	AGameOverController(const AGameOverController& _Other) = delete;
	AGameOverController(AGameOverController&& _Other) noexcept = delete;
	AGameOverController& operator=(const AGameOverController& _Other) = delete;
	AGameOverController& operator=(AGameOverController&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	AGameOverCounter* Counter;

};

#pragma once
#include "PuyoText.h"

// Ό³Έν :
class AGameOverPuyoText : public APuyoText
{
public:
	// constrcuter destructer
	AGameOverPuyoText();
	~AGameOverPuyoText();

	// delete Function
	AGameOverPuyoText(const AGameOverPuyoText& _Other) = delete;
	AGameOverPuyoText(AGameOverPuyoText&& _Other) noexcept = delete;
	AGameOverPuyoText& operator=(const AGameOverPuyoText& _Other) = delete;
	AGameOverPuyoText& operator=(AGameOverPuyoText&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};


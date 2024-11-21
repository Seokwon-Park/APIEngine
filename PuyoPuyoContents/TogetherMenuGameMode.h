#pragma once
#include "TogetherMenu.h"
#include "TogetherMenuBackground.h"

// Ό³Έν :
class ATogetherMenuGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATogetherMenuGameMode();
	~ATogetherMenuGameMode();

	// delete Function
	ATogetherMenuGameMode(const ATogetherMenuGameMode& _Other) = delete;
	ATogetherMenuGameMode(ATogetherMenuGameMode&& _Other) noexcept = delete;
	ATogetherMenuGameMode& operator=(const ATogetherMenuGameMode& _Other) = delete;
	ATogetherMenuGameMode& operator=(ATogetherMenuGameMode&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	ATogetherMenu* Menu;
};


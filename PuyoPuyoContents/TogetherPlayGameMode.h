#pragma once
#include "EngineCore/GameMode.h"

// �ʶ����� �ѿ�ѿ�
class ATogetherPlayGameMode : public AGameMode
{
public:
	// constrcuter destructer
	ATogetherPlayGameMode();
	~ATogetherPlayGameMode();

	// delete Function
	ATogetherPlayGameMode(const ATogetherPlayGameMode& _Other) = delete;
	ATogetherPlayGameMode(ATogetherPlayGameMode&& _Other) noexcept = delete;
	ATogetherPlayGameMode& operator=(const ATogetherPlayGameMode& _Other) = delete;
	ATogetherPlayGameMode& operator=(ATogetherPlayGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
protected:

private:

};


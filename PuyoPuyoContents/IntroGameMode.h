#pragma once
#include "Fader.h"
#include "EngineCore/GameMode.h"

// 설명 :
class AIntroGameMode : public AGameMode
{
public:
	// constrcuter destructer
	AIntroGameMode();
	~AIntroGameMode();

	// delete Function
	AIntroGameMode(const AIntroGameMode& _Other) = delete;
	AIntroGameMode(AIntroGameMode&& _Other) noexcept = delete;
	AIntroGameMode& operator=(const AIntroGameMode& _Other) = delete;
	AIntroGameMode& operator=(AIntroGameMode&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
	void MoveScene();
protected:
	void BeginPlay() override;
private:
	float EventTimer = 0.0f;
	AFader* Fader = nullptr;

	// 순차적으로 실행
	std::queue<std::pair<int, EngineDelegate>> EventQueue;
};


#pragma once
#include <EngineCore/GameMode.h>

// Ό³Έν :
class AMenuGameMode : public AGameMode
{ 
public:
	// constrcuter destructer
	AMenuGameMode();
	~AMenuGameMode();

	// delete Function
	AMenuGameMode(const AMenuGameMode& _Other) = delete;
	AMenuGameMode(AMenuGameMode&& _Other) noexcept = delete;
	AMenuGameMode& operator=(const AMenuGameMode& _Other) = delete;
	AMenuGameMode& operator=(AMenuGameMode&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveToScene(std::string _SceneName);

protected:

private:

};


#pragma once
#include <EngineCore/GameMode.h>

// ���� :
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
	void MoveMenu(FVector2D _Dir);

protected:

private:
	int CurMenuIndex = 0;
	std::vector<class ACarbuncleMenu*> Menus;
};


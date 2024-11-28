#pragma once
#include <EngineCore/InputComponent.h>

// 클래스 설명 :
class AMenuManager : public AActor
{
public:
	// Constrcuter Destructer
	AMenuManager();
	~AMenuManager();

	// Delete Function
	AMenuManager(const AMenuManager& _Other) = delete;
	AMenuManager(AMenuManager&& _Other) noexcept = delete;
	AMenuManager& operator=(const AMenuManager& _Other) = delete;
	AMenuManager& operator=(AMenuManager&& _Other) noexcept = delete;

	void MoveToScene(std::string _SceneName);
	void SelectMenu();
	void MoveMenu(int _Dir);

	virtual void Tick(float _DeltaTime) override;
protected:

	virtual void BeginPlay() override;
private:
	bool LockControl = false;
	bool IsMoving = false;
	const int MenuSize = 5;
	float InputDelay = 0.2f;
	float InputTimer = 0.0f;
	int CurMenuIndex = 0;
	std::vector<class ACarbuncleMenu*> Menus;
	std::vector<std::string> LevelNames;
	std::vector<std::string> BGMNames;

	UInputComponent* Input;
};

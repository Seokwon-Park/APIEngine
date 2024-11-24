#pragma once
#include "EnemySelect.h"
#include "CharacterFrame.h"

// Ό³Έν :
class AEnemySelector : public AActor
{
public:
	// constrcuter destructer
	AEnemySelector();
	~AEnemySelector();

	// delete Function
	AEnemySelector(const AEnemySelector& _Other) = delete;
	AEnemySelector(AEnemySelector&& _Other) noexcept = delete;
	AEnemySelector& operator=(const AEnemySelector& _Other) = delete;
	AEnemySelector& operator=(AEnemySelector&& _Other) noexcept = delete;

	void SetupSelector(int _Size, int _StartRange, ACharacterFrame* Frame);
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	int Level = 0;
	int Size = 0;
	int CurIndex = 0;
	float Timer = 0.0f;
	float Delay = 0.01f;
	float SelectTimer = 0.0f;
	std::vector<AEnemySelect*> EnemyList;
	ACharacterFrame* Frame;
};


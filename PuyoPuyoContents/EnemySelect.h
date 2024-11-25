#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// Ό³Έν :
class AEnemySelect : public AActor
{
public:
	// constrcuter destructer
	AEnemySelect();
	~AEnemySelect();

	// delete Function
	AEnemySelect(const AEnemySelect& _Other) = delete;
	AEnemySelect(AEnemySelect&& _Other) noexcept = delete;
	AEnemySelect& operator=(const AEnemySelect& _Other) = delete;
	AEnemySelect& operator=(AEnemySelect&& _Other) noexcept = delete;

	inline int GetIndex() { return Index; }
	inline void SetOn() { Sr->SetSprite("EnemySelectOn", Index); }
	inline void SetOff() { Sr->SetSprite("EnemySelectOff", Index); }
	inline void Setup(int _Index) { Index = _Index; }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	bool IsOn = false;
	int Index = 0;
	USpriteRendererComponent* Sr;
	
};


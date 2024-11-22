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

	void SetOn() { Sr->SetSprite("EnemySelectOn", Index); }
	void SetOff() { Sr->SetSprite("EnemySelectOff", Index); }
	void Setup(int _Index) { Index = _Index; }
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	int Index = 0;
	USpriteRendererComponent* Sr;
};


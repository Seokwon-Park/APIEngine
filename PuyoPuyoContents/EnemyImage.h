#pragma once
#include <EngineCore/SpriteRendererComponent.h>


// Ό³Έν :
class AEnemyImage : public AActor
{
public:
	// constrcuter destructer
	AEnemyImage();
	~AEnemyImage();

	// delete Function
	AEnemyImage(const AEnemyImage& _Other) = delete;
	AEnemyImage(AEnemyImage&& _Other) noexcept = delete;
	AEnemyImage& operator=(const AEnemyImage& _Other) = delete;
	AEnemyImage& operator=(AEnemyImage&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	USpriteRendererComponent* Sr;
private:
};


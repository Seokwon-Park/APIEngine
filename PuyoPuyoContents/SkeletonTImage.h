#pragma once
#include "EnemyImage.h"

// Ό³Έν :
class ASkeletonTImage : public AEnemyImage
{
public:
	// constrcuter destructer
	ASkeletonTImage();
	~ASkeletonTImage();

	// delete Function
	ASkeletonTImage(const ASkeletonTImage& _Other) = delete;
	ASkeletonTImage(ASkeletonTImage&& _Other) noexcept = delete;
	ASkeletonTImage& operator=(const ASkeletonTImage& _Other) = delete;
	ASkeletonTImage& operator=(ASkeletonTImage&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};


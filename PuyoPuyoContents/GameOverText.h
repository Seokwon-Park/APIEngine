#pragma once

// 클래스 설명 :
class AGameOverText : public AActor
{
public:
	// Constrcuter Destructer
	AGameOverText();
	~AGameOverText();

	// Delete Function
	AGameOverText(const AGameOverText& _Other) = delete;
	AGameOverText(AGameOverText&& _Other) noexcept = delete;
	AGameOverText& operator=(const AGameOverText& _Other) = delete;
	AGameOverText& operator=(AGameOverText&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
	const std::vector<int> SpriteIndex = { 0,1,2,3,4,5,3,6 };
	const std::vector<FVector2D> SpriteSize= { FVector2D( 72, 64 ),FVector2D( 56, 64 ),FVector2D( 88, 64 ),
	FVector2D( 56, 64 ),FVector2D( 64, 64 ),FVector2D( 56, 64 ),FVector2D(56, 64),FVector2D( 56, 64 )};

	float Timer = 0.0f;
	std::vector<USpriteRendererComponent*> Sr;
};

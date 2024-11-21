#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// 설명 :


class APlayFrame : public AActor
{
public:
	// constrcuter destructer
	APlayFrame();
	~APlayFrame();

	// delete Function
	APlayFrame(const APlayFrame& _Other) = delete;
	APlayFrame(APlayFrame&& _Other) noexcept = delete;
	APlayFrame& operator=(const APlayFrame& _Other) = delete;
	APlayFrame& operator=(APlayFrame&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	void SetFrame(EPuyoGameMode _Mode, int _StageIndex = 0);
protected:
	virtual void BeginPlay() override;

private:


	//프레임 명칭, 좌표, 크기
	const std::string FramePartName[7] = { "Head", "Center", "Left", "InnerLeft", "Right", "InnerRight", "Tail" };
	const FVector2D FrameLocation[7] = { FVector2D(0,0),FVector2D(304,64),FVector2D(0,32),FVector2D(224,32),FVector2D(608,32),FVector2D(400,32),FVector2D(0,416) };
	const FVector2D FrameScale[7] = { FVector2D(640,32),FVector2D(32,128),FVector2D(32,384),FVector2D(16,384),FVector2D(32,384),FVector2D(16,384),FVector2D(0,416) };

	std::vector<USpriteRendererComponent*> FrameSr;
	USpriteRendererComponent* HeadSr;
	USpriteRendererComponent* CenterSr;
	USpriteRendererComponent* LeftSideSr;
	USpriteRendererComponent* InnerLeftSideSr;
	USpriteRendererComponent* RightSideSr;
	USpriteRendererComponent* InnerRightSideSr;
	USpriteRendererComponent* TailSr;
};


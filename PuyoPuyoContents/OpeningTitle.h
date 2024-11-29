#pragma once

// 설명 :
class AOpeningTitle : public AActor
{
public:
	// constrcuter destructer
	AOpeningTitle();
	~AOpeningTitle();

	// delete Function
	AOpeningTitle(const AOpeningTitle& _Other) = delete;
	AOpeningTitle(AOpeningTitle&& _Other) noexcept = delete;
	AOpeningTitle& operator=(const AOpeningTitle& _Other) = delete;
	AOpeningTitle& operator=(AOpeningTitle&& _Other) noexcept = delete;

	void Init();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	const float Height = 132.0f;
	const FVector2D StartPos = FVector2D(270.0f, Height);
	const std::vector<FVector2D> MidPos= { {-20.0f, Height}, {-20.0f, Height}, {500.0f, Height}, {500.0f, Height} }; // 중간 위치
	const std::vector<FVector2D> TargetPos= { {248.0f, Height}, {356.0f, Height}, {24.0f, Height}, {132.0f, Height} }; // 최종 위치
	const std::vector<float> Delays = { 0.0f, 0.3f, 0.0f, 0.3f }; // 각 글자의 이동 시작 지연 시간
	std::vector<bool> IsLocated = { false,false,false,false };
	bool IsMoveEnd = false;

	float Duration = 0.5f;
	float Timer = 0.0f;
	float Duration2 = 0.3f;
	float Timer2 = 0.0f;
	float Duration3 = 0.3f;
	float Timer3 = 0.0f;

	std::vector<USpriteRendererComponent*> Sr;
	USpriteRendererComponent* TsuRenderer;
	USpriteRendererComponent* TitlePuyo1;
	USpriteRendererComponent* TitlePuyo2;
	USpriteRendererComponent* TitlePuyo3;
	UAnimatorComponent* TitleAnim;
	UAnimatorComponent* TitleAnim2;
};


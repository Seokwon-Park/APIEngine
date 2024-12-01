#pragma once
#include "PuyoText.h"
#include "NameText.h"
#include <EngineCore/InputComponent.h>

enum class EResultStep
{
	Idle,
	Show,
	Adjust,
	Wait,
};
// Ό³Έν :
class AResultUI : public AActor
{
public:
	// constrcuter destructer
	AResultUI();
	~AResultUI();

	// delete Function
	AResultUI(const AResultUI& _Other) = delete;
	AResultUI(AResultUI&& _Other) noexcept = delete;
	AResultUI& operator=(const AResultUI& _Other) = delete;
	AResultUI& operator=(AResultUI&& _Other) noexcept = delete;

	long long CalculateBonusScore(int _Time);
	void SetupResult(int _ElapsedTime, APuyoText* _PlayerScore);
	void Idle();
	void ShowText();
	void AdjustScore();
	void NextGame();
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	bool CheckPoint1 = false;
	bool CheckPoint2 = false;
	bool CheckPoint3 = false;
	float FlickTimer = 0.0f;
	float FlickDelay = 0.2f;

	float FlickTimer2 = 0.0f;
	float FlickDelay2 = 0.1f;
	float CountingTimer = 0.0f;


	long long DBonus = 0;
	long long DExp = 0;
	long long Elapsed = 0;
	long long Bonus = 0;
	long long StagePoint = 0;
	long long RestPoint = 0;
	APuyoText* PlayerScore = nullptr;
	EResultStep CurStep = EResultStep::Idle;
	//Left Panel;
	FVector2D LeftOffset;
	APuyoText* YouWin;
	ANameText* PlayTime;
	APuyoText* ElapsedTime;
	ANameText* SecText;
	ANameText* BonusText;
	APuyoText* BonusScoreText;
	ANameText* PtsText;

	//Right Panel
	FVector2D RightOffset;
	
	ANameText* StageText1;
	ANameText* StageText2;
	APuyoText* StagePointText;
	ANameText* PtsText2;
	
	ANameText* RestText1;
	ANameText* RestText2;
	APuyoText* RestPointText;
	ANameText* PtsText3;

	APuyoText* LevelUpText;

	UInputComponent* Input;

};


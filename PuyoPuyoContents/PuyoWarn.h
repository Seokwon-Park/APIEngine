#pragma once
#include <EngineCore/SpriteRendererComponent.h>

enum class EWarningState {
	Idle,        // 대기 상태
	Gathering,   // 특정 위치로 이동 중
	Calculate,     // 모인 상태 유지
	Returning    // 원래 자리로 복귀 중
};
// 설명 :
class APuyoWarn : public AActor
{
public:
	// constrcuter destructer
	APuyoWarn();
	~APuyoWarn();

	// delete Function
	APuyoWarn(const APuyoWarn& _Other) = delete;
	APuyoWarn(APuyoWarn&& _Other) noexcept = delete;
	APuyoWarn& operator=(const APuyoWarn& _Other) = delete;
	APuyoWarn& operator=(APuyoWarn&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
	void UpdateWarning();
	bool CalcWarn(const int _SpriteIndex, FVector2D& _Offset, int& _CurIndex, int& _Left);
	bool HasWarn() { return WarnNum > 0; }
	void SetWarnNum(int _Value) { WarnNum = _Value; }
	void AddWarnNum(int _Value) { WarnNum += _Value; }
	void SubWarnNum(int _Value) { WarnNum -= _Value; }
	int GetWarnNum() const { return WarnNum; }

protected:
	virtual void BeginPlay() override;

private:
	//예고 뿌요 단위
	const int WarnUnit[6] = { 1,6,30, 200, 300, 420 };
	FVector2D TargetPos[6];
	FVector2D StartPos[6];
	EWarningState State = EWarningState::Idle;

	int WarnNum = 0;
	float Timer = 0.0f;
	float Duration = 0.2f;

	std::vector<USpriteRendererComponent*> Warnings;

};


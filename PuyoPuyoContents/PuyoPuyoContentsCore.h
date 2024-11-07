#pragma once
#include <EngineCore/EngineAPICore.h>

// 설명 :
class PuyoPuyoContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	PuyoPuyoContentsCore();
	~PuyoPuyoContentsCore();

	// delete Function
	PuyoPuyoContentsCore(const PuyoPuyoContentsCore& _Other) = delete;
	PuyoPuyoContentsCore(PuyoPuyoContentsCore&& _Other) noexcept = delete;
	PuyoPuyoContentsCore& operator=(const PuyoPuyoContentsCore& _Other) = delete;
	PuyoPuyoContentsCore& operator=(PuyoPuyoContentsCore&& _Other) noexcept = delete;

protected:
	// UContentsCore을(를) 통해 상속됨
	void BeginPlay() override;
	void SetupCarbuncleSprite();
	void SetupPuyoSprite();
	void Tick() override;

private:


};


#pragma once
#include <EngineCore/EngineAPICore.h>

// ���� :
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
	// UContentsCore��(��) ���� ��ӵ�
	void BeginPlay() override;
	void SetupCarbuncleSprite();
	void SetupPuyoSprite();
	void Tick() override;

private:


};


#pragma once
#include <EngineCore/EngineAPICore.h>

// ���� :
class UGameContentsCore : public UContentsCore
{
public:
	// constrcuter destructer
	UGameContentsCore();
	~UGameContentsCore();

	// delete Function
	UGameContentsCore(const UGameContentsCore& _Other) = delete;
	UGameContentsCore(UGameContentsCore&& _Other) noexcept = delete;
	UGameContentsCore& operator=(const UGameContentsCore& _Other) = delete;
	UGameContentsCore& operator=(UGameContentsCore&& _Other) noexcept = delete;

protected:
	// UContentsCore��(��) ���� ��ӵ�
	void BeginPlay() override;
	void Tick() override;
private:


};


#pragma once
#include <EngineCore/EngineAPICore.h>

// 설명 :
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
	// UContentsCore을(를) 통해 상속됨
	void BeginPlay() override;
	void Tick() override;
private:


};


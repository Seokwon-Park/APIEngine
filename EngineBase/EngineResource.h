#pragma once
#include "EnginePath.h"

// Ό³Έν :
class UEngineResource : public UObject
{
public:
	// constrcuter destructer
	UEngineResource();
	~UEngineResource();

	// delete Function
	UEngineResource(const UEngineResource& _Other) = delete;
	UEngineResource(UEngineResource&& _Other) noexcept = delete;
	UEngineResource& operator=(const UEngineResource& _Other) = delete;
	UEngineResource& operator=(UEngineResource&& _Other) noexcept = delete;

protected:

private:
	UEnginePath Path;
};


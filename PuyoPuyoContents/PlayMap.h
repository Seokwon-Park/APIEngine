#pragma once
#include <EngineCore/SpriteRendererComponent.h>

// ���� :
class APlayMap : public AActor
{
public:
	// constrcuter destructer
	APlayMap();
	~APlayMap();

	// delete Function
	APlayMap(const APlayMap& _Other) = delete;
	APlayMap(APlayMap&& _Other) noexcept = delete;
	APlayMap& operator=(const APlayMap& _Other) = delete;
	APlayMap& operator=(APlayMap&& _Other) noexcept = delete;

protected:

private:
	USpriteRendererComponent* Sr;
};


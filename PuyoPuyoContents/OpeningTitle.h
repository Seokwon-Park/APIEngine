#pragma once

// Ό³Έν :
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

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:
	std::vector<USpriteRendererComponent*> Sr;
};


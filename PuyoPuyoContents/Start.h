#pragma once

// Ό³Έν :
class AStart : public AActor
{
public:
	// constrcuter destructer
	AStart();
	~AStart();

	// delete Function
	AStart(const AStart& _Other) = delete;
	AStart(AStart&& _Other) noexcept = delete;
	AStart& operator=(const AStart& _Other) = delete;
	AStart& operator=(AStart&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};


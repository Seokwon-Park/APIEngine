#pragma once

// Ό³Έν :
class ATower : public AActor
{
public:
	// constrcuter destructer
	ATower();
	~ATower();

	// delete Function
	ATower(const ATower& _Other) = delete;
	ATower(ATower&& _Other) noexcept = delete;
	ATower& operator=(const ATower& _Other) = delete;
	ATower& operator=(ATower&& _Other) noexcept = delete;

	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;

private:

};


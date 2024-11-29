#pragma once

// Ŭ���� ���� :
class AOpeningParticle : public AActor
{
public:
	// Constrcuter Destructer
	AOpeningParticle();
	~AOpeningParticle();

	// Delete Function
	AOpeningParticle(const AOpeningParticle& _Other) = delete;
	AOpeningParticle(AOpeningParticle&& _Other) noexcept = delete;
	AOpeningParticle& operator=(const AOpeningParticle& _Other) = delete;
	AOpeningParticle& operator=(AOpeningParticle&& _Other) noexcept = delete;


	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:


};

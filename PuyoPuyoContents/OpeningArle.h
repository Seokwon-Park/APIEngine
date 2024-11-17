#pragma once

// 클래스 설명 :
class AOpeningArle : public AActor
{
public:
	// Constrcuter Destructer
	AOpeningArle();
	~AOpeningArle();

	// Delete Function
	AOpeningArle(const AOpeningArle& _Other) = delete;
	AOpeningArle(AOpeningArle&& _Other) noexcept = delete;
	AOpeningArle& operator=(const AOpeningArle& _Other) = delete;
	AOpeningArle& operator=(AOpeningArle&& _Other) noexcept = delete;

	void Tick(float _DeltaTime) override;
protected:
	void BeginPlay()override;


private:

};

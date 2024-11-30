#pragma once

// Ŭ���� ���� :
class AGameOverCounter :public AActor
{
public:
	// Constrcuter Destructer
	AGameOverCounter();
	~AGameOverCounter();

	// Delete Function
	AGameOverCounter(const AGameOverCounter& _Other) = delete;
	AGameOverCounter(AGameOverCounter&& _Other) noexcept = delete;
	AGameOverCounter& operator=(const AGameOverCounter& _Other) = delete;
	AGameOverCounter& operator=(AGameOverCounter&& _Other) noexcept = delete;
	virtual void Tick(float _DeltaTime) override;
protected:
	virtual void BeginPlay() override;
private:
    std::vector<std::vector<std::vector<int>>> NumberPatterns = {
        // ���� 1
        {
            {0, 0, 1, 0, 0},
            {0, 1, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 1, 1, 0},
        },
        // ���� 2
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0},
            {0, 1, 0, 0, 0},
            {1, 1, 1, 1, 1},
        },
        // ���� 3
        {
            {0, 1, 1, 1, 0},
            {1, 0, 0, 0, 1},
            {0, 0, 0, 0, 1},
            {0, 1, 1, 1, 0},
            {0, 0, 0, 0, 1},
            {1, 0, 0, 0, 1},
            {0, 1, 1, 1, 0 },
        }
        // 4~10�� �̿� �����ϰ� ����
    };

    std::vector<std::vector<class APuyo*>> Board;
};

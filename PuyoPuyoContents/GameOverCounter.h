#pragma once
#include "GameOverPuyo.h"
#include "GameOverText.h"
#include "GameOverBackground.h"

// 클래스 설명 :
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
	void UpdateNumber();
    inline void SetupCounter(AGameOverText* _Text, AGameOverBackground* _Background)
    {
        Text = _Text;
        BG = _Background;
    }

    inline int GetCount() const { return Count; }

    void SkipTime();
protected:
	virtual void BeginPlay() override;
private:
    AGameOverPuyo* GameOverPuyo = nullptr;
    AGameOverText* Text = nullptr;
    AGameOverBackground* BG = nullptr;
    std::vector<EPuyoColor> Colors = { EPuyoColor::Red,EPuyoColor::Green,EPuyoColor::Blue,EPuyoColor::Yellow,EPuyoColor::Purple };
    std::vector<std::vector<std::vector<int>>> NumberPatterns = { 
        // 숫자 0
       {
           {0, 0, 1, 1, 1, 0, 0},
           {0, 1, 0, 0, 0, 1, 0},
           {0, 1, 0, 0, 0, 1, 0},
           {0, 1, 0, 0, 0, 1, 0},
           {0, 1, 0, 0, 0, 1, 0},
           {0, 1, 0, 0, 0, 1, 0},
           {0, 0, 1, 1, 1, 0, 0},
       },
        // 숫자 1
        {
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
        // 숫자 2
        {
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 1, 0},
        },
        // 숫자 3
        {
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
        // 숫자 4
        {
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0},
            {0, 0, 1, 0, 1, 0, 0},
            {0, 1, 0, 0, 1, 0, 0},
            {0, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 1, 0, 0},
        },
        // 숫자 5
        {
            {0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
                {
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 0, 0},
            {0, 1, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
                {
            {0, 1, 1, 1, 1, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0},
        },
                {
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
                {
            {0, 0, 1, 1, 1, 0, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 1, 0},
            {0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 0, 0},
        },
                {
            {0, 1, 0, 0, 1, 1, 0},
            {1, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 1, 0, 0, 1},
            {0, 1, 0, 0, 1, 1, 0},
        },
    };

    std::vector<std::vector<class APuyo*>> Board;
    float Timer = 0.0f;
    int Count = 10;
    bool IsGameOver = false;


};

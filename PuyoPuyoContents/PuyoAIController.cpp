#include "aepch.h"
#include "PuyoAIController.h"

APuyoAIController::APuyoAIController()
{
}

APuyoAIController::~APuyoAIController()
{
}


int dx[4] = { 0,-1,0,1 };
int dy[4] = { -1,0,1,0 };

//우선은 놓을 수 있는 경우는
//위를 향할때 6군데
//아래를 향할때 6군데
//오른쪽을향할때 5군데
//왼쪽을 향할때 5군대
//
//총 22가지의 경우의 수가 있다.
//
//높이별 점수 부여
//보드에 각 칸에 대해 점수를 부여한다.
//각칸에 대한 색깔별 가중치 점수를 부여
//위의 22가지 경우를 대입해가며 비교,
//
//별 차이 없으면 어캄 ? 걍 대충 하셈.
void APuyoAIController::CalculateBoard()
{
	for (int i = BoardState.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < BoardState[0].size(); j++)
		{
			std::fill(EvaluateBoard[i][j].begin(), EvaluateBoard[i][j].end(), 0);
		}
	}

	std::vector<int> BlockColors = Board->GetBlockInfo();
	std::vector<int> MaxY(6);
	for (int i = BoardState.size() - 1; i >= 0; i--)
	{
		for (int j = 0; j < BoardState[0].size(); j++)
		{
			//if (BoardState[i][j] == -1)
			//{
			//	TargetX = j;
			//	TargetY = i;
			//	return;
			//}
			if (BoardState[i][j] == -1)
			{
				MaxY[j] = FEngineMath::Max(MaxY[j], i);
				for (int dir = 0; dir < 4; dir++)
				{
					int tx = j + dx[dir];
					int ty = i + dy[dir];
					if (ty < 0 || tx < 0 || ty >= 13 || tx >= 6)continue;
					if (BoardState[ty][tx] != -1)
					{
						EvaluateBoard[i][j][BoardState[ty][tx]]++;
					}
				}
			}
		}
	}

	int EvaluateScore = 0;


}

void APuyoAIController::BeginPlay()
{
	Super::BeginPlay();

	Board = GetActor<APuyoBoard>();
	EvaluateBoard.resize(Board->GetPuyoBoardSize().Y, std::vector<std::vector<int>>(Board->GetPuyoBoardSize().X,
		std::vector<int>(5, 0)));
}

void APuyoAIController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
		
	/*if (Board->GetMainPuyoCoord().Y >= TargetY)
	{
		State = EPuyoAIState::Calculation;
	}*/

	if (State == EPuyoAIState::Calculation)
	{
		BoardState = Board->GetBoardState();
		CalculateBoard();
		State = static_cast<EPuyoAIState>(RandomDevice.GetRandomInt(1, 4));
		return;
	}
	

	if (Board->GetMainPuyoCoord().X < TargetX)
	{
		Board->PuyoMoveLR({ 1,0 });
	}
	else if(Board->GetMainPuyoCoord().X >TargetX)
	{
		Board->PuyoMoveLR({ -1,0 });
	}
	Delay -= _DeltaTime;
	//Do Sth
	if (Delay > 0.0f) return;
	Board->PuyoForceDown();
	Delay = 0.1f;


	//switch (State)
	//{
	//case EPuyoAIState::Down:
	//	break;
	//case EPuyoAIState::Left:
	//	Board->PuyoMoveLR({-1,0});
	//	break;
	//case EPuyoAIState::Right:
	//	Board->PuyoMoveLR({ 1,0});
	//	break;
	//case EPuyoAIState::Rotate:
	//	Board->Rotate(true);
	//	break;
	//default:
	//	break;
	//}
	//Board->PuyoForceDown();

}


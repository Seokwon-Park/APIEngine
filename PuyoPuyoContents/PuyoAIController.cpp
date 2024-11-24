#include "aepch.h"
#include "PuyoAIController.h"

APuyoAIController::APuyoAIController()
{
}

APuyoAIController::~APuyoAIController()
{
}


void APuyoAIController::ReceiveBlockColors()
{
	BlockColors = Board->GetBlockInfo();
}

//�켱�� ���� �� �ִ� ����
//���� ���Ҷ� 6����
//�Ʒ��� ���Ҷ� 6����
//�����������Ҷ� 5����
//������ ���Ҷ� 5����
//
//�� 22������ ����� ���� �ִ�.
//
//���̺� ���� �ο�
//���忡 �� ĭ�� ���� ������ �ο��Ѵ�.
//��ĭ�� ���� ���� ����ġ ������ �ο�
//���� 22���� ��츦 �����ذ��� ��,
//
//�� ���� ������ ��į ? �� ���� �ϼ�.
void APuyoAIController::CalculateBoard()
{
	auto [Rows, Cols] = Board->GetPuyoBoardSize();

	for (int i = Cols - 1; i >= 0; i--)
	{
		for (int j = 0; j < Rows; j++)
		{
			//�������� ����ġ�� �ο�.
			std::fill(EvaluateBoard[i][j].begin(), EvaluateBoard[i][j].end(), i);
		}
	}

	std::vector<int> BottomY(6);
	for (int i = Cols - 1; i >= 0; i--)
	{
		for (int j = 0; j < Rows; j++)
		{
			//if (BoardState[i][j] == -1)
			//{
			//	TargetX = j;
			//	TargetY = i;
			//	return;
			//}
			if (BoardState[i][j] == -1)
			{
				BottomY[j] = FEngineMath::Max(BottomY[j], i);
				for (int dir = 0; dir < 4; dir++)
				{
					int tx = j + Dx[dir];
					int ty = i + Dy[dir];
					if (ty < 0 || tx < 0 || ty >= 13 || tx >= 6)continue;
					if (BoardState[ty][tx] != -1)
					{

						EvaluateBoard[i][j][BoardState[ty][tx]] += CalculateBFS(tx, ty);
					}
				}
			}
		}
	}

	int EvaluateScore = 0;
	for (int X = 0; X < BoardState[0].size(); X++)
	{
		int Result = 0;
		int Y = BottomY[X];
		if (Board->IsInBoard(X, Y))
		{
			Result += EvaluateBoard[Y][X][BlockColors[0]];
		}
		if (Board->IsInBoard(X, Y - 1))
		{
			Result += EvaluateBoard[Y - 1][X][BlockColors[1]];
		}
		if (Result >= EvaluateScore)
		{
			EvaluateScore = Result;
			TargetX = X;
			TargetY = Y;
			TargetDir = 0;
		}
		if (Board->IsInBoard(X, Y))
		{
			Result += EvaluateBoard[Y][X][BlockColors[1]];
		}
		if (Board->IsInBoard(X, Y - 1))
		{
			Result += EvaluateBoard[Y - 1][X][BlockColors[0]];
		}
		if (Result >= EvaluateScore)
		{
			EvaluateScore = Result;
			TargetX = X;
			TargetY = Y;
			TargetDir = 2;
		}
	}

	for (int X = 0; X < 5; X++)
	{
		int Result = 0;
		int Y = BottomY[X];
		Result = EvaluateBoard[Y][X][BlockColors[0]] + EvaluateBoard[BottomY[X + 1]][X][BlockColors[1]];
		if (Result >= EvaluateScore)
		{
			EvaluateScore = Result;
			TargetX = X;
			TargetY = Y;
			TargetDir = 3;
		}
		Result = EvaluateBoard[Y][X][BlockColors[1]] + EvaluateBoard[BottomY[X + 1]][X][BlockColors[0]];
		if (Result >= EvaluateScore)
		{
			EvaluateScore = Result;
			TargetX = X + 1;
			TargetY = BottomY[X + 1];
			TargetDir = 1;
		}
	}

}

void APuyoAIController::DebugEvaluateBoard()
{
	FVector2D Pos = Board->GetActorLocation();
	for (int i = 0; i < 13; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			for (int color = 0; color < 6; color++)
			{
				EngineDebugHelper::PushString(std::to_string(EvaluateBoard[i][j][color]), Pos + FVector2D(j * 36 + (color % 3) * 8, i * 36 + (color / 3) * 16));
			}
		}
	}

}

int APuyoAIController::CalculateBFS(int _X, int _Y)
{
	auto [Cols, Rows] = Board->GetPuyoBoardSize();
	std::vector<std::vector<bool>> Visited(Rows, std::vector<bool>(Cols, false));
	// ���� BFS �Լ��� ����
	std::queue<FIntPoint> Queue;
	// Todo : �꿡���� 4��� �ٸ����� ���� �� �ְ� �� ����
	// ���� ��ġ�� �ѿ�� ������ ���� �ѿ��� ��ǥ���� ����Ǵ� 
	// �ӽ� ���� ����� 4���� ũ�� ���Ÿ�Ͽ� ����
	std::vector<FIntPoint> Temp;
	// ��ó�� ���ػѿ䵵 ���� �����س��� �ӽ� ���� ����� 4���� ũ�� ���� �����.
	std::vector<FIntPoint> Garbages;

	Queue.push({ _X,_Y });
	Visited[_Y][_X] = true;
	int Color = BoardState[_Y][_X];
	int Linked = 8;
	while (!Queue.empty())
	{
		auto [CurX, CurY] = Queue.front();
		Queue.pop();
		for (int Dir = 0; Dir < 4; Dir++)
		{
			int TargetX = CurX + Dx[Dir];
			int TargetY = CurY + Dy[Dir];
			if (!Board->IsInBoard(TargetX, TargetY) || true == Visited[TargetY][TargetX])
			{
				continue;
			}
			int TargetColor = BoardState[TargetY][TargetX];
			if (Color != TargetColor)
			{
				continue;
			}
			Queue.push(FIntPoint(TargetX, TargetY));
			Visited[TargetY][TargetX] = true;
			Linked <<= 1;
		}
	}

	return Linked;
}

void APuyoAIController::BeginPlay()
{
	Super::BeginPlay();

	Board = GetActor<APuyoBoard>();
	EvaluateBoard.resize(Board->GetPuyoBoardSize().Y, std::vector<std::vector<int>>(Board->GetPuyoBoardSize().X,
		std::vector<int>(6, 0)));
	Board->PuyoCreateDelegate += std::bind(&APuyoAIController::ReceiveBlockColors, this);
	Board->PuyoCreateDelegate += std::bind([=]() {State = EPuyoAIState::Calculation; });
}

void APuyoAIController::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	BoardState = Board->GetBoardState();
	//DebugEvaluateBoard();
	auto [Point, Dir] = Board->GetMainPuyoInfo();
	if (State == EPuyoAIState::Calculation)
	{
		CalculateBoard();
		State = static_cast<EPuyoAIState>(RandomDevice.GetRandomInt(1, 4));
		return;
	}

	if (Point.X < TargetX)
	{
		Board->PuyoMoveLR({ 1,0 });
	}
	else if (Point.X > TargetX)
	{
		Board->PuyoMoveLR({ -1,0 });
	}

	if (Dir != TargetDir)
	{
		Board->Rotate(true);
		Delay = 0.1f;
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


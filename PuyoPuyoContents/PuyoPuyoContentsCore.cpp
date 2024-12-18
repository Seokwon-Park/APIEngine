#include "aepch.h"
#include "PuyoPuyoContentsCore.h"

#include "DummyPawn.h"
#include "IntroGameMode.h"

#include "MenuGameMode.h"
#include "SoloMenuGameMode.h"
#include "TogetherMenuGameMode.h"

#include "PuzzleGameMode.h"
#include "SoloPlayGameMode.h"
#include "TogetherPlayGameMode.h"
#include "TrainingPlayGameMode.h"

#include "OptionsGameMode.h"
#include "GameOverGameMode.h"

#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/AudioManager.h>
#include <EnginePlatform/EngineSound.h>


PuyoPuyoContentsCore::PuyoPuyoContentsCore()
{
}

PuyoPuyoContentsCore::~PuyoPuyoContentsCore()
{
}

void PuyoPuyoContentsCore::BeginPlay()
{
	EngineDebugHelper::SetShowFPS(false);

	UEngineAPICore::GetCore()->LoadResources();

	//USoundManager::GetInstance().FindSound("OPTheme.mp3")->Play();

	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {0,0 }, { 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {32,0 }, { 32, 32 } });
	//
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {0,160 }, { 48, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {48,160 }, { 48, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {96,160 }, { 40, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {136,160 }, { 40, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {176,160 }, { 48, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {224,160 }, { 56, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {280,160 }, { 56, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {272,192 }, { 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("MiniCar", "KAR.CNS.BMP", { {304,192 }, { 32, 32 } });

	//Star
	UImageManager::GetInstance().InsertCustomSpriteData("Star", "PUYO_RY.CNS.BMP", { {384,32 }, { 16, 16 } });

	//Intro
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOEYE", "OP_PUYO.CNS.BMP", { {0,0 }, { 144, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOBOT", "OP_PUYO.CNS.BMP", { {0,240 }, { 640, 240 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOTOP", "OP_PUYO.CNS.BMP", { {160,0 }, { 480, 240 } });

	//인트로 카벙클
	UImageManager::GetInstance().InsertCustomSpriteData("OPCAR", "OP_KAR.CNS.BMP", { {0,0 }, { 448, 480 } });
	UImageManager::GetInstance().CuttingSpriteCustom("OPCARJEWEL", "OP_KAR.CNS.BMP", { 448,0 }, { 640,72 }, { 48,72 });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCARJEWEL", "OP_KAR.CNS.BMP", { { 0,220 }, { 48,72 } });

	//인트로 아르르 나쟈
	UImageManager::GetInstance().InsertCustomSpriteData("OPARLE", "OP_ARLE.CNS.BMP", { {0,0 }, { 640, 480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {0,480 }, { 144, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {144,480 }, { 176, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {320,480 }, { 144, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {464,480 }, { 176, 104 } });

	//Todo:순서 어케?
	//인트로 동전
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {0,0 }, { 224, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {224,0 }, { 160, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {384,0 }, { 160, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {544,0 }, { 96, 224 } });

	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {0,224 }, { 96, 224 } });
	//옆면
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {96,224 }, { 32, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {128,224 }, { 96, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {224,224 }, { 160, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {384,224 }, { 160, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_COIN.CNS.BMP", { {544,224 }, { 96, 224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCOIN", "OP_ETC.CNS.BMP", { {0,0 }, { 224, 224 } });

	//게임 타이틀
	UImageManager::GetInstance().InsertCustomSpriteData("PU", "OP_ETC.CNS.BMP", { {224,0 }, { 108, 96 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Yo", "OP_ETC.CNS.BMP", { {332,0 }, { 116, 96 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Tsu", "OP_ETC.CNS.BMP", { {448,0 }, { 176, 144 } });
	UImageManager::GetInstance().CuttingSpriteCustom("TitlePuyoG", "OP_ETC.CNS.BMP", { 224,96 }, { 368, 144 }, { 48,48 });
	UImageManager::GetInstance().CuttingSpriteCustom("TitlePuyoR", "OP_ETC.CNS.BMP", { 224,144 }, { 368, 176 }, { 48,32 });
	UImageManager::GetInstance().InsertCustomSpriteData("Particle", "OP_ETC.CNS.BMP", { {332,0 }, { 176, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Particle", "OP_ETC.CNS.BMP", { {332,0 }, { 176, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Particle", "OP_ETC.CNS.BMP", { {332,0 }, { 176, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Compile", "OP_ETC.CNS.BMP", { {224,176 }, { 416, 32 } });

	//세피아 변환
	for (int i = 0; i < 6; i++)
	{
		UImageManager::GetInstance().ImageToSepia("SepiaRoll" + std::to_string(i) , "OP_ROLL.CNS.bmp", 0.2f * i);
		UImageManager::GetInstance().InsertCustomSpriteData("SepiaRoll", "SepiaRoll"+std::to_string(i), {{0,0}, {640,640}});
	}

	// 색상 반전
	UImageManager::GetInstance().ImageToInvert("OPBackInv", "OP_BACK.CNS.bmp");

	//너랑나랑 뿌요뿌요 메뉴 화면
	// 너랑나랑뿌요뿌요 메뉴 텍스트
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,0 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,96 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,128 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,32 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,64 }, { 512,32 } });

	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,0 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,96 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,128 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,32 }, { 512,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuText", "SEL_0.CNS.BMP", { { 0,64 }, { 512,32 } });


	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuLArrow", "SEL_0.CNS.BMP", { { 512,0 }, { 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuLArrow", "SEL_0.CNS.BMP", { { 528,0 }, { 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuRArrow", "SEL_0.CNS.BMP", { { 544,0 }, { 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuRArrow", "SEL_0.CNS.BMP", { { 560,0 }, { 16,24 } });

	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 544,32 }, { 16,16 } }); //TopLEft
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 304,192 }, { 304,16 } }); // Up
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 560,32 }, { 16,16 } }); // TopRight
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 624,0 }, { 8,224 } }); //Left
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 632,0 }, { 8,224 } }); //Right
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 544,48 }, { 16,16 } }); // BotLeft
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 304,208 }, { 304,16 } }); // Down
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOn", "SEL_0.CNS.BMP", { { 560,48 }, { 16,16 } }); // BotRight

	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 512,32 }, { 16,16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 0,192 }, { 304,16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 528,32 }, { 16,16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 608,0 }, { 8,224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 616,0 }, { 8,224 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 512,48 }, { 16,16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 0,208 }, { 304,16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSMenuFrameOff", "SEL_0.CNS.BMP", { { 528,48 }, { 16,16 } });

	//솔로모드 메뉴 스프라이트
	UImageManager::GetInstance().CuttingSprite("ARLE", "KAO_ARLE.CNS.BMP", { 160,112 });
	for (int i = 1; i <= 6; i++)
	{
		UImageManager::GetInstance().CuttingSprite("LV" + std::to_string(i), "LV" + std::to_string(i) + ".CNS.BMP", { 160,112 });
	}
	// 캐릭터 프레임
	UImageManager::GetInstance().CuttingSprite("FRAME", "KAO_WAKU.CNS.BMP", { 176,128 });
	// 탑?같이 생긴거
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,0 },		{256,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 256,0 },	{224,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,80 },	{192,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 480,0 },	{160,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 192,80 },	{128,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 320,80 },	{96,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { {  432,80  },{64,16} });//꼭대기
	UImageManager::GetInstance().InsertCustomSpriteData("TOWEREdge", "SELECT_T.CNS.BMP", { { 416,80 }, {16,16} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWEREdge", "SELECT_T.CNS.BMP", { { 496,80 }, {16,16} });
	// 적 선택 리스트
	UImageManager::GetInstance().CuttingSprite("EnemySelectOn", "SELECT_L.CNS.BMP", { 48,48 });
	UImageManager::GetInstance().CuttingSprite("EnemySelectOff", "SELECT_D.CNS.BMP", { 48,48 });

	UImageManager::GetInstance().CuttingSpriteCustom("EnemySelectText", "SELECT_L.CNS.BMP", { 384, 96 }, { 640, 128 }, { 32,32 });
	UImageManager::GetInstance().CuttingSpriteCustom("EnemySelectText", "SELECT_L.CNS.BMP", { 384, 96 }, { 640, 128 }, { 32,32 });



	//단색 스프라이트(+페이더용)
	UImageManager::GetInstance().CreateColorImage("Black"); 
	UImageManager::GetInstance().CreateColorImage("White", { 0,0,0,255 });
	UImageManager::GetInstance().CreateColorImage("Yellow", { 255, 255, 0, 255 });
	UImageManager::GetInstance().CreateColorImage("SkyBlue", { 0, 243, 243, 255 });
	UImageManager::GetInstance().CreateColorImage("GameOverBack", { 0, 0,32, 0 });
	UImageManager::GetInstance().CreateColorImage("Sepia", {112, 66, 20, 255});
	//인게임 Text
	UImageManager::GetInstance().ImageToGrayScale("GrayText", "Puyo_G_.cns.bmp");
	UImageManager::GetInstance().CuttingSprite("PUYO_BP.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G_.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_RY.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("GrayText", { 16,32 });
	UImageManager::GetInstance().CuttingSpriteCustom("NameText", "PUYO_RY.CNS.BMP", { 0,208 }, { 640,240 }, { 16,16 });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainString", "PUYO_RY.CNS.BMP", { { 240,32 }, { 48, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainString", "PUYO_BP.CNS.BMP", { { 240,32 }, { 48, 16 } });

	// 일시정지(휴식) 텍스트
	UImageManager::GetInstance().InsertCustomSpriteData("Pause", "PUYO_RY.CNS.BMP", { { 512,128 }, { 128, 48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Pause", "PUYO_BP.CNS.BMP", { { 512,128 }, { 128, 48 } });

	// 상쇄 텍스트
	UImageManager::GetInstance().InsertCustomSpriteData("OffsetText", "PUYO_RY.CNS.BMP", { { 368,128 }, { 64, 32 } });

	// 게임 끝나고 나서 프레임
	UImageManager::GetInstance().CuttingSprite("LVFrame", "LV_Waku.cns.bmp", { 16,16 });

	// 게임 플레이 관련
	// 인게임 뿌요 관련 스프라이트
	SetupPuyoSprite();
	//뿌요 터질 때 파티클
	SetupPuyoBoomParticleSprite();

	for (int i = 1; i <= 34; i++)
	{
		std::string Postfix = std::to_string(i);
		if (Postfix.size() < 2)
		{
			Postfix = "0" + Postfix;
		}
		if (i == 9 || i == 16 || i == 22 || i == 27 || i == 30 || i == 33)continue;
		UImageManager::GetInstance().InsertCustomSpriteData("FaceIdle", "FACE" + Postfix + ".CNS.BMP", { {0,0}, { 160, 112 } });
		UImageManager::GetInstance().InsertCustomSpriteData("FaceLose", "FACE" + Postfix + ".CNS.BMP", { {0,128}, { 160, 112 } });
		UImageManager::GetInstance().InsertCustomSpriteData("FaceWin", "FACE" + Postfix + ".CNS.BMP", { {160,128}, { 160, 112 } });
	}

	//Cut Menu Bg
	for (int i = 0; i <= 9; i++)
	{
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "L.CNS.BMP", { 128, 128 });
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "R.CNS.BMP", { 128, 128 });
	}

	for (int i = 1; i <= 8; i++)
	{
		//Solo Play Bg
		UImageManager::GetInstance().InsertCustomSpriteData("LVBG", "L" + std::to_string(i) + "_F.CNS.BMP", { {0,0},{640,480} });
		//Solo play Frame
		UImageManager::GetInstance().InsertCustomSpriteData("LVHEAD", "L" + std::to_string(i) + "_F.CNS.BMP", { { 0,0 }, { 640, 32 } });
		UImageManager::GetInstance().InsertCustomSpriteData("LVCENTER", "L" + std::to_string(i) + "_F.CNS.BMP", { { 304,64 }, { 32, 128 } });
		UImageManager::GetInstance().InsertCustomSpriteData("LVLEFT", "L" + std::to_string(i) + "_F.CNS.BMP", { { 0,32 },	{ 32,384} });
		UImageManager::GetInstance().InsertCustomSpriteData("LVINNERLEFT", "L" + std::to_string(i) + "_F.CNS.BMP", { { 224,32 }, { 16,384} });
		UImageManager::GetInstance().InsertCustomSpriteData("LVRIGHT", "L" + std::to_string(i) + "_F.CNS.BMP", { { 608,32 }, { 32,384 } });
		UImageManager::GetInstance().InsertCustomSpriteData("LVINNERRIGHT", "L" + std::to_string(i) + "_F.CNS.BMP", { { 400,32 }, { 16,384 } });
		UImageManager::GetInstance().InsertCustomSpriteData("LVTAIL", "L" + std::to_string(i) + "_F.CNS.BMP", { { 0,416 }, { 640, 64 } });
		UImageManager::GetInstance().InsertCustomSpriteData("LVBOTBG", "L" + std::to_string(i) + "_F.CNS.BMP", { { 32,352 }, { 192, 64 } });
		for (int j = 0; j < 6; j++)
		{
			UImageManager::GetInstance().InsertCustomSpriteData("LVBOTFR", "L" + std::to_string(i) + "_F.CNS.BMP", { { 32 + 32 * j,416 }, { 32, 64 } });
		}
		for (int j = 0; j < 6; j++)
		{
			UImageManager::GetInstance().InsertCustomSpriteData("LVBOTFR", "L" + std::to_string(i) + "_F.CNS.BMP", { { 416 + 32 * j,416 }, { 32, 64 } });
		}
	}

	std::vector<std::string> VSMapList = { "VS_N.CNS.BMP","VS_2K.CNS.BMP","VS_6K.CNS.BMP","VS_H.CNS.BMP","VS_S.CNS.BMP" };

	for (int i = 0; i < VSMapList.size(); i++)
	{
		//Multi Play Bg
		UImageManager::GetInstance().InsertCustomSpriteData("VSBG", VSMapList[i], { {0,0}, {640,480} });

		//Multi play Frame
		UImageManager::GetInstance().InsertCustomSpriteData("VSHEAD", VSMapList[i], { { 0,0 }, { 640, 32 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSCENTER", VSMapList[i], { { 304,64 }, { 32, 128 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSTAIL", VSMapList[i], { { 0,416 }, { 640, 64 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSLEFT", VSMapList[i], { { 0,32 }, { 32,384} });
		UImageManager::GetInstance().InsertCustomSpriteData("VSINNERLEFT", VSMapList[i], { { 224,32 }, { 16,384} });
		UImageManager::GetInstance().InsertCustomSpriteData("VSRIGHT", VSMapList[i], { { 608,32 }, { 32,384 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSINNERRIGHT", VSMapList[i], { { 400,32 }, { 16,384 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSBOTBG", VSMapList[i], { { 32,352 }, { 192,64 } });

		for (int j = 0; j < 6; j++)
		{
			UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR", VSMapList[i], { { 32 + 32 * j,416 }, { 32, 64 } });
		}
		for (int j = 0; j < 6; j++)
		{
			UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR", VSMapList[i], { { 416 + 32 * j,416 }, { 32, 64 } });
		}
	}

	UImageManager::GetInstance().InsertCustomSpriteData("TRBG", "TOKO_BG2.CNS.BMP", { { 0,0 }, { 640, 480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("TRHEAD", "TOKO_1A.CNS.BMP", { { 0,0 }, { 640, 480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("TRTAIL", "TOKO_2A.CNS.BMP", { { 0,0 }, { 640, 480 } });
	UImageManager::GetInstance().CuttingSprite("TRBOTBG", "TOKO_FF.CNS.BMP", { 192, 64 });
	for (int j = 0; j < 6; j++)
	{
		UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR1", "TOKO_1A.CNS.BMP", { { 32 + 32 * j,416 }, { 32, 64 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR2", "TOKO_2A.CNS.BMP", { { 32 + 32 * j,416 }, { 32, 64 } });
	}

	for (int j = 0; j < 6; j++)
	{
		UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR1", "TOKO_1A.CNS.BMP", { { 416 + 32 * j,416 }, { 32, 64 } });
		UImageManager::GetInstance().InsertCustomSpriteData("VSBOTFR2", "TOKO_2A.CNS.BMP", { { 416 + 32 * j,416 }, { 32, 64 } });
	}


	//Cut Menu Image

	// 카벙클 메뉴 이미지 자르기
	SetupCarbuncleSprite();

	// 연쇄발생시 이펙트 커팅
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { {0,64},{32, 32} });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { { 32,64 },{ 32, 32 } });
	for (int i = 0; i < 6; i++)
	{
		UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { { 64 + 64 * i , 64 },{ 64, 64 } });
	}
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXB", "PUYO_BP.CNS.BMP", { {0,64},{32, 32} });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXB", "PUYO_BP.CNS.BMP", { { 32,64 },{ 32, 32 } });
	for (int i = 0; i < 6; i++)
	{
		UImageManager::GetInstance().InsertCustomSpriteData("ChainFXB", "PUYO_BP.CNS.BMP", { { 64 + 64 * i , 64 },{ 64, 64 } });
	}


	//예고뿌요 스프라이트 커팅
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_RY.CNS.BMP", { { 320,144 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_RY.CNS.BMP", { { 288,128 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_RY.CNS.BMP", { { 256,128 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_BP.CNS.BMP", { { 192,160 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_RY.CNS.BMP", { { 224,128 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("Warning", "PUYO_RY.CNS.BMP", { { 192,128 },{ 32, 32 } });

	//꽈당 큐
	UImageManager::GetInstance().InsertCustomSpriteData("Kwadankyu", "PUYO_BP.CNS.BMP", { { 448,32 },{ 192, 96 } });

	//게임 오버 텍스트 스프라이트(싱글플레이)
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 0,0 },	{ 72, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 72,0 },	{ 56, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 128,0 },{ 88, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 216,0 },{ 56, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 272,0 },{ 64, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 336,0 },{ 56, 64 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "Over.CNS.BMP", { { 392,0 },{ 56, 64 } });
	//게임오버 장면 아르르
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverArle", "Over.CNS.BMP", { { 208,208 },{ 256, 112 } });
	// 계속 할까요?
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverContinue", "Over.CNS.BMP", { { 208,320 },{ 432, 32 } });
	// 게임오버 장면 뿌요
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverPuyo", "Over.CNS.BMP", { { 0,64 },{ 224, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverPuyo", "Over.CNS.BMP", { {224,64 },{ 224, 144} });
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverPuyo", "Over.CNS.BMP", { { 0,208 },{ 208, 152 } });

	
	//옵션 관련
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,0},{ 288, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,32},{ 256, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,64},{ 192, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,96},{ 192, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,128},{ 128, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,160},{ 288, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,192},{ 352, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTMENU", "OPT_STR.CNS.BMP", { { 0,224},{ 224, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,352},{ 320, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,384},{ 352, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,416},{ 224, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,448},{ 192, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,480},{ 288, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("SOUNDMENU", "OPT_STR.CNS.BMP", { { 0,512},{ 192, 32 } });


	UImageManager::GetInstance().InsertCustomSpriteData("OPTDIFF", "OPT_STR.CNS.BMP", { { 0,256},{ 184, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTDIFF", "OPT_STR.CNS.BMP", { { 96,256},{ 72, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTDIFF", "OPT_STR.CNS.BMP", { { 224,256},{ 64, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTDIFF", "OPT_STR.CNS.BMP", { { 192,288},{ 128, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPTDIFF", "OPT_STR.CNS.BMP", { { 0,288},{ 184, 32 } });
	///////////////////옵션 관련

	//////////여기서 부터 오디오 설정
	UAudioManager::GetInstance().FindSound("PuyoMoveMenu.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("PuyoMoveLR.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("PuyoEnemyChange.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("PUYOselect.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("PUYOPuyo2.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("SoloStart.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("StartPistol.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("Pause.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("GameLose.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("ARLE_Lose.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("GameOver.MID")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("PuyoPlace.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("Yaho.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("SoloWin.MID")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("CountingSound.wav")->SetLoop(false);
	UAudioManager::GetInstance().FindSound("Nuisance.wav")->SetLoop(false);

	for (int i = 0; i < 7; i++)
	{
		UAudioManager::GetInstance().FindSound("ARLE_" + std::to_string(i)+".wav")->SetLoop(false);
	}

	for (int i = 0; i < 7; i++)
	{
		UAudioManager::GetInstance().FindSound("PuyoDestroy" + std::to_string(i) + ".wav")->SetLoop(false);
	}

	for (int i = 1; i <= 34; i++)
	{
		std::string Temp= std::to_string(i);
		std::string Index = std::string(2 - Temp.size(), '0') + Temp;
		GameSettings::GetInstance().PickSound.push_back("VOIC" + Index + "S.wav");
		UAudioManager::GetInstance().FindSound("VOIC" + Index + "S.wav")->SetLoop(false);
	}


	// 여기서부터 게임 구성을 만든다.
	// TODO: 인트로(로딩?) 화면, 메인메뉴, 게임플레이(모드별 분리?), 
	// 게임오버? , 게임엔딩?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 640, 480 });
	UEngineAPICore::GetCore()->CreateLevel<AIntroGameMode, ADummyPawn>("Intro");
	UEngineAPICore::GetCore()->CreateLevel<AMenuGameMode, ADummyPawn>("Menu");
	UEngineAPICore::GetCore()->CreateLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
	UEngineAPICore::GetCore()->CreateLevel<ATogetherMenuGameMode, ADummyPawn>("TogetherMenu");

	UEngineAPICore::GetCore()->CreateLevel<ASoloPlayGameMode, ADummyPawn>("SoloPlay");
	UEngineAPICore::GetCore()->CreateLevel<ATogetherPlayGameMode, ADummyPawn>("TogetherPlay");
	UEngineAPICore::GetCore()->CreateLevel<ATrainingPlayGameMode, ADummyPawn>("TrainingPlay");
	UEngineAPICore::GetCore()->CreateLevel<APuzzleGameMode, ADummyPawn>("PuzzlePlay");
	UEngineAPICore::GetCore()->CreateLevel<AOptionsGameMode, ADummyPawn>("Options");
	UEngineAPICore::GetCore()->CreateLevel<AGameOverGameMode , ADummyPawn>("GameOver");
	//UEngineAPICore::GetCore()->CreateLevel("End");

	UEngineAPICore::GetCore()->OpenLevel("Intro");
	//UEngineAPICore::GetCore()->OpenLevel("TogetherPlay");
}

void PuyoPuyoContentsCore::SetupPuyoBoomParticleSprite()
{
	//Cut Puyo Boom Particles
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomR", "PUYO_R.CNS.BMP", { { 0,32 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomG", "PUYO_G.CNS.BMP", { { 0,32 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomB", "PUYO_B.CNS.BMP", { { 0,32 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomP", "PUYO_P.CNS.BMP", { { 0,32 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomY", "PUYO_Y.CNS.BMP", { { 0,32 },{ 32, 32 } });

	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomR", "PUYO_R.CNS.BMP", { { 592,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomG", "PUYO_G.CNS.BMP", { { 592,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomB", "PUYO_B.CNS.BMP", { { 592,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomP", "PUYO_P.CNS.BMP", { { 592,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomY", "PUYO_Y.CNS.BMP", { { 592,32 },{ 16, 16 } });

	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomR", "PUYO_R.CNS.BMP", { { 608,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomG", "PUYO_G.CNS.BMP", { { 608,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomB", "PUYO_B.CNS.BMP", { { 608,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomP", "PUYO_P.CNS.BMP", { { 608,32 },{ 16, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("PuyoBoomY", "PUYO_Y.CNS.BMP", { { 608,32 },{ 16, 16 } });
}

void PuyoPuyoContentsCore::SetupCarbuncleSprite()
{
	UImageManager::GetInstance().InsertCustomSpriteData("CARHEAD", "MENU_KA.CNS.BMP", { { 0,0 },{ 160, 152 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARHEAD", "MENU_KB.CNS.BMP", { { 0,0 },{ 160, 152 } });

	//Up Body
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KA.CNS.BMP", { { 352,0 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KA.CNS.BMP", { { 496,48 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KA.CNS.BMP", { { 496,0 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KA.CNS.BMP", { { 496,96 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KA.CNS.BMP", { { 352,48 },{ 144,48 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 352,0 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 496,48 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 496,0 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 496,96 },{ 144,48 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 352,48 },{ 144,48 } });

	//Inactive Animation Up
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 0,152 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 144,192 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 144,152 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 144,232 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 0,240 },{ 144,40 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 288,152 },{ 144,56} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 288,208 },{ 144,56} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 432,162 },{ 144,56} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 288,264 },{ 144,56} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 144,272 },{ 144,56} });

	UImageManager::GetInstance().InsertCustomSpriteData("CARUBODY", "MENU_KB.CNS.BMP", { { 432,208 },{ 144,88 } });



	//Down Body
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KA.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KA.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KA.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KA.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KA.CNS.BMP", { { 352,96 },{ 144,40 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 208,80 },{ 144,40 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 352,96 },{ 144,40 } });


	//Inactive Animation Down
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 0,192 },{ 144,48} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 0,192 },{ 144,48} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 0,192 },{ 144,48} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 0,192 },{ 144,48} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 0,272 },{ 144,48} });

	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 432,264 },{ 144,32} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 432,264 },{ 144,32} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 432,264 },{ 144,32} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 432,264 },{ 144,32} });
	UImageManager::GetInstance().InsertCustomSpriteData("CARDBODY", "MENU_KB.CNS.BMP", { { 432,264 },{ 144,32} });

	//Hand
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 160,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 208,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 256,0 },{ 24,72 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KB.CNS.BMP", { { 160,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KB.CNS.BMP", { { 208,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KB.CNS.BMP", { { 256,0 },{ 24,72 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 184,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 232,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 280,0 },{ 24,72 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KB.CNS.BMP", { { 184,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KB.CNS.BMP", { { 232,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KB.CNS.BMP", { { 280,0 },{ 24,72 } });

	//Leg
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEG", "MENU_KA.CNS.BMP", { { 160,120 },{ 176,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEG", "MENU_KB.CNS.BMP", { { 160,120 },{ 176,32 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFTARROW", "MENU_KA.CNS.BMP", { { 304,0 },{ 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFTARROW", "MENU_KA.CNS.BMP", { { 304,24 },{ 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHTARROW", "MENU_KA.CNS.BMP", { { 320,0 },{ 16,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHTARROW", "MENU_KA.CNS.BMP", { { 320,24 },{ 16,24 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARJEWEL", "MENU_KA.CNS.BMP", { { 160,72 },{ 24,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARJEWEL", "MENU_KA.CNS.BMP", { { 184,72 },{ 24,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARJEWEL", "MENU_KA.CNS.BMP", { { 160,96 },{ 24,24 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARJEWEL", "MENU_KA.CNS.BMP", { { 184,96 },{ 24,24 } });
}

void PuyoPuyoContentsCore::SetupPuyoSprite()
{
	//Cut Puyo
	UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_B.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_P.CNS.BMP", { 32,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_Y.CNS.BMP", { 32,32 });
	//방해 뿌요
	UImageManager::GetInstance().InsertCustomSpriteData("GARBAGE", "PUYO_BP.CNS.BMP", { { 0,128 },{ 32,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GARBAGE", "PUYO_BP.CNS.BMP", { { 32,128 },{ 32,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GARBAGE", "PUYO_BP.CNS.BMP", { { 64,128 },{ 32,32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("GARBAGE", "PUYO_BP.CNS.BMP", { { 96,128 },{ 32,32 } });
}

void PuyoPuyoContentsCore::Tick()
{
}


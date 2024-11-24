#include "aepch.h"
#include "PuyoPuyoContentsCore.h"

#include "DummyPawn.h"
#include "IntroGameMode.h"

#include "MenuGameMode.h"
#include "SoloMenuGameMode.h"
#include "TogetherMenuGameMode.h"

#include "SoloPlayGameMode.h"
#include "TogetherPlayGameMode.h"
#include "TrainingPlayGameMode.h"

#include "OptionsGameMode.h"

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
	EngineDebugHelper::SetShowFPS(true);

	UEngineAPICore::GetCore()->LoadResources();

	//USoundManager::GetInstance().FindSound("OPTheme.mp3")->Play();

	//Intro
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOEYE", "OP_PUYO.CNS.BMP", { {0,0 }, { 144, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOBOT", "OP_PUYO.CNS.BMP", { {0,240 }, { 640, 240 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOTOP", "OP_PUYO.CNS.BMP", { {160,0 }, { 480, 240 } });

	UImageManager::GetInstance().InsertCustomSpriteData("OPCAR", "OP_KAR.CNS.BMP", { {0,0 }, { 448, 480 } });
	UImageManager::GetInstance().CuttingSpriteCustom("OPCARJEWEL", "OP_KAR.CNS.BMP", { 448,0 }, { 640,72 }, { 48,72 });
	UImageManager::GetInstance().InsertCustomSpriteData("OPCARJEWEL", "OP_KAR.CNS.BMP", { { 0,220 }, { 48,72 } });

	//Todo: 나중에 다시 생각해봄
	UImageManager::GetInstance().InsertCustomSpriteData("OPARLE", "OP_ARLE.CNS.BMP", { {0,0 }, { 640, 480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {0,480 }, { 144, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {144,480 }, { 176, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {320,480 }, { 144, 104 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPFINGER", "OP_ARLE.CNS.BMP", { {464,480 }, { 176, 104 } });

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

	//솔로모드 메뉴 스프라이트
	UImageManager::GetInstance().CuttingSprite("ARLE", "KAO_ARLE.CNS.BMP", { 160,112 });
	for (int i = 1; i <= 6; i++)
	{
		UImageManager::GetInstance().CuttingSprite("LV" + std::to_string(i), "LV" + std::to_string(i) + ".CNS.BMP", { 160,112 });
	}
	// 캐릭터 프레임
	UImageManager::GetInstance().CuttingSprite("FRAME", "KAO_WAKU.CNS.BMP", { 176,128 });
	// 탑?같이 생긴거
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,0 }, {256,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 256,0 }, {224,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 480,0 }, {160,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,80 }, {192,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,0 }, {128,80} });
	UImageManager::GetInstance().InsertCustomSpriteData("TOWER", "SELECT_T.CNS.BMP", { { 0,0 }, {96,80} });
	// 적 선택 리스트
	UImageManager::GetInstance().CuttingSprite("EnemySelectOn", "SELECT_L.CNS.BMP", { 48,48 });
	UImageManager::GetInstance().CuttingSprite("EnemySelectOff", "SELECT_D.CNS.BMP", { 48,48 });

	UImageManager::GetInstance().CuttingSpriteCustom("EnemySelectText", "SELECT_L.CNS.BMP", { 384, 96 }, { 640, 128 }, { 32,32 });



	//단색 스프라이트(+페이더용)
	UImageManager::GetInstance().CreateColorImage("Black");
	UImageManager::GetInstance().CreateColorImage("White", { 0,0,0,255 });
	UImageManager::GetInstance().CreateColorImage("Yellow", { 255, 255, 0, 255 });
	//인게임 Text
	UImageManager::GetInstance().ImageToGrayScale("GrayText", "Puyo_BP.cns.bmp");
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



	// 게임 플레이 관련
	// 인게임 뿌요 관련 스프라이트
	SetupPuyoSprite();
	//뿌요 터질 때 파티클
	SetupPuyoBoomParticleSprite();

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


	//GameOver
	UImageManager::GetInstance().InsertCustomSpriteData("GameOverText", "PUYO_BP.CNS.BMP", { { 448,32 },{ 192, 96 } });

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
	//UEngineAPICore::GetCore()->CreateLevel<ATogetherMenuGameMode, ADummyPawn>("PuzzlePlay");
	UEngineAPICore::GetCore()->CreateLevel<AOptionsGameMode, ADummyPawn>("Options");
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


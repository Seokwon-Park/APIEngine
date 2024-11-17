#include "aepch.h"
#include "PuyoPuyoContentsCore.h"
#include "TogetherPlayGameMode.h"
#include "MenuGameMode.h"
#include "SoloMenuGameMode.h"
#include "IntroGameMode.h"
#include "DummyPawn.h"
#include <EngineBase/EngineFile.h>
#include <EngineBase/EngineDirectory.h>
#include <EngineCore/ImageManager.h>
#include <EngineCore/SoundManager.h>
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



	//인게임 뿌요 관련 스프라이트
	SetupPuyoSprite();
	
	//Intro Eye
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOEYE", "OP_PUYO.CNS.BMP", { {0,0 }, { 144, 144 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOBOT", "OP_PUYO.CNS.BMP", { {0,240 }, { 640, 240 } });
	UImageManager::GetInstance().InsertCustomSpriteData("OPPUYOTOP", "OP_PUYO.CNS.BMP", { {160,0 }, { 480, 240 } });


	UImageManager::GetInstance().CreateColorImage("Black" );
	UImageManager::GetInstance().CreateColorImage("White", { 0,0,0,255 });
	UImageManager::GetInstance().CreateColorImage("Yellow", { 255, 255, 0, 255 });
	//Cut Text
	UImageManager::GetInstance().CuttingSprite("PUYO_BP.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G_.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_RY.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSpriteCustom("NameText", "PUYO_RY.CNS.BMP", { 0,208 }, { 640,240 }, { 16,16 });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainString", "PUYO_RY.CNS.BMP", { { 240,32 }, { 48, 16 } });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainString", "PUYO_BP.CNS.BMP", { { 240,32 }, { 48, 16 } });

	//Cut Intro Bg
	for (int i = 0; i <= 9; i++)
	{
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "L.CNS.BMP", { 128, 128 });
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "R.CNS.BMP", { 128, 128 });
	}


	SetupPuyoBoomParticleSprite();

	//Solo Play Bg
	for (int i = 1; i <= 8; i++)
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "L1_F.CNS.BMP", { {0,0},{640,480} });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });

	UImageManager::GetInstance().InsertCustomSpriteData("LVHEAD", "L1_F.CNS.BMP", { { 0,0 }, { 640, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVCENTER", "L1_F.CNS.BMP", { { 304,64 }, { 32, 128 } });

	//Multi Play Bg
	UImageManager::GetInstance().InsertCustomSpriteData("VSHEAD", "VS_2K.CNS.BMP", { { 0,0 }, { 640, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSCENTER", "VS_2K.CNS.BMP", { { 304,64 }, { 32, 128 } });

	UImageManager::GetInstance().InsertCustomSpriteData("VSBOARD", "VS_2K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSBOARD", "VS_6K.CNS.BMP", { { 0,0 },{ 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSBOARD", "VS_H.CNS.BMP", { { 0,0 }, { 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSBOARD", "VS_N.CNS.BMP", { { 0,0 }, { 640,480 } });
	UImageManager::GetInstance().InsertCustomSpriteData("VSBOARD", "VS_S.CNS.BMP", { { 0,0 }, { 640,480 } });

	UImageManager::GetInstance().InsertCustomSpriteData("LVHEAD", "L1_F.CNS.BMP", { { 0,0 }, { 640, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("LVCENTER", "L1_F.CNS.BMP", { { 304,64 }, { 32, 128 } });

	//Together Play Bg
	UImageManager::GetInstance().CuttingSprite("L1_F.CNS.BMP", { 640,480 });


	//Cut Menu Image

	// 카벙클 메뉴 이미지 자르기
	SetupCarbuncleSprite();

	// 연쇄발생시 이펙트 커팅
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { {0,64},{32, 32} });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { { 32,64 },{ 32, 32 } });
	for (int i = 0; i < 6; i++)
	{
		UImageManager::GetInstance().InsertCustomSpriteData("ChainFXR", "PUYO_RY.CNS.BMP", { { 64 + 64*i , 64 },{ 64, 64 } });
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


	UImageManager::GetInstance().CuttingSprite("MENU_KA.CNS.BMP", { 640,480 });
	UImageManager::GetInstance().CuttingSprite("MENU_KB.CNS.BMP", { 640,480 });

	// 여기서부터 게임 구성을 만든다.
	// TODO: 인트로(로딩?) 화면, 메인메뉴, 게임플레이(모드별 분리?), 
	// 게임오버? , 게임엔딩?
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowTitle("Puyo Puyo Tsu");
	UEngineAPICore::GetCore()->GetMainWindow().SetWindowPosAndScale({ 0, 0 }, { 640, 480 });
	UEngineAPICore::GetCore()->CreateLevel<AIntroGameMode, ADummyPawn>("Intro");
	UEngineAPICore::GetCore()->CreateLevel<AMenuGameMode, ADummyPawn>("Menu");
	UEngineAPICore::GetCore()->CreateLevel<ASoloMenuGameMode, ADummyPawn>("SoloMenu");
	UEngineAPICore::GetCore()->CreateLevel<ATogetherPlayGameMode, ADummyPawn>("TogetherPlay");
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


	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 160,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 208,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARLEFT", "MENU_KA.CNS.BMP", { { 256,0 },{ 24,72 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 184,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 232,0 },{ 24,72 } });
	UImageManager::GetInstance().InsertCustomSpriteData("CARRIGHT", "MENU_KA.CNS.BMP", { { 280,0 },{ 24,72 } });

	UImageManager::GetInstance().InsertCustomSpriteData("CARLEG", "MENU_KA.CNS.BMP", { { 160,120 },{ 176,32 } });

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


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


PuyoPuyoContentsCore::PuyoPuyoContentsCore()
{
}

PuyoPuyoContentsCore::~PuyoPuyoContentsCore()
{
}

void PuyoPuyoContentsCore::BeginPlay()
{
	UEngineDebugHelper::SetShowFPS(true);

	UEngineAPICore::GetCore()->LoadResources();

	SetupPuyoSprite();

	//Cut Text
	UImageManager::GetInstance().CuttingSprite("PUYO_BP.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_G_.CNS.BMP", { 16,32 });
	UImageManager::GetInstance().CuttingSprite("PUYO_RY.CNS.BMP", { 16,32 });

	//Cut Intro Bg
	for (int i = 0; i <= 9; i++)
	{
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "L.CNS.BMP", { 128, 128 });
		UImageManager::GetInstance().CuttingSprite("SD" + std::to_string(i) + "R.CNS.BMP", { 128, 128 });
	}

	//Cut Play Bg
	UImageManager::GetInstance().CuttingSprite("L1_F.CNS.BMP", { 640,480 });

	//Cut Menu Image
	
	// 카벙클 메뉴 이미지 자르기
	SetupCarbuncleSprite();

	// 연쇄발생시 이펙트 커팅
	UImageManager::GetInstance().InsertCustomSpriteData("ChainEffect", "MENU_KA.CNS.BMP", { { 0,64 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainEffect", "MENU_KA.CNS.BMP", { { 32,64 },{ 32, 32 } });
	UImageManager::GetInstance().InsertCustomSpriteData("ChainEffect", "MENU_KA.CNS.BMP", { { 64,64 },{ 64, 64 } });




	
	UImageManager::GetInstance().CuttingSprite("MENU_KA.CNS.BMP", { 640,480 });
	UImageManager::GetInstance().CuttingSprite("MENU_KB.CNS.BMP", { 640,480 });

	//UImageManager::GetInstance().CuttingSprite("PUYO_R.CNS.bmp", { 32, 32 });
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
}

void PuyoPuyoContentsCore::Tick()
{
}


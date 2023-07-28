#include "App.h"
#include "DxLib.h"
#include "Common.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Sound.h"

/// <summary>
/// コンストラクタ
/// </summary>
App::App()
{
	SetMainWindowText("SharkGame");
	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, COLOR_BIT_DEPTH);
	ChangeWindowMode(FALSE);
	SetWaitVSyncFlag(FALSE);
	SetOutApplicationLogValidFlag(FALSE); // Log.txtを書き出さないようにする
	DxLib_Init();
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(FALSE);

	sceneManager = new SceneManager();
	sceneManager->SetNowScene(TAG_SCENE::TAG_TITLE);
}

App::~App()
{
	Sound::InitSound();
	delete sceneManager;
	sceneManager = 0;

	DxLib_End();
}

void App::GameLoop()
{
	sceneManager->GameLoop();
}
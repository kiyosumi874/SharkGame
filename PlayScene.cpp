#include "PlayScene.h"
#include "DxLib.h"
#include "Input.h"
#include "GameStateMachine.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
	: gameStateMachine(nullptr)
{
	gameStateMachine = new GameStateMachine();
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	delete gameStateMachine;
}

/// <summary>
/// 更新
/// </summary>
TAG_SCENE PlayScene::Update(float deltaTime)
{
	// 次のシーンへ
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		gameStateMachine->ChangeState(GameStateType::Title);
	}

	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

	gameStateMachine->OnUpdate(deltaTime);

	map->Update(deltaTime);

	// 次のループもこのシーンを継続
	return TAG_SCENE::TAG_NONE;
}

/// <summary>
/// 描画
/// </summary>
void PlayScene::Draw()
{
#ifdef _DEBUG
	printfDx("PlayScene\n");
#endif // _DEBUG
	gameStateMachine->OnDraw();

	map->Draw();
}
#include "PlayScene.h"
#include "DxLib.h"
#include "Input.h"

/// <summary>
/// コンストラクタ
/// </summary>
PlayScene::PlayScene()
{
	// 処理なし
}

/// <summary>
/// デストラクタ
/// </summary>
PlayScene::~PlayScene()
{
	// 処理なし
}

/// <summary>
/// 更新
/// </summary>
TAG_SCENE PlayScene::Update()
{
	// 次のシーンへ
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		return TAG_SCENE::TAG_RESULT;
	}

	// 終了
	if (Input::IsDown1P(BUTTON_ID_BACK))
	{
		return TAG_SCENE::TAG_END;
	}

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
}
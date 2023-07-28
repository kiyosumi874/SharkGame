#include "GameStateTitle.h"
#include "DxLib.h"
#include "Input.h"

/// <summary>
/// ステートを開始した時に呼ばれる
/// </summary>
void GameStateTitle::OnEnter()
{
	// 処理なし
}

/// <summary>
/// 毎フレーム呼ばれる更新
/// </summary>
void GameStateTitle::OnUpdate(float deltaTime)
{
}

/// <summary>
/// 毎フレーム呼ばれる更新
/// </summary>
void GameStateTitle::OnDraw()
{
	printfDx("State:Title\n");
}

/// <summary>
/// ステートを終了した時に呼ばれる
/// </summary>
void GameStateTitle::OnExit()
{
	// 処理なし
}

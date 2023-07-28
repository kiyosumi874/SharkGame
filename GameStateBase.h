#pragma once

/// <summary>
/// GameStateのBaseクラス
/// </summary>
class GameStateBase
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameStateBase();

    /// <summary>
    /// デストラクタ
    /// </summary>
    virtual ~GameStateBase();

    /// <summary>
    /// ステートを開始した時に呼ばれる
    /// </summary>
    virtual void OnEnter() { }

    /// <summary>
    /// 毎フレーム呼ばれる更新
    /// </summary>
    virtual void OnUpdate(float deltaTime) { }

    /// <summary>
    /// 毎フレーム呼ばれる描画
    /// </summary>
    virtual void OnDraw() { }

    /// <summary>
    /// ステートを終了した時に呼ばれる
    /// </summary>
    virtual void OnExit() { }
};
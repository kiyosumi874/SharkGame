#pragma once
#include <vector>
#include "GameStateBase.h"
#include "GameStateType.h"

/// <summary>
/// ゲームステートをまとめたクラス
/// </summary>
class GameStates
{
public:
    /// <summary>
    /// コンストラクタ
    /// </summary>
    GameStates();

    /// <summary>
    /// デストラクタ
    /// </summary>
    ~GameStates();

    /// <summary>
    /// ステートを取得する
    /// </summary>
    /// <param name="type">ステートの種類</param>
    /// <returns>ステートのインスタンス</returns>
    GameStateBase* GetState(const GameStateType type);
private:
    class GameStateTitle* gameStateTitle;
    class GameStateStartCountDown* gameStateStartCountDown;
    class GameStatePlayerRound* gameStatePlayerRound;
    class GameStateSharkShoot* gameStateSharkShoot;
    class GameStateSharkFly* gameStateSharkFly;
    class GameStateSharkLandsOnWater* gameStateSharkLandsOnWater;
    class GameStateResult* gameStateResult;

    std::vector<GameStateBase*> gameStates;
};
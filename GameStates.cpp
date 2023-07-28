#include "GameStates.h"
#include "GameStateTitle.h"
#include "GameStateStartCountDown.h"
#include "GameStatePlayerRound.h"
#include "GameStateSharkShoot.h"
#include "GameStateSharkFly.h"
#include "GameStateSharkLandsOnWater.h"
#include "GameStateResult.h"

GameStates::GameStates()
    : gameStates(NULL)
    , gameStateTitle(nullptr)
    , gameStateStartCountDown(nullptr)
    , gameStatePlayerRound(nullptr)
    , gameStateSharkShoot(nullptr)
    , gameStateSharkFly(nullptr)
    , gameStateResult(nullptr)
{
    gameStateTitle = new GameStateTitle();
    gameStateStartCountDown = new GameStateStartCountDown();
    gameStatePlayerRound = new GameStatePlayerRound();
    gameStateSharkShoot = new GameStateSharkShoot();
    gameStateSharkFly = new GameStateSharkFly();
    gameStateResult = new GameStateResult();
    gameStateSharkLandsOnWater = new GameStateSharkLandsOnWater();
    gameStates.push_back(gameStateTitle);
    gameStates.push_back(gameStateStartCountDown);
    gameStates.push_back(gameStatePlayerRound);
    gameStates.push_back(gameStateSharkShoot);
    gameStates.push_back(gameStateSharkFly);
    gameStates.push_back(gameStateSharkLandsOnWater);
    gameStates.push_back(gameStateResult);
}

GameStates::~GameStates()
{
    delete gameStateTitle;
    delete gameStateStartCountDown;
    delete gameStatePlayerRound;
    delete gameStateSharkShoot;
    delete gameStateSharkFly;
    delete gameStateSharkLandsOnWater;
    delete gameStateResult;
    gameStates.clear();
}

GameStateBase* GameStates::GetState(const GameStateType type)
{
    return gameStates[(int)type];
}

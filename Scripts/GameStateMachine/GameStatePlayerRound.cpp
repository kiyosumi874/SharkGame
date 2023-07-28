#include "GameStatePlayerRound.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Shark/Shark.h"
#include "Player/Player.h"
#include "Map/Map.h"

GameStatePlayerRound::GameStatePlayerRound(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStatePlayerRound::OnEnter()
{
}

void GameStatePlayerRound::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::SharkShoot);
	}

	initData.player->Update(deltaTime);
	initData.shark->UpdatePlayerRound();
}

void GameStatePlayerRound::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:PlayerRound\n");
#endif // _DEBUG
	initData.map->Draw();
	initData.player->Draw();
	initData.shark->Draw();
}

void GameStatePlayerRound::OnExit()
{
}

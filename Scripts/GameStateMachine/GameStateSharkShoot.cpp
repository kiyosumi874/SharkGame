#include "GameStateSharkShoot.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Map/Map.h"

GameStateSharkShoot::GameStateSharkShoot(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateSharkShoot::OnEnter()
{
}

void GameStateSharkShoot::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::SharkFly);
	}
}

void GameStateSharkShoot::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:SharkShoot\n");
#endif // _DEBUG
	initData.map->Draw();
}

void GameStateSharkShoot::OnExit()
{
}

#include "GameStateResult.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "UI/PressAUI.h"
#include "Map/Map.h"
#include "UI/ResultScoreUI.h"

GameStateResult::GameStateResult(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

void GameStateResult::OnEnter()
{
	initData.pressAUI->Initialize(false);
	initData.resultScoreUI->Initialize(0);
}

void GameStateResult::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_START))
	{
		ChangeState(GameStateType::Title);
	}
	initData.pressAUI->Update(deltaTime);
}

void GameStateResult::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:Result\n");
#endif // _DEBUG
	initData.map->Draw();
	initData.pressAUI->Draw();
	initData.resultScoreUI->Draw();
}

void GameStateResult::OnExit()
{
}

#include "GameStateMachine.h"
#include "GameStates.h"
#include "GameStateBase.h"

GameStateMachine::GameStateMachine()
	: gameStates(nullptr)
	, currentState(nullptr)
{
	gameStates = new GameStates();
	currentState = gameStates->GetState(GameStateType::Title);
	currentState->OnEnter();
}

GameStateMachine::~GameStateMachine()
{
	delete gameStates;
}

void GameStateMachine::ChangeState(GameStateType nextStateType)
{
	auto nextState = gameStates->GetState(nextStateType);
	currentState->OnExit();
	nextState->OnEnter();
	currentState = nextState;
}

void GameStateMachine::OnUpdate(float deltaTime)
{
	currentState->OnUpdate(deltaTime);
}

void GameStateMachine::OnDraw()
{
	currentState->OnDraw();
}

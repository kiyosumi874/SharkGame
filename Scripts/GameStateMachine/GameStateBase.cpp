#include "GameStateBase.h"

/// <summary>
/// �R���X�g���N�^
/// </summary>
GameStateBase::GameStateBase(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: changeStateMediator(nullptr)
	, gameStateMachine(nullptr)
	, initData()
{
	this->changeStateMediator = changeStateMediator;
	this->gameStateMachine = gameStateMachine;
	this->initData = initData;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
GameStateBase::~GameStateBase()
{
	changeStateMediator = nullptr;
}

/// <summary>
/// �X�e�[�g��ύX����
/// </summary>
void GameStateBase::ChangeState(GameStateType nextStateType)
{
	(gameStateMachine->*changeStateMediator)(nextStateType);
}

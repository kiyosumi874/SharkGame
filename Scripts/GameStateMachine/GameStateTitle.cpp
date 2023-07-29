#include "GameStateTitle.h"
#include "DxLib.h"
#include "Input/Input.h"
#include "Player/Player.h"
#include "Map/Map.h"
#include "UI/PressAUI.h"
#include "Shark/Shark.h"

GameStateTitle::GameStateTitle(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData)
	: GameStateBase(changeStateMediator, gameStateMachine, initData)
{
}

/// <summary>
/// �X�e�[�g���J�n�������ɌĂ΂��
/// </summary>
void GameStateTitle::OnEnter()
{
	initData.pressAUI->Initialize(true);
	initData.map->Initialize();
	initData.player->Initialize();
	initData.shark->Init();
	initData.shark->SetplayerAngle(initData.player->GetRotationRad());
}

/// <summary>
/// ���t���[���Ă΂��X�V
/// </summary>
void GameStateTitle::OnUpdate(float deltaTime)
{
	if (Input::IsDown1P(BUTTON_ID_A))
	{
		ChangeState(GameStateType::StartCountDown);
	}
	initData.pressAUI->Update(deltaTime);
}

/// <summary>
/// ���t���[���Ă΂��X�V
/// </summary>
void GameStateTitle::OnDraw()
{
#ifdef _DEBUG
	printfDx("State:Title\n");
#endif // _DEBUG
	initData.map->DrawBeach();
	initData.player->Draw();
	initData.pressAUI->Draw();
	initData.shark->Draw();
}

/// <summary>
/// �X�e�[�g���I���������ɌĂ΂��
/// </summary>
void GameStateTitle::OnExit()
{
	// �����Ȃ�
}
#pragma once
#include "GameStateType.h"
#include "GameStateMachine.h"
#include "GameStateInitializeData.h"

typedef void (GameStateMachine::*ChangeStateMediator)(GameStateType);

/// <summary>
/// GameState��Base�N���X
/// </summary>
class GameStateBase
{
public:

    

    GameStateBase() = delete; // �f�t�H���g�R���X�g���N�^�̎g�p����
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameStateBase(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData);

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~GameStateBase();

    /// <summary>
    /// �X�e�[�g���J�n�������ɌĂ΂��
    /// </summary>
    virtual void OnEnter() { }

    /// <summary>
    /// ���t���[���Ă΂��X�V
    /// </summary>
    virtual void OnUpdate(float deltaTime) { }

    /// <summary>
    /// ���t���[���Ă΂��`��
    /// </summary>
    virtual void OnDraw() { }

    /// <summary>
    /// �X�e�[�g���I���������ɌĂ΂��
    /// </summary>
    virtual void OnExit() { }
protected:
    /// <summary>
    /// �X�e�[�g��ύX����
    /// </summary>
    void ChangeState(GameStateType nextStateType);

    InitializeData initData;
private:
    ChangeStateMediator changeStateMediator;
    GameStateMachine* gameStateMachine;
};
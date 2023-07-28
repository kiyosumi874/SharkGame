#pragma once
#include "GameStateBase.h"

/// <summary>
/// �Q�[���X�e�[�g�F�T���𓊂�����
/// </summary>
class GameStateSharkShoot : public GameStateBase
{
public:
	GameStateSharkShoot(ChangeStateMediator changeStateMediator, GameStateMachine* gameStateMachine, InitializeData initData);

    /// <summary>
    /// �X�e�[�g���J�n�������ɌĂ΂��
    /// </summary>
    void OnEnter() override;

    /// <summary>
    /// ���t���[���Ă΂��X�V
    /// </summary>
    void OnUpdate(float deltaTime) override;

    /// <summary>
    /// ���t���[���Ă΂��`��
    /// </summary>
    void OnDraw() override;

    /// <summary>
    /// �X�e�[�g���I���������ɌĂ΂��
    /// </summary>
    void OnExit() override;
};
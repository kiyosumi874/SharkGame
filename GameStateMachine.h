#pragma once
#include "GameStateType.h"

/// <summary>
/// �Q�[���S�̂̃X�e�[�g�}�V��
/// </summary>
class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

    /// <summary>
    /// �X�e�[�g��ύX����
    /// </summary>
    void ChangeState(GameStateType nextStateType);

    /// <summary>
    /// �X�V
    /// </summary>
    void OnUpdate(float deltaTime);

    /// <summary>
    /// �`��
    /// </summary>
    void OnDraw();
private:
    class GameStates* gameStates;
    class GameStateBase* currentState;
};
#pragma once
#include "GameStateBase.h"

/// <summary>
/// �Q�[���X�e�[�g�F�^�C�g��
/// </summary>
class GameStateTitle : public GameStateBase
{
public:
    // NOTE:����͗�Ƃ��ď����Ȃ��ł��֐����������Ă��邪
    // ���ۂ͂��Ȃ��Ă��悢
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
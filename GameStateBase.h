#pragma once

/// <summary>
/// GameState��Base�N���X
/// </summary>
class GameStateBase
{
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    GameStateBase();

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
};
#pragma once

/// <summary>
/// �Q�[���V�[���̃X�e�[�g�̎��
/// </summary>
enum GameStateType
{
    Title, // �^�C�g���X�e�[�g
    StartCountDown, // �n�܂�܂ł̃J�E���g�_�E���̃X�e�[�g
    PlayerRound, // �v���C���[����]������X�e�[�g
    SharkShoot, // �T���𓊂������̃X�e�[�g
    SharkFly, // �T�������ł��鎞�̃X�e�[�g
    SharkLandsOnWater, // �T���������������̃X�e�[�g
    Result, // ���U���g�̃X�e�[�g
    None
};
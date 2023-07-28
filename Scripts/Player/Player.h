#pragma once
#include <DxLib.h>

class Player {
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// ��Ԃ̍X�V
	/// </summary>
	/// <param name="deltaTime">�f���^�^�C��</param>
	void Update(float deltaTime);

	void Draw();

private:

	VECTOR position;		// ���W�x�N�g��

	VECTOR v1;

	int inputX, inputY;		// �p�b�h�̃A�i���O�X�e�B�b�N����

	int prevInputX, prevInputY;

	int graphHandle;		// �摜�n���h��

	float power;			// ��΂���

	float inputAngle;		// �X�e�B�b�N�̓��͊p�x

	float prevInputAngle;	// �O�t���[���ł̓��͊p�x

	float angleBetween;

	float playerAngle;

	float playerAngleAdd;

	bool prevFrameInput;	// �O�̃t���[���œ��͂���������
};
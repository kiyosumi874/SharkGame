#pragma once
#include <DxLib.h>

class Player {
public:

	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	Player();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// ��Ԃ̍X�V
	/// </summary>
	/// <param name="deltaTime">�f���^�^�C��</param>
	void Update(float deltaTime);

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̉�]�p�x
	/// </summary>
	/// <returns></returns>
	float GetRotationRad() const { return playerAngle; }

	/// <summary>
	/// �m�肵���ŏI���x (�l�Œ�)
	/// </summary>
	/// <returns></returns>
	float GetVelocity() const { return 300; }

	/// <summary>
	/// �{�^������������
	/// </summary>
	/// <returns></returns>
	bool GetIsPushButton() const{ return pushFlg; }
private:

	VECTOR position;		// ���W�x�N�g��

	VECTOR v1;

	int inputX, inputY;		// �p�b�h�̃A�i���O�X�e�B�b�N����

	int prevInputX, prevInputY;

	int graphHandle;		// �摜�n���h��

	int gauseGraph;			// �Q�[�W�摜

	float power;			// ��΂���

	float inputAngle;		// �X�e�B�b�N�̓��͊p�x

	float prevInputAngle;	// �O�t���[���ł̓��͊p�x

	float angleBetween;

	float playerAngle;

	float rotationSum;

	float playerAngleAdd;

	float prevTimer;

	float powerAdd;

	float velocity;

	float angle;

	int timer;

	bool prevFrameInput;	// �O�̃t���[���œ��͂���������

	bool isStartTimer;

	bool pushFlg;
	int graphHandle2;
};
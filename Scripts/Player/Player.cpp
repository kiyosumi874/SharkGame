#include <math.h>

#include "Common.h"
#include "Player.h"

// �R���X�g���N�^
Player::Player()
{
	// ���W�̏�����
	position = VGet(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, 0);

	// �A�i���O�X�e�B�b�N���͏�����
	inputX = 0;
	inputY = 0;

	// �p���[������
	power = 0;

	// �p�x������
	inputAngle = 0;

	angleBetween = 0;

	playerAngle = 0;

	playerAngleAdd = 0;

	// �t���O������
	prevFrameInput = false;

	// �摜�̓ǂݍ���
	graphHandle = LoadGraph("Textures/Player/Player.png");

	// �f�b�h�]�[���ݒ�
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.7);
}

// ��Ԃ̍X�V
void Player::Update(float deltaTime)
{
	// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓��͗ʂ��擾
	GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

	inputAngle = atan2(inputY, inputX);

	if (inputAngle < 0)
	{
		inputAngle = DX_PI_F * 2 + inputAngle;
	}

	if (prevFrameInput)
	{
		angleBetween = fabs(prevInputAngle - inputAngle);
	}
	else
	{
		angleBetween = 0.0;
	}

	if (angleBetween<=0.0)
	{
		if (power > 0)
			power -= 0.01;
		else
			power = 0;
	}

	if (prevFrameInput)
	{
		v1 = VTransform(VNorm(VGet(prevInputX, prevInputY, 0)), MGetRotZ(DX_PI_F / 2));
		VECTOR v2 = VNorm(VGet(inputX, inputY, 0));
		angleBetween = VDot(v1, v2) / (VSize(v1) * VSize(v2));
	}
	else
	{
		angleBetween = 0.0f;
	}

	if (prevFrameInput && angleBetween > 0.0f)
	{
		power += angleBetween;
	}

	if (power < 100)
		playerAngle += DX_PI_F / 180 * (power / 50);
	else
		playerAngle += DX_PI_F / 180 * (100.0 / 50);

	if (fabs(inputX) + fabs(inputY) > 0)
	{
		prevFrameInput = true;
		prevInputAngle = inputAngle;
		prevInputX = inputX;
		prevInputY = inputY;
	}
	else
	{
		prevFrameInput = false;
	}
}

void Player::Draw()
{
	DrawRotaGraph(position.x, position.y, 0.5, playerAngle, graphHandle, TRUE);

	DrawLine(position.x, position.y, position.x+v1.x*50, position.y+v1.y*50, GetColor(255, 255, 255));

	printfDx("X %d Y %d", inputX, inputY);
	printfDx("\nangle %f", inputAngle);
	printfDx("\nangleBetween %f", angleBetween);
	printfDx("\npower %f", power);
	printfDx("\nprevFrameInput %s", prevFrameInput ? "true" : "false");
}
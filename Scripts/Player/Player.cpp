#include <math.h>

#include "Common.h"
#include "Player.h"
#include "Input/Input.h"

// �R���X�g���N�^
Player::Player()
{
	// ���W�̏�����
	position = VGet(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, 0);

	// �摜�̓ǂݍ���
	graphHandle = LoadGraph("Textures/Player/Player.png");

	// �Q�[�W�摜
	gauseGraph = LoadGraph("Textures/Player/Gauge.png");

	graphHandle2 = LoadGraph("Textures/UI/AButton.png");

	// �f�b�h�]�[���ݒ�
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.9);
}

// ������
void Player::Initialize()
{
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

	rotationSum = 0;

	velocity = 0;

	timer = 10;

	angle=0;

	powerAdd = 0;

	isStartTimer = false;

	prevTimer = 0;

	// �t���O������
	prevFrameInput = false;

	pushFlg = false;
}

// ��Ԃ̍X�V
void Player::Update(float deltaTime)
{
	//// �X�^�[�g�^�C�}�[�t���O�������Ă����� �^�C�}�[���J�n������
	//if (isStartTimer)
	//{
	//	// ��b�̌o�߂𔻒�
	//	if (GetNowCount() - prevTimer >= 1000)
	//	{
	//		// �^�C�}�[�̌���
	//		timer--;

	//		// �^�C�}�[�v���̂��߂� �O�t���[���̎��ԕۑ�
	//		prevTimer = GetNowCount();
	//	}
	//}

	// �^�C�}�[��0��艺 ���� �{�^����������Ă��Ȃ��Ȃ�
	if (power>100 && !pushFlg)
	{
		// �{�^���������ꂽ�� 
		if (Input::IsPress1P(ButtonID::BUTTON_ID_A))
		{
			pushFlg = true;
		}

		if (pushFlg)
		{
			if (angle >= DX_PI_F / 180 * 82.5 &&
				angle <= DX_PI_F / 180 * 97.5)
				powerAdd = 2;
			else if (angle >= DX_PI_F / 180 * 55 &&
				angle <= DX_PI_F / 180 * 125)
				powerAdd = 1.5;
			else if (angle >= DX_PI_F / 180 * 22.5 &&
				angle <= DX_PI_F / 180 * 157.5)
				powerAdd = 1;

			velocity = power * powerAdd;
		}
	}

	float x = acos(playerAngle);
	float y = asin(playerAngle);

	if (timer >= 0)
	{

		// �Q�[���p�b�h�̃A�i���O�X�e�B�b�N�̓��͗ʂ��擾
		GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

		// �X�e�B�b�N�̓��͂���p�x���Z�o
		inputAngle = atan2(inputY, inputX);

		// �X�e�B�b�N�̊p�x�� 0 ~ 2�� �ɂ���
		if (inputAngle < 0)
		{
			inputAngle = DX_PI_F * 2 + inputAngle;
		}

		// �O�t���[�� �� �X�e�B�b�N����͂��Ă���Ȃ� �O�̃t���[���Ƃ� �p�x�̍� ���o��
		if (prevFrameInput)
		{
			// �O�t���[�� �� ���݂̃t���[�� �� �p�x�̍��̐�Βl �� ���߂�
			angleBetween = fabs(prevInputAngle - inputAngle);
		}
		// �O�t���[���ł̓��͂��Ȃ���΍��� 0 �Ƃ���
		else
		{
			angleBetween = 0.0;
		}

		// �p�x�̍��̐�Βl�� 0 �Ȃ� ���͖��� �Ƃ��� �p���[ �� ��]���v�� �� ���炷
		if (fabs(angleBetween) == 0.0)
		{
			// �p���[������Ȃ猸�炷
			if (power > 0) {
				// �p���[����
				power -= 0.1;

				// ��]���v�� ���� 
				rotationSum -= (rotationSum / fabs(rotationSum))*0.1;
			}
			// �p���[���Ȃ��Ȃ� 0 �ɃZ�b�g
			else {

				// �p���[���Z�b�g
				power = 0;

				// ��]���v�� ���Z�b�g
				rotationSum = 0;
			}

		}

		// �O�t���[���ŁA���͂��������Ȃ�A�O�t���[���̊p�x�ƌ��݃t���[���̊p�x�Ƃ̂Ȃ��p���A���ςŋ��߂�
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

		if (prevFrameInput && angleBetween != 0.0f)
		{
			rotationSum += angleBetween;
			power = fabs(rotationSum);
		}

		playerAngle += DX_PI_F / 180 * (rotationSum / 10);

		if (fabs(inputX) + fabs(inputY) > 0)
		{
			prevFrameInput = true;
			prevInputAngle = inputAngle;
			prevInputX = inputX;
			prevInputY = inputY;

			if (!isStartTimer)
			{
				isStartTimer = true;
				prevTimer = GetNowCount();
			}
		}
		else
		{
			prevFrameInput = false;
		}
	}
}

void Player::Draw()
{
	DrawRotaGraph(position.x, position.y, 0.5, playerAngle, graphHandle, TRUE);

	if (power>100)
	{
		DrawGraph(position.x, position.y - 128, gauseGraph, TRUE);
		DrawGraph(position.x + 150, position.y - 200, graphHandle2, TRUE);

	}

	//VECTOR rotationVector = VTransform(VGet(0, 50, 0), MGetRotZ(playerAngle));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(255, 255, 255));
	//rotationVector = VTransform(VGet(100, 0, 0), MGetRotZ(DX_PI_F / 180.0 * 7.5));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(255, 255, 0));
	//rotationVector = VTransform(VGet(100, 0, 0), MGetRotZ(-DX_PI_F / 180.0 * 7.5));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(0, 255, 0));


	/*printfDx("\nTimer : %d", timer);
	printfDx("\nplayerAngle %f", playerAngle);
	printfDx("\nangle %f", angle);*/
	//printfDx("X %d Y %d", inputX, inputY);
	//printfDx("\nangle %f", inputAngle);
	//printfDx("\nangleBetween %f", angleBetween);
	/*printfDx("\npower %f", power);
	printfDx("\npowerAdd %f", powerAdd);
	printfDx("\nvelocity %f", velocity);*/
	//printfDx("\nprevFrameInput %s", prevFrameInput ? "true" : "false");
}


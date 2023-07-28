#include "DxLib.h"
#include "Shark.h"
#include "Common.h"
#include <math.h>

#define PI 3.141592

Shark::Shark()
{
	x = 0;
	y = 0;

	image = LoadGraph("Textures/Shark/Shark.png");
	imageAngle = 0;

	stateType = PlayerRound;
	ModeChange(Up);
}

void Shark::Update()
{	
	switch (stateType)
	{
	case Shark::PlayerRound:
		UpdatePlayerRound();
		break;
	case Shark::SharkRound:
		UpdateSharkRound();
		break;
	case Shark::End:
		break;
	default:
		break;
	}
}

void Shark::Draw()
{
	DrawRotaGraph(x,y,magnification,angle,image,true,true);
}

Shark::~Shark()
{
	DeleteGraph(image);
}

void Shark::UpdatePlayerRound()
{
	//�v���C���[�̊p�x�Ɋ�Â��ĉ�]����(�Ƃ肠�������Őݒ肷��)
	imageAngle++;
	if (imageAngle == 24)
	{
		imageAngle = 0;//�摜�̊p�x(��)
	}
	angle = (PI / 6) * imageAngle;
	float playerSize = 500; //�v���C���[�̔��a�̃T�C�Y�i�����߁j

	//�v���C���[�̑傫�������Ƃɉ摜�̕\������ʒu��␳
	float pxValue = cosf(angle) * playerSize;
	float pyValue = sinf(angle) * playerSize;

	x = SCREEN_WIDTH / 2 + pxValue; //SCREEN / 2 �̕����̓v���C���[�̒��S���W
	y = SCREEN_HEIGHT / 2 + pyValue;

	//�v���C���[�����b������T���̏�������ݒ肷��
	//stateType = SharkRound;
	//x = (SCREEN_WIDTH / 2) - 300;
	//y = 390;
	//ModeChange(Up);
}

void Shark::UpdateSharkRound()
{
	//���[�h�Ԋҁi���͋����Œ����j
	if (y < 400)
	{
		ModeChange(Stay);
	}
	else if(y > 600)
	{
		ModeChange(Down);
	}

	//�ړ�
	y += flyY;

	//��]������
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	angle = (PI / 6) * imageAngle;
}

void Shark::ModeChange(Mode mode)
{
	switch (mode)
	{
	case Shark::Up:
		flyY = -3;
		break;
	case Shark::Stay:
		flyY = 0.1;
		break;
	case Shark::Down:
		flyY = 3;
		break;
	default:
		break;
	}
}
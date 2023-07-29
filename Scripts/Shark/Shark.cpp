#include "DxLib.h"
#include "Shark.h"
#include "Common.h"
#include <math.h>

Shark::Shark()
{
	image = LoadGraph("Textures/Shark/Shark.png");
	LoadDivGraph("Textures/Shark/effect.png", effectXNum * effectYNum, effectXNum, effectYNum, effectXSize, effectYSize, effectImg);

	Init();
}

void Shark::Update(float deltaTime)
{	
	switch (stateType)
	{
	case Shark::PlayerRound:
		UpdatePlayerRound(deltaTime);
		break;
	case Shark::Turn:
		UpdateTurn(deltaTime);
	case Shark::SharkRound:
		UpdateSharkRound(deltaTime);
		break;
	case Shark::End:
		break;
	default:
		break;
	}
}

void Shark::Draw()
{
	//if (stateType == SharkRound) //�G�t�F�N�g��SharkR�̂ݕ`��
	//{
	//	DrawRotaGraph3((SCREEN_WIDTH / 2),SCREEN_HEIGHT / 2,effectXSize - 150,effectYSize / 2,
	//		1, 1,eAngle, effectImg[effectHandle], true);
	//}

	printfDx("\n%f", effectAngle);

	DrawRotaGraph(x, y, sharkMagnification, iangle, image, true, true);
}

Shark::~Shark()
{
	DeleteGraph(image);
	for (int i = 0; i < effectXNum * effectYNum; i++)
	{
		DeleteGraph(effectImg[i]);
	}
}

void Shark::Init()
{
	x = playerX + cosf(0.0f) * playerSize;
	y = playerY + sinf(0.0f) * playerSize;
	iangle = 0.0f;
	imageAngle = 0;
	effectHandle = 0;
	endFlag = false;
	isThrow = false;
	isLandsOnWater = false;
	stateType = PlayerRound;
}

void Shark::UpdatePlayerRound(float deltaTime)
{
	//�v���C���[�̊p�x�Ɋ�Â��ĉ�]����(�Ƃ肠�������Őݒ肷��)
	/*imageAngle++;
	if (imageAngle == 24)
	{
		imageAngle = 0;//�摜�̊p�x(��)
	}
	iangle = (DX_PI_F / 6) * imageAngle;*/

	iangle = playerAngle;

	//�v���C���[�̑傫�������Ƃɉ摜�̕\������ʒu��␳
	float pxValue = cosf(iangle) * playerSize;
	float pyValue = sinf(iangle) * playerSize;

	x = playerX + pxValue;
	y = playerY + pyValue;

	//�v���C���[�����b������T���̏�������ݒ肷��
	if (isThrow)
	{
		InitTurn();
	}
}

void Shark::InitSharkRound()
{
	stateType = SharkRound;
	x = (SCREEN_WIDTH / 2) - 300;
	y = SCREEN_HEIGHT;

	//�X�R�A�����Ԏ��Ԍv�Z
	float score = maxScore; //���ɍő�l
	float allTime = score / maxScore * maxTime;
	if (allTime > 6.0f)
	{
		upTime = 3.0f;
		stayTime = allTime - 6.0f;
		downTime = 3.0f;
	}
	else
	{
		upTime = allTime / 2;
		downTime = allTime - upTime;
	}
	ModeChange(Up);
	effectAngle = -45;
}

void Shark::UpdateSharkRound(float deltaTime)
{
	//���[�h�Ԋҁi���͋����Œ����j
	switch (mode)
	{
	case Shark::Up:
		upTime -= deltaTime;
		if (upTime <= 0)
		{
			ModeChange(Stay);
		}
		break;
	case Shark::Stay:
		stayTime -= deltaTime;
		if (upTime <= 0)
		{
			ModeChange(Down);
		}
		break;
	case Shark::Down:
		downTime -= deltaTime;
		if (downTime <= 0)
		{
			isLandsOnWater = true;
		}
		break;
	default:
		break;
	}

	//�ړ�
	y += flyY;

	//��]������
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	iangle = (DX_PI_F / 6) * imageAngle;

	//�G�t�F�N�g�̓Y�����ԍ���ύX
	if (effectHandle == 17)
	{
		effectHandle = 0;
	}
	else
	{
		effectHandle++;
	}

	//�G�t�F�N�g�̃A���O������
	effectAngle += eAValue;

	eAngle = DX_PI_F / 180 * effectAngle;

	
}

void Shark::InitTurn()
{
	x = 0;
	y = SCREEN_HEIGHT;

	stateType = Turn;
}

void Shark::UpdateTurn(float deltaTime)
{
	//��]
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	iangle = (DX_PI_F / 6) * imageAngle;

	//�ړ�
	x += 5;
	y += -3;

	if (x >= SCREEN_WIDTH)
	{
		endFlag = true;
	}
}

void Shark::ModeChange(Mode mode)
{
	switch (mode)
	{
	case Shark::Up:
		flyY = -3;
		eAValue = 45 / upTime;
		this->mode = Up;
		break;
	case Shark::Stay:
		flyY = 0.1;
		eAValue = 0;
		this->mode = Stay;
		break;
	case Shark::Down:
		flyY = 3;
		eAValue = 45 / downTime;
		this->mode = Down;
		break;
	default:
		break;
	}
}
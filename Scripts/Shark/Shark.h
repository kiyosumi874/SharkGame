
#pragma once
class Shark
{
public:
	Shark();
	~Shark();
	void Update();
	void Draw();
	void UpdatePlayerRound();
	void UpdateSharkRound();
private:
	enum StateType
	{
		PlayerRound,
		SharkRound,
		End
	};

	enum Mode
	{
		Up,
		Stay,
		Down
	};

	

	void ModeChange(Mode mode);

	float x;
	float y;

	int image;
	float imageAngle;
	const double magnification = 0.3;

	float flyY;
	float angle;
	
	StateType stateType;
	Mode mode;
};


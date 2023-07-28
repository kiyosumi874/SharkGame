#pragma once
#include <DxLib.h>

class Player {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// 状態の更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	void Update(float deltaTime);

	void Draw();

private:

	VECTOR position;		// 座標ベクトル

	VECTOR v1;

	int inputX, inputY;		// パッドのアナログスティック入力

	int prevInputX, prevInputY;

	int graphHandle;		// 画像ハンドル

	float power;			// 飛ばす力

	float inputAngle;		// スティックの入力角度

	float prevInputAngle;	// 前フレームでの入力角度

	float angleBetween;

	float playerAngle;

	float playerAngleAdd;

	bool prevFrameInput;	// 前のフレームで入力があったか
};
#pragma once
#include"../Utility/Vector2D.h"

//playerの状態
enum ePlayerState
{
	IDLE,   //待機
	WALK,   //歩く
	SHOOT,   //撃つ
};

class Player
{
private:
	int  player_image;   //playerの画像

	Vector2D location;   //位置座標
	float angle;         //角度



public:
	Player();	//コンストラクタ
	~Player();	//デストラクタ

	void Initialize(int pnum, float x);         //初期化処理
												// pnumは何番目のPlayerなのか？
												// x はPlayerのx座標

	void Update();								//更新処理
	void Draw()const;							//描画処理
	void Finalize();							//終了時処理

	ePlayerState player_state;   //playerの状態
};


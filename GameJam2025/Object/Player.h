﻿#pragma once
#include"../Utility/Vector2D.h"

//playerの状態
enum ePlayerState
{
	IDLE,   //待機
	WALK,   //歩く
	SHOOT,   //撃つ
	WIN,    //勝ち
	LOSS,   //負け
};

class Player
{
protected:

private:
	int fps;   //フレームレート
	bool is_sound_played; // SEが再生されたかどうかを管理するフラグ
	
	int animation[2];   //アニメーション画像
	int animation_count;//アニメーション時間
	float animation_time;//
	int  player_image;   //playerの画像
	int Player1;   //プレイヤー１
	int Player2;   //プレイやー２

	Vector2D location;   //位置座標
	Vector2D velocity;      //移動速度
	Vector2D direction;   //進行方向

	float angle;         //角度

	static Player* instance;
	Player* player;
	int flip_flag;   //画像反転フラグ
	int utu_SE;     //撃つSE
	float rotation_angle;  // 画像の回転角度（LOSSのとき使用）
	float rotation_speed;   // 回転速度（LOSS時に使用）

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
	static Player* GetInstance();

private:
	void Animecount(float delta_second);
	void Movement(float delta_second);
};


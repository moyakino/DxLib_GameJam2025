#pragma once
#include"../Utility/Vector2D.h"

/* Player2の描画をPlayer1からどれだけずらすか*/
#define PLAYER2SHIFT 100

//playerの状態
enum ePlayerState
{
	IDLE,   //待機
	WALK,   //歩く
	WALK_IDLE,//歩いた後の待ち状態
	SHOOT,   //撃つ
	WIN,    //勝ち
	WIN2,   //負け
	RESET  //戻る
};

class Player
{
protected:

private:
	int fps;   //フレームレート
	bool is_sound_played; // SEが再生されたかどうかを管理するフラグ
	
	int animation[2];   //アニメーション画像
	int animation_count;//アニメーション時間

	int  player_image;   //playerの画像

	int PlayerName_image[2]; //PlayerName

	Vector2D location;   //位置座標 Player1用
	Vector2D location2;  //位置座標 Player2用
	Vector2D direction;   //進行方向
	Vector2D direction2;   //進行方向

	float angle;         //角度

	int flip_flag;   //画像反転フラグ
	int utu_SE;     //撃つSE
	int run_SE;     //歩くSE
	int down_SE;    //倒れるSE
	float rotation_angle;  // 画像の回転角度（LOSSのとき使用）
	float rotation_speed;   // 回転速度（LOSS時に使用）

	bool death_flg;      //負けフラグ
	int playernum;      //プレイヤーの番号
	float darkening_alpha;  // 暗転の透明度
	bool is_darkening;      // 暗転のフラグ
	float darkening_time;   // 暗転時間（秒）
	bool has_rotated;       // 回転したかどうかのフラグ
	bool has_location;

	int loss_image;  // 負けた時の画像
	int win_image;	 //勝った時の画像
	int player_SHOOT;//撃ってる時の画像

	int Complete;	//入力が完了したか(勝敗判定終了)
	bool IdleTiming;

	bool WinLoseDisplayFlag; //勝敗表示用

	bool FadeOutFlag;	//暗転フラグ

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

	bool GetDeathFlg() const;//敗北取得

	void GetInputCompleteNotice(int CompleteNum);
	void SetWinLoseflg(bool flg);

	void SetIdleTiming(bool Timing);

private:
	void Animecount();
	void Movement(float delta_second);
};


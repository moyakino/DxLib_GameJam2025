#include "Player.h"

#include "DxLib.h"

Player::Player() :
	player_state(ePlayerState::WALK),//playerの初期状態
	player_image(NULL), //player画像
	fps(0),             //フレームレート
	flip_flag(FALSE),   //画像反転用フラグ
	is_sound_played(false),//SEのフラグ
	rotation_angle(0.0f),  //初期回転角度
	rotation_speed(1.5f),   // 1フレームごとに回転する速度
	animation_count(0),
	darkening_alpha(0.0f), // 初期値は透明（暗転していない）
	is_darkening(false),   // 初期は暗転していない
	darkening_time(0.0f),  // 初期時間
	has_rotated(false),     // 初期は回転していない
	has_location(false),
	Complete(-1),
	run_SE(NULL),
	utu_SE(NULL),
	down_SE(NULL),
	down_se_flg(NULL),
	IdleTiming(false),
	WinLoseDisplayFlag(false),
	FadeOutFlag(false),
	location(0.0f, 0.0f),
	location2(0.0f, 0.0f),
	direction(0.0f, 0.0f),
	direction2(0.0f, 0.0f),
	win_image(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
	PlayerName_image[0] = NULL;
	PlayerName_image[1] = NULL;
	loss_image = LoadGraph("Resource/images/player3.png");  // 倒れた画像
	player_SHOOT = LoadGraph("Resource/images/player_BUNG.png");  // 倒れた画像
}

Player::~Player()
{
}

//初期化処理
void Player::Initialize(int pnum, float x)
{

	animation[0] = LoadGraph("Resource/images/player1.png");
	animation[1] = LoadGraph("Resource/images/player2.png");

	PlayerName_image[0] = LoadGraph("Resource/images/player_name1.png");
	PlayerName_image[1] = LoadGraph("Resource/images/player_name2.png");

	win_image = LoadGraph("Resource/images/player4.png");

	//画像の読み込み
	player_image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);
	direction2 = Vector2D(-1.0f, 0.0f);

	//初期位置の設定
	location.x = 520;
	location.y = 310;

	location2.x = 420 - PLAYER2SHIFT;
	location2.y = 310;

	//初期画像反転の設定
	//flip_flag = FALSE;

	//負けフラグ初期化処理
	death_flg = false;

	//SE・BGM
	utu_SE = LoadSoundMem("Resource/sound/Gunfire.wav");
	run_SE = LoadSoundMem("Resource/sound/step.wav");
	down_SE = LoadSoundMem("Resource/sound/down.wav");

	//エラーチェック
	if (utu_SE == -1)
	{
		throw("SEありません\n");
	}

}

//更新処理
void Player::Update()
{
	// フレームレート
	fps++;

	switch (player_state)
	{
		//止まっている状態
		//画面中央で止まってるとき
	case ePlayerState::IDLE:
		player_image = animation[0];
		//flip_flag = FALSE;  // 画像反転フラグをリセット
		location.x = 520;  // Player1 元の位置に戻す
		location.y = 310;
		location2.x = 420 - PLAYER2SHIFT;  // Player2 元の位置に戻す
		location2.y = 310;
		direction = Vector2D(1.0f, 0.0f);
		direction2 = Vector2D(-1.0f, 0.0f);
		//is_sound_played = false;   //音のフラグをリセット
		//rotation_angle = 0.0f;//回転角度を戻す
		//FadeOutFlag = false;	//暗転しない
		//WinLoseDisplayFlag = false; //勝敗表示なし
		Complete = -1;
		IdleTiming = false; 
		is_sound_played = false;
		down_se_flg = false;
		player_state = ePlayerState::WALK;
		break;


		//歩き出している状態
	case ePlayerState::WALK:
		Animecount();
		Movement(fps);
		// 画面端で反転
		int player_width;
		GetGraphSize(player_image, &player_width, nullptr);

		/* 画面端まで動いたら反転 */
		if (location.x <= 0 || location.x + player_width >= 1280)
		{
			direction.x = 0;
			//flip_flag = TRUE;
			player_state = ePlayerState::WALK_IDLE;
		}
		
		rotation_angle = 0.0f;//回転角度を戻す
		break;

		//歩いた後の待機状態
	case ePlayerState::WALK_IDLE:
		player_image = animation[0];
		is_sound_played = false;   //音のフラグをリセット
		rotation_angle = 0.0f;//回転角度を戻す

		/* 勝敗が判定中以外になると撃つ状態に移行 */
		if (Complete >= 0 && Complete <= 2)
		{
			player_state = ePlayerState::SHOOT;
		}

		break;
		

		//撃つ状態
	case ePlayerState::SHOOT:

		/* Player1 勝ち */
		if (WinLoseDisplayFlag == true && Complete == 1)
		{
			player_state = ePlayerState::WIN;
		}
		/* Player2 勝ち */
		else if (WinLoseDisplayFlag == true && Complete == 2)
		{
			player_state = ePlayerState::WIN2;
		}

		break;


	case WIN:

		if (CheckSoundMem(utu_SE) != TRUE && is_sound_played == false)
		{
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE);
			is_sound_played = true;
		}

		if (CheckSoundMem(down_SE) != TRUE && down_se_flg == false)
		{
			PlaySoundMem(down_SE, DX_PLAYTYPE_BACK, TRUE);
			down_se_flg = true;
		}


		if (WinLoseDisplayFlag == false)
		{
			player_state = ePlayerState::RESET;
		}

		break;

		//負けた状態
	case ePlayerState::WIN2:

		if (CheckSoundMem(utu_SE) != TRUE && is_sound_played == false)
		{
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE);
			is_sound_played = true;
		}

		if (CheckSoundMem(down_SE) != TRUE && down_se_flg == false)
		{
			PlaySoundMem(down_SE, DX_PLAYTYPE_BACK, TRUE);
			down_se_flg = true;
		}

		if (WinLoseDisplayFlag == false)
		{
			player_state = ePlayerState::RESET;
		}

		break;


		//やり直し
	case ePlayerState::RESET:

		if (IdleTiming == true)
		{
			player_state = ePlayerState::IDLE;
		}

		break;
	default:
		break;
	}
	//フレームレートのリセット
	if (fps > 59)
	{
		fps = 0;
	}
}

//描画処理
void Player::Draw() const
{
	//テストFPS描画
	//DrawFormatString(0, 700, GetColor(255, 255, 255), "fps::%d", fps);
	//DrawFormatString(0, 500, GetColor(255, 255, 255), "animation_count::%d", animation_count);

	int width, height;
	GetGraphSize(player_image, &width, &height); // 画像の幅と高さを取得

	switch (player_state)
	{
	case WALK:
		/* Player1 右側 */
		/* 画面端まで歩く */
		DrawGraphF(location.x, location.y, player_image, TRUE);
		/* Player2 左側 */
		/* 画面端まで歩く */
		DrawTurnGraphF(location2.x - 30, location.y, player_image, TRUE);
		break;
	case WALK_IDLE:
		/* Player1 構える */
		DrawTurnGraphF(location.x, location.y, player_SHOOT, TRUE);
		/* Player2 構える */
		DrawGraphF(location2.x - 30, location.y, player_SHOOT, TRUE);
		break;
	case WIN:
		/* Player1 勝ち Player2 負け */
		DrawTurnGraphF(location.x, 400, loss_image, TRUE);
		DrawGraphF(location2.x - 30, location.y, player_SHOOT, TRUE);
		break;
	case WIN2:
		/* Player2 勝ち Player1 負け */
		DrawTurnGraphF(location.x, location.y, player_SHOOT, TRUE);
		DrawGraphF(location2.x - 30, 400, loss_image, TRUE);
		break;
	default:
		break;
	}
	// 常に Player1 の名前を描画
	DrawGraphF(location.x + 85, location.y - 100, PlayerName_image[1], TRUE);
	// 常に Player2 の名前を描画
	DrawGraphF(location2.x + 50, location2.y - 100, PlayerName_image[0], TRUE);
}


//終了処理
void Player::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

void Player::Animecount()
{
	// 60フレームごとに切り替え
	//30で割った数が０の時切り替え
	if (fps % 30 == 0)  // 60〜119フレームで切り替え
	{

		//歩くSE
		PlaySoundMem(run_SE, DX_PLAYTYPE_BACK, TRUE);

		// 画像の切り替え（最初の1回のみ）
		if (player_image == animation[0])
		{
			player_image = animation[1];  // animation[1] に切り替え
		}
		else
		{
			player_image = animation[0];
		}
	}
}

//移動処理
void Player::Movement(float delta_second)
{
	// 移動速度の調整
	float speed = 2.0f;
	location += direction * speed;

	location2 += direction2 * speed;
}

//負け取得
bool Player::GetDeathFlg() const
{
	return this->death_flg;
}

void Player::GetInputCompleteNotice(int CompleteNum)
{
	// 3が判定中
	// 2がPlayer2の勝ち
	// 1がPlayer1の勝ち
	// 0が引き分け
	Complete = CompleteNum;
}

void Player::SetWinLoseflg(bool flg)
{
	WinLoseDisplayFlag = flg;
}

void Player::SetIdleTiming(bool Timing)
{
	IdleTiming = Timing;
}

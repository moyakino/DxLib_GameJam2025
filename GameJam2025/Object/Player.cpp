#include "Player.h"

#include "DxLib.h"

Player* Player::instance = nullptr;

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
	ShootTiming(3),
	Resetflg(false)
{
	animation[0] = NULL;
	animation[1] = NULL;
	loss_image = LoadGraph("Resource/images/player3.png");  // 倒れた画像
}

Player::~Player()
{
}

//初期化処理
void Player::Initialize(int pnum, float x)
{

	animation[0] = LoadGraph("Resource/images/player1.png");
	animation[1] = LoadGraph("Resource/images/player2.png");

	//画像の読み込み
	player_image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);

	//初期位置の設定
	location.x = 520;
	location.y = 310;

	//初期画像反転の設定
	flip_flag = FALSE;

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
		velocity.x = 0;   //移動
		is_sound_played = false;   //音のフラグをリセット
		rotation_angle = 0.0f;//回転角度を戻す
		break;


		//歩き出している状態
	case ePlayerState::WALK:
		flip_flag = FALSE;  // WALKでも元に戻す

		if (!is_sound_played)   //音が再生されていないとき
		{
			//ChangeVolumeSoundMem(200, run_SE);   //音量調整
			PlaySoundMem(run_SE, DX_PLAYTYPE_BACK, TRUE);   //音を再生
			is_sound_played = true;   //音が再生されたことを記憶させる
		}
		Animecount();
		Movement(fps);
		// 画面端で反転
		int player_width;
		GetGraphSize(player_image, &player_width, nullptr);

		if (location.x <= 0 || location.x + player_width >= 1280)
		{
			direction.x = 0;
			flip_flag = TRUE;
			player_state = ePlayerState::WALK_IDLE;
		}

		/* 入力が終わったら撃つ状態に移行 */
		if (ShootTiming != 3)
		{
				player_state = ePlayerState::SHOOT;
		}
		
		rotation_angle = 0.0f;//回転角度を戻す
		break;


		//歩いた後の待機状態
	case ePlayerState::WALK_IDLE:
		player_image = animation[0];
		velocity.x = 0;   //移動
		is_sound_played = false;   //音のフラグをリセット
		rotation_angle = 0.0f;//回転角度を戻す
		if (fps == 59)
		{
			player_state = ePlayerState::LOSS;
		}
		break;
		

		//撃つ状態
	case ePlayerState::SHOOT:
		if (CheckSoundMem(utu_SE) != TRUE)
		{
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE);
			player_state = ePlayerState::LOSS;
			is_sound_played = false;  // ここでリセット
		}
		flip_flag = TRUE;
		rotation_angle = 0.0f;
		break;


		//負けた状態
	case ePlayerState::LOSS:
		darkening_time += 0.09f;  // ここで暗転時間が増加する
		if (darkening_time >= 1.0f && !has_rotated)
		{
			PlaySoundMem(down_SE, DX_PLAYTYPE_BACK, TRUE);
			player_image = loss_image;
			has_rotated = true;
		}
		////リセットされたら
		//if (Resetflg == true)
		//{
		//	darkening_time = 0;

		//	player_state = ePlayerState::RETURN;
		//}
		if (fps == 59)
		{
			player_state = ePlayerState::RETURN;
		}
		break;


		//やり直し
	case ePlayerState::RETURN:

		darkening_time = 0.0f;  // 暗転を解除（すぐに明るくする）


		if (darkening_time < 3.0f)  // 2秒間暗転を維持
		{
			if (!has_location)  // まだ位置を戻していない場合
			{
				/* 再設定 */
				//location.x = 520;  // 元の位置に戻す
				//location.y = 310;
				velocity.x = 0;   //移動
				flip_flag = FALSE;  // 画像反転フラグをリセット
				has_location = true;  // 位置を戻したことを記録
			}

			darkening_time += 0.09f; // 暗転時間を増加
		}
		else  // 暗転が終了したら明るくする
		{
			location.x = 520;  // 元の位置に戻す
			location.y = 310;
			darkening_time = 0.0f;  // 暗転を解除（すぐに明るくする）
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
	DrawFormatString(0, 700, GetColor(255, 255, 255), "fps::%d", fps);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "animation_count::%d", animation_count);
	//DrawFormatString(0, 100, GetColor(255, 255, 255), "fps::%d", fps);
	//DrawFormatString(0, 600, GetColor(255, 255, 255), "player_state::%s", player_state);

	int width, height;
	GetGraphSize(player_image, &width, &height); // 画像の幅と高さを取得

	if (player_state == ePlayerState::LOSS || player_state == ePlayerState::RETURN)
	{
		if (darkening_time < 1.0f)
		{
			DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		}
		else if (darkening_time == 0.0f)
		{
			DrawTurnGraph(location.x, location.y, player_image, TRUE);
		}

		if (darkening_time >= 1.0f && player_state == ePlayerState::LOSS)
		{
			//倒れた画像の描画
			DrawRotaGraph(location.x + width / 2, location.y + height / 2 + 100, 1.0, rotation_angle, player_image, TRUE);
		}
	}
	else
	{
		/* 負けの時か 再設定の時 */
		if (flip_flag)
		{
			DrawTurnGraph(location.x, location.y, player_image, TRUE);
		}
		else
		{
			DrawGraph(location.x, location.y, player_image, TRUE);
		}
	}
}


//終了処理
void Player::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);

	delete instance;
}

//インスタンス取得処理
Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

void Player::Animecount()
{
	// 60フレームごとに切り替え
	//30で割った数が０の時切り替え
	if (fps % 30 == 0)  // 60〜119フレームで切り替え
	{
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

void Player::SetResetflg(bool flg)
{
	Resetflg = flg;
}

void Player::SetShootTiming(int Timing)
{
	ShootTiming = Timing;
}

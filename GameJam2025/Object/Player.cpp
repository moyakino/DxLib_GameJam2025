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
	Complete(-1)
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
	case ePlayerState::IDLE:
		player_image = animation[0];
		velocity.x = 0;   //移動
		is_sound_played = false;   //音のフラグをリセット
		flip_flag = FALSE;  // IDLEでは元に戻す
		rotation_angle = 0.0f;//回転角度を戻す
		break;
		//歩き出している状態
	case ePlayerState::WALK:

		Animecount();

		Movement(fps);
		//テストif文
		if (fps == 59)
		{
				player_state = ePlayerState::SHOOT;
		}
		flip_flag = FALSE;  // WALKでも元に戻す
		rotation_angle = 0.0f;//回転角度を戻す
		break;
		//撃つ状態
	case ePlayerState::SHOOT:
		//テストif文
		if (fps == 59)
		{
			player_state = ePlayerState::LOSS;

		}
		flip_flag = TRUE;  // SHOOT時に画像を反転
		rotation_angle = 0.0f;//回転角度を戻す
		break;
	case ePlayerState::WIN:
		rotation_angle = 0.0f;
		break;
	case ePlayerState::LOSS:
		if (!is_sound_played)   //音が再生されていないとき
		{
			ChangeVolumeSoundMem(200, utu_SE);   //音量調整
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE);   //音を再生
			is_sound_played = true;   //音が再生されたことを記憶させる
		}
		darkening_time += 0.09; // 暗転時間を増加

		if (darkening_time >= 1.0f && !has_rotated)  // 1秒後に画像変更＆回転
		{
			player_image = loss_image;  // 倒れた後の画像に変更
			has_rotated = true;
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
	//DrawFormatString(0, 500, GetColor(255, 255, 255), "animation_count::%d", animation_count);

	int width, height;
	GetGraphSize(player_image, &width, &height); // 画像の幅と高さを取得

	if (player_state == ePlayerState::LOSS)
	{
		if (darkening_time < 1.0f)
		{
			DrawBox(0, 0, 1280, 720, GetColor(0, 0, 0), TRUE);
		}

		if (darkening_time >= 1.0f)
		{
			//倒れた画像の描画
			DrawRotaGraph(location.x + width / 2, location.y + height / 2 + 100, 1.0, rotation_angle, player_image, TRUE);
		}
	}
	else
	{
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
	//移動処理
	location += direction;
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

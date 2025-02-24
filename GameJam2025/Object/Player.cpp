#include "Player.h"

#include "DxLib.h"

Player* Player::instance = nullptr;

Player::Player():
	player_state(ePlayerState::WALK),//playerの初期状態
	player_image(NULL), //player画像
	fps(0),             //フレームレート
	flip_flag(FALSE),   //画像反転用フラグ
	is_sound_played(false),//SEのフラグ
	rotation_angle(0.0f),  //初期回転角度
	rotation_speed(1.5f),   // 1フレームごとに回転する速度
	animation_count(0),
	velociy_x(0)
{
	animation[0] = NULL;
	animation[1] = NULL;
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
		flip_flag = FALSE;  // WALKでも元に戻す
		//テストif文
		if (fps == 59)
		{
			player_state = ePlayerState::LOSS;

		}
		rotation_angle = 0.0f;//回転角度を戻す
		break;
		//撃つ状態
	case ePlayerState::SHOOT:
		if (!is_sound_played)   //音が再生されていないとき
		{
			ChangeVolumeSoundMem(200, utu_SE);   //音量調整
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE);   //音を再生
			is_sound_played = true;   //音が再生されたことを記憶させる
		}
		flip_flag = TRUE;  // SHOOT時に画像を反転
		rotation_angle = 0.0f;//回転角度を戻す
		break;
	case ePlayerState::WIN:
		rotation_angle = 0.0f;
		break;
	case ePlayerState::LOSS:
		// 倒れたように見せるための設定
		flip_flag = FALSE; // 左右反転はしない
		if (rotation_angle > -90.0f * DX_PI / 180.0f) // -90度になるまで回転
		{
			rotation_angle -= rotation_speed * DX_PI / 180.0f;  // 徐々に回転
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
	DrawFormatString(0, 100, GetColor(255, 255, 255), "fps::%d", fps);
	DrawFormatString(0, 500, GetColor(255, 255, 255), "animation_count::%d", animation_count);
	int width, height;
	GetGraphSize(player_image, &width, &height); // 画像の幅と高さを取得

	if (player_state == ePlayerState::LOSS)
	{
		// 画像の左上を基準に回転させるため、中心のズレを補正
		DrawRotaGraph(location.x + width / 2, location.y + height / 2, 1.0, rotation_angle, player_image, TRUE);
	}
	else
	{
		if (flip_flag)
		{
			DrawTurnGraph(location.x, location.y, player_image, TRUE);
		}
		else
		{
			DrawRotaGraphF(location.x, location.y, 1.0, 0.0, player_image, TRUE);
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

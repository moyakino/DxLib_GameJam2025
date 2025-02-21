#include "Player.h"

#include "DxLib.h"

Player* Player::instance = nullptr;

Player::Player():
	player_state(ePlayerState::SHOOT),
	player_image(NULL),
	fps(0),
	flip_flag(FALSE),
	is_sound_played(false)
{

	animation[0] = NULL;
	animation[1] = NULL;
}

Player::~Player()
{
}

void Player::Initialize(int pnum, float x)
{

	player_image = LoadGraph("Resource/images/player1.png");
	//画像の読み込み
	switch (pnum)
	{
		//player1
	case 0:
		player_image = LoadGraph("Resource/images/player1.png");
		break;
		//player2
	case 1:
		player_image = LoadGraph("Resource/images/player2.png");
		break;
	default:
		break;
	}

	//エラーチェック
	if (player_image == -1)
	{
		throw("プレイヤーの画像がありません\n");
	}

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);

	//初期位置の設定
	location.x = 520;
	location.y = 310;

	flip_flag = FALSE;

	//SE・BGM
	utu_SE = LoadSoundMem("Resource/sound/Gunfire.wav");

	if (utu_SE == -1)
	{
		throw("SEありません\n");
	}

}

void Player::Update()
{
	//フレームレート
	fps++;

	switch (player_state)
	{
		//止まってる状態
	case ePlayerState::IDLE:
		//player_imageに直立の画像を入れる
		player_image = LoadGraph("Resource/images/player1.png");
		//移動
		velocity.x = 0;
		is_sound_played = false; // 音のフラグをリセット
		break;
		//歩いてる状態
	case ePlayerState::WALK:
		player_image = LoadGraph("Resource/images/player1.png");

		Animecount(fps);
		Movement(fps);
		
		break;
		//撃っている状態
	case ePlayerState::SHOOT:
		if (!is_sound_played) // 音が再生されていない場合のみ
		{
			ChangeVolumeSoundMem(255, utu_SE);
			PlaySoundMem(utu_SE, DX_PLAYTYPE_BACK, TRUE); // 音を再生
			is_sound_played = true; // 音が再生されたことを記録
		}
		//画像反転させたい
		flip_flag = TRUE;
		break;
	default:
		break;
	}

	if (fps > 59)
	{
		fps = 0;
	}
}

void Player::Draw() const
{
	
	DrawFormatString(0, 100, GetColor(255, 255, 255), "fps::%d", fps);
	//画像描画
	DrawGraph(location.x, location.y, player_image, TRUE);
}

void Player::Finalize()
{
}

Player* Player::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Player();
	}
	return instance;
}

void Player::Animecount(float delta_second)
{
	//// 移動中のアニメーション
	//animation_time += delta_second;
	//if (animation_time >= (1.0f / 8.0f))
	//{
	//	animation_time = 0.0f;
	//	animation_count++;
	//	if (animation_count >= 2)
	//	{
	//		animation_count = 0;
	//	}
	//	// 画像の設定
	//	player_image = animation[animation_num[animation_count]];
	//}
}

void Player::Movement(float delta_second)

{
	//移動処理
	location += direction;
}

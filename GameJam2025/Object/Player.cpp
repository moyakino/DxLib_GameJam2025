#include "Player.h"

#include "DxLib.h"

Player* Player::instance = nullptr;

Player::Player():
	player_state(ePlayerState::IDLE),
	player_image(NULL),fps(0)
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

		break;
	case ePlayerState::WALK:
		Animecount(fps);
		Movement(fps);
		
		break;
	case ePlayerState::SHOOT:
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
	DrawGraph(0, 0, player_image, FALSE);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "fps::%d", fps);
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
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 8.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		// 画像の設定
		player_image = animation[animation_num[animation_count]];
	}
}

void Player::Movement(float delta_second)
{
	velocity.x += 1.0f;

	if (velocity.x == 50.0f)
	{
		velocity.x = 0;
	}
}

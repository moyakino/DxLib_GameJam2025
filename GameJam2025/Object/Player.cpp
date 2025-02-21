#include "Player.h"

#include "DxLib.h"

Player* Player::instance = nullptr;

Player::Player():
	player_state(ePlayerState::IDLE),
	player_image(NULL)
{
	animation[0] = LoadGraph("Resource/images/player.png");
	animation[1] = NULL;
}

Player::~Player()
{
}

void Player::Initialize(int pnum, float x)
{

	player_image = animation[0];
	////画像の読み込み
	//switch (pnum)
	//{
	//case 0:
	//	player_image = LoadGraph("Resource/images/player.png");
	//	break;
	//case 1:
	//	player_image = LoadGraph("Resource/images/player.png");
	//	break;
	//default:
	//	break;
	//}

	//エラーチェック
	if (player_image == -1)
	{
		throw("Resource / images / player.pngがありません\n");
	}
}

void Player::Update()
{
}

void Player::Draw() const
{
	DrawGraph(0, 0, animation[0], FALSE);
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

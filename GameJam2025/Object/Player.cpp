#include "Player.h"

#include "DxLib.h"

Player::Player():
	player_state(ePlayerState::IDLE),
	player_image(NULL)
{

}

Player::~Player()
{
}

void Player::Initialize(int pnum, float x)
{
	//画像の読み込み
	switch (pnum)
	{
	case 0:
		player_image = LoadGraph("Resource/images/player.bmp");
		break;
	case 1:
		player_image = LoadGraph("Resource/images/player.bmp");
		break;
	default:
		break;
	}

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
	DrawRotaGraphF(location.x, location.y, 1.0, angle, player_image, TRUE);
}

void Player::Finalize()
{
}

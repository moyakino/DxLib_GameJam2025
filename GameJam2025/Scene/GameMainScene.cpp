#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"
#include<random>

#include "../Object/Player.h"

GameMainScene::GameMainScene():player(nullptr)
{
}

GameMainScene::~GameMainScene()
{
}

//初期化処理
void GameMainScene::Initialize()
{
	/*CreateObject<Player>(Vector2D(320.0f, 94.0f));*/
	player = Player::GetInstance();
	player->Initialize(0, 0.0);
}

//更新処理
eSceneType GameMainScene::Update()
{

	player->Update();
	

	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_RANKING;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void GameMainScene::Draw() const
{
	DrawString(0, 0, "GameMainScene", GetColor(255, 255, 255));

	//テスト コントローラーの入力 2Player分取得
	DrawFormatString(0, 200, GetColor(255, 255, 255), 
		"Player1::%d  Player2::%d", InputControl::GetButtonDown(XINPUT_BUTTON_B, 0), InputControl::GetButtonDown(XINPUT_BUTTON_B, 1));

	player->Draw();

}

//終了時処理
void GameMainScene::Finalize()
{
	delete player;
}

//現在のシーン情報を取得
eSceneType GameMainScene::GetNowScene() const
{
    return eSceneType::E_MAIN;
}

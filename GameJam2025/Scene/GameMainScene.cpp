#include "GameMainScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#include "../Object/Player.h"

GameMainScene::GameMainScene()
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

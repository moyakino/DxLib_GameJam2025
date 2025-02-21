#include "TitleScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

TitleScene::TitleScene() :background_image(NULL), gametitle_image(NULL), cursor_image(NULL),
start_image(NULL),end_image(NULL),cursor_num(0)
{
}

TitleScene::~TitleScene()
{
}

//初期化処理
void TitleScene::Initialize()
{
	background_image = LoadGraph("Resource/Images/");
	gametitle_image = LoadGraph("Resource/Images/");
	start_image = LoadGraph("Resource/Images/");
	cursor_image = LoadGraph("Resource/Images/");
	end_image = LoadGraph("Resource/Images/");

	title_sound = LoadSoundMem("Resource/sound/");
	button_sound = LoadSoundMem("Resource/sound/");
	cursor_sound = LoadSoundMem("Resource/sound/");

	
}

//更新処理
eSceneType TitleScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_MAIN;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void TitleScene::Draw() const
{
	DrawString(0, 0, "TitleScene", GetColor(255, 255, 255));
}

//終了処理
void TitleScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType TitleScene::GetNowScene() const
{
	return eSceneType::E_TITLE;
}

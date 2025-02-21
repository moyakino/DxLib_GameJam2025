#include "RankingScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

/*ランキングは、ランキング画面の描画・アニメーションなど*/

RankingScene::RankingScene()
{
	rankingdata = nullptr;
}

RankingScene::~RankingScene()
{
}

//初期化処理
void RankingScene::Initialize()
{
	rankingdata = new RankingData;
}

//更新処理
eSceneType RankingScene::Update()
{
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		return eSceneType::E_RESULT;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void RankingScene::Draw() const
{
	DrawString(0, 0, "RankingScene", GetColor(255, 255, 255));
}

//終了処理
void RankingScene::Finalize()
{
	delete rankingdata;
}

//現在のシーン情報を取得
eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}

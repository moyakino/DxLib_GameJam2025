#include "RankingScene.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

/*ランキングは、ランキング画面の描画・アニメーションなど*/

RankingScene::RankingScene()
{
	//rankingdata = nullptr;

	ranking.ReadRanking();
	for (int i = 0; i < 5; i++) {

		rankingData[i] = ranking.GetRankingData(i);
	}
}

RankingScene::~RankingScene()
{
}

//初期化処理
void RankingScene::Initialize()
{
	//rankingdata = new RankingData;

	//image = LoadGraph("Resources/images/Ranking_bg.png");
	//DesideSE = LoadSoundMem("Resources/sounds/kettei.mp3");
}

//更新処理
eSceneType RankingScene::Update()
{
	/* 遷移先がTitleSceneしかない */
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0))
	{
		//PlaySoundMem(DesideSE, DX_PLAYTYPE_BACK);
		return eSceneType::E_TITLE;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void RankingScene::Draw() const
{
	/* 背景画像 */
	//DrawGraph(0, 0, image, TRUE);

	SetFontSize(100);
	DrawString(450, 100, "RANKING", 0xff0000);

	SetFontSize(60);

	/* ランキングの表示 */
	for (int i = 0; i < 5; i++) {

		DrawFormatString(350, 300 + 50 * i, 0xffffff, "%d %4s ", rankingData[i].no, rankingData[i].name.c_str());
		DrawFormatString(650, 300 + 50 * i, 0xffffff, "%5ld", rankingData[i].score);
	}

	/* Aボタン */
	SetFontSize(40);
	DrawString(550, 610, "A  PUSH", 0xff0000);
}

//終了処理
void RankingScene::Finalize()
{
	//delete rankingdata;
}

//現在のシーン情報を取得
eSceneType RankingScene::GetNowScene() const
{
	return eSceneType::E_RANKING;
}

#include "EndScene.h"
#include"DxLib.h"

EndScene::EndScene() :location(0, 0), fps(0), seconds(0)
{
}

EndScene::~EndScene()
{
}

//初期化処理
void EndScene::Initialize()
{


}

//更新処理
eSceneType EndScene::Update()
{
	/* フレームレート */
	fps++;


	/* 再設定 */
	if (fps > 10000)
	{
		if (seconds > 100)
		{
			seconds = 0;
		}

		seconds++;

		/* この中に入ったら1秒たちました */
		fps = 0;
	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

//描画処理
void EndScene::Draw() const
{
	SetFontSize(100);

	DrawString(500, 680 - fps, "提供", GetColor(255, 255, 255));

	SetFontSize(80);
	DrawString(400, 880 - fps, "チーム社不", GetColor(255, 255, 255));

	SetFontSize(50);

	DrawString(475, 1080 - fps, "新里　滉規", GetColor(255, 255, 255));

	DrawString(475, 1180 - fps, "宮城　汐凪", GetColor(255, 255, 255));

	DrawString(475, 1280 - fps, "松田　颯馬", GetColor(255, 255, 255));

	DrawString(475, 1380 - fps, "仲松　汰晟", GetColor(255, 255, 255));

	SetFontSize(80);

	DrawString(400, 1580 - fps, "使用ツール", GetColor(255, 255, 255));

	DrawString(300, 1780 - fps, "visual Studio 2022", GetColor(255, 255, 255));

	DrawString(400, 1980 - fps, "使用webツール", GetColor(255, 255, 255));

	DrawString(450, 2180 - fps, "chatGPT", GetColor(255, 255, 255));

	DrawString(375, 2380 - fps, "Pixsel Garo", GetColor(255, 255, 255));
	
	DrawString(200, 2580 - fps, "Art Studio まほろば", GetColor(255, 255, 255));
	
	SetFontSize(50);

	DrawString(200, 2780 - fps, "レトロゲーム風ロゴジェネレーター", GetColor(255, 255, 255));

	SetFontSize(80);

	DrawString(400, 2980 - fps, "素材提供", GetColor(255, 255, 255));
	
	DrawString(400, 3180 - fps, "KENNEY", GetColor(255, 255, 255));

	DrawString(375, 3380 - fps, "Pixsel Garo", GetColor(255, 255, 255));

	DrawString(375, 3580 - fps, "効果音ラボ", GetColor(255, 255, 255));

	

	
}

//終了処理
void EndScene::Finalize()
{
}

//現在のシーン情報を取得
eSceneType EndScene::GetNowScene() const
{
	return eSceneType::E_END;
}

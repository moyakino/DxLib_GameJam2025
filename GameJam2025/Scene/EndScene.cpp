#include "EndScene.h"
#include"DxLib.h"

EndScene::EndScene() :location(0, 0), fps(0), seconds(0), end_thank(NULL), end_you(NULL),end_for(NULL),end_play(NULL),image_end(NULL),end_bgm(NULL),
StartTime(NULL),sound_BUNG(NULL),timer_34(NULL)
{
}

EndScene::~EndScene()
{
}

//初期化処理
void EndScene::Initialize()
{
	//音読み込み
	sound_BUNG = LoadSoundMem("Resource/sound/Gunfire.wav");
	end_bgm = LoadSoundMem("Resource/sound/end_bgm_.wav");
	//
	PlaySoundMem(end_bgm, DX_PLAYTYPE_BACK, TRUE);

	//画像読み込み
	end_thank = LoadGraph("Resource/images/end_thank.png");
	end_you = LoadGraph("Resource/images/end_you.png");
	end_for = LoadGraph("Resource/images/end_for.png");
	end_play = LoadGraph("Resource/images/end_play.png");
	image_end = LoadGraph("Resource/images/image_end.png");
	//現在時間取得
	StartTime = GetNowCount();
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
	//背景描画
	DrawRotaGraph(640, 360, 1.0, 0.0, image_end, FALSE);

	
	//34秒たったらBUNGの音を鳴らす
	if ((GetNowCount() - StartTime) > 33975 &&  GetNowCount() - StartTime < 34000)
	{
		PlaySoundMem(sound_BUNG,DX_PLAYTYPE_BACK,TRUE);
	}

	
	//34秒たったらthankyou for playingを描画
	if (GetNowCount() - StartTime > 34000)
	{

		DrawRotaGraph(350, 120, 0.74, 0.0, end_thank, TRUE);

		DrawRotaGraph(910, 120, 0.74, 0.0, end_you, TRUE);

		DrawRotaGraph(150, 350, 0.74, 0.0, end_for, TRUE);

		DrawRotaGraph(370, 570, 0.74, 0.0, end_play, TRUE);
	}
	
	//36秒経ったらゲームを終了
	if (GetNowCount() - StartTime > 36000)
	{
		DxLib_End();
	}
	
	//エンドクレジットテキスト
	SetFontSize(100);

	DrawString(500, 680 - fps, "提供", GetColor(255, 255, 255));

	SetFontSize(80);
	DrawString(400, 820 - fps, "チーム社不", GetColor(255, 255, 255));

	SetFontSize(50);

	DrawString(275, 980 - fps, "新里　滉規", GetColor(255, 255, 255));

	DrawString(675, 980 - fps, "宮城　汐凪", GetColor(255, 255, 255));

	DrawString(275, 1080 - fps, "松田　颯馬", GetColor(255, 255, 255));

	DrawString(675, 1080 - fps, "仲松　汰晟", GetColor(255, 255, 255));

	SetFontSize(80);

	DrawString(400, 1180 - fps, "使用ツール", GetColor(255, 255, 255));

	DrawString(300, 1280 - fps, "visual Studio 2022", GetColor(255, 255, 255));

	DrawString(400, 1380 - fps, "使用webツール", GetColor(255, 255, 255));

	DrawString(200, 1480 - fps, "chatGPT", GetColor(255, 255, 255));

	DrawString(650, 1480 - fps, "Pixsel Garo", GetColor(255, 255, 255));
	
	DrawString(200, 1580 - fps, "Art Studio まほろば", GetColor(255, 255, 255));
	
	SetFontSize(50);

	DrawString(200, 1680 - fps, "レトロゲーム風ロゴジェネレーター", GetColor(255, 255, 255));

	SetFontSize(80);

	DrawString(400, 1780 - fps, "素材提供", GetColor(255, 255, 255));
	
	DrawString(200, 1880 - fps, "KENNEY", GetColor(255, 255, 255));

	DrawString(500, 1880 - fps, "Pixsel Garo", GetColor(255, 255, 255));

	DrawString(200, 1980 - fps, "効果音ラボ", GetColor(255, 255, 255));
	


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

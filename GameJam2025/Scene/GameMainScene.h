#pragma once
#define D_PIVOT_CENTER
#include<vector>
#include "SceneBase.h"
#include "../Utility/Vector2D.h"
#include "../Object/Player.h"

#define PLAYER1 0
#define PLAYER2 1

#define ROUND1XPLAYER1 50
#define ROUND1XPLAYER2 970

class GameMainScene : public SceneBase
{
private:

	/* Playerオブジェクト */
	Player* player;

	/* XBoxButtonの画像 */
	int CommandButtonImage[8];
	int EmptiyImage;

	/* Player1 用 */
	int RandNum[8];
	int PlayerWinLossCount;

	/* Player2 用 */
	int RandNum2[8];
	int Player2WinLossCount;

	/* 勝敗用 */
	int WinLossImage[5];
	bool WinLossDisplayFlag;
	int WinLossDisplayCount;

	/* Ready用 */
	int ReadyImage;
	bool Readyflg;
	int ReadyImageDisplayTime;

	bool RandomNumberGenerated;
	bool RandomNumberGenerated2;
	bool CommandInputFlg;

	/* コマンドの数を描画 */
	int RoundCount;
	bool CommandRenderFlag;

	/* ゲームのラウンド回数 */
	int GameRound;

	/* fps */
	int fps;

	/* カウンタ */
	int Seconds;
	int WaitTime;

	/* テスト用 */
	int TestNum;
	int TestImage;

	//背景
	int background_image;

	/* 待ち時間開始 */
	bool WaitTimeStart;

	/* リザルト画面遷移カウント */
	int ResultScreenTransitionCount;

	/* フィニッシュ画像 */
	int FinishImage;
	bool FinishRenderFlag;

	/* GameMainBGM */
	int GameMain_bgm;

public:

	GameMainScene();
	virtual ~GameMainScene();

	virtual void Initialize() override;
	virtual eSceneType Update() override;
	virtual void Draw() const override;
	virtual void Finalize() override;

	virtual eSceneType GetNowScene() const override;

	void GetRandomCommand(int player_num);

	/* 撃つ時のタイミング */
	bool GetWinLossDisplayFlag();

	int RandomWaitTime();

	void InitializeVariables();
};


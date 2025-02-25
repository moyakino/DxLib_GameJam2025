#include "InputNameScene.h"
#include"../Utility/InputControl.h"

InputNameScene::InputNameScene()
{
	//score = round;
	cursorPoint = { 0, 0 };
	ranking.ReadRanking();
	for (int i = 0; i < 5; i++) {
		rankingData[i] = ranking.GetRankingData(i);
	}
}

InputNameScene::~InputNameScene()
{
}

void InputNameScene::Initialize()
{
	//SelectSE = LoadSoundMem("Resources/sounds/cursorsound.mp3");
	//DesideSE = LoadSoundMem("Resources/sounds/kettei.mp3");
	//BackSE = LoadSoundMem("Resources/sounds/cancel.mp3");
}

eSceneType InputNameScene::Update()
{
	/* キーボード入力 */
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP, 0)) {
		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.y < 0) {
			//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
			if (cursorPoint.x > 10) {
				cursorPoint.y = 3;
			}
			else {
				cursorPoint.y = 4;
			}
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN, 0)) {
		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.y > 3 && cursorPoint.x > 10 || cursorPoint.y > 4) {
			cursorPoint.y = 0;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT, 0)) {
		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (++cursorPoint.x > 10 && cursorPoint.y > 3 || cursorPoint.x > 12) {
			cursorPoint.x = 0;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT, 0)) {
		//PlaySoundMem(SelectSE, DX_PLAYTYPE_BACK);
		if (--cursorPoint.x < 0) {
			if (cursorPoint.y > 3) {
				cursorPoint.x = 10;
			}
			else {
				cursorPoint.x = 12;
			}
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_A, 0) && (name.size() < 5 || keyboard[cursorPoint.y][cursorPoint.x] == '<')) {
		//PlaySoundMem(BackSE, DX_PLAYTYPE_BACK);
		if (keyboard[cursorPoint.y][cursorPoint.x] == '<') {
			if (name.size() > 0) {
				name.erase(name.begin() + (name.size() - 1));
			}
		}
		else {
			name += keyboard[cursorPoint.y][cursorPoint.x];
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B, 0)) {

		//PlaySoundMem(DesideSE, DX_PLAYTYPE_BACK);
		ranking.WriteRanking(name, score);

		/* GameMainに遷移 */
		//return new DrawRanking(/*score*/);

	}

	//現在のシーンタイプを返す
	return GetNowScene();
}

void InputNameScene::Draw() const
{
	/* タイトル */
	//DrawGraph(0, 0, image, TRUE);
	SetFontSize(80);
	DrawString(120, 100, "INPUT RANKING", 0xffffff);

	/* Playerが入力した文字描画 */
	SetFontSize(48);
	DrawBox(420, 240, 860, 300, 0xffffff, TRUE);
	DrawFormatString(420, 250, 0xFF00FF, "%s", name.c_str());

	/* 選択カーソル(Box)の表示 */
	DrawBox(310 + 50 * cursorPoint.x, 350 + 50 * cursorPoint.y,
		350 + 50 * cursorPoint.x, 405 + 50 * cursorPoint.y, 0x808080, TRUE);

	/* 入力用キーボード */
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 14; j++) {
			DrawFormatString(j * 50 + 318, i * 50 + 355, 0xffffff, "%c", keyboard[i][j]);
		}
	}

	SetFontSize(32);
	DrawString(435, 640, "B BUTTON PUSH", 0xffffff);
}

void InputNameScene::Finalize()
{
}

eSceneType InputNameScene::GetNowScene() const
{
	return eSceneType::E_INPUTNAME;
}

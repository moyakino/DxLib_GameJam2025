#pragma once

#include"Vector2D.h"

//入力値管理機能
class InputControl
{
private:

	static bool now_button[16];       //現在フレーム入力値
	static bool old_button[16];       //過去フレーム入力値

	static int XInputButtonArrayPlayer[8];
	static int RandNum[8];
	static bool RandomNumberPassed;
	static int RandCount;
	static bool CommandInputCompleted;

	static bool now_button2[16];       //現在フレーム入力値
	static bool old_button2[16];       //過去フレーム入力値

	static int XInputButtonArrayPlayer2[8];
	static int RandNum2[8];
	static bool RandomNumberPassed2;
	static int RandCount2;
	static bool CommandInputCompleted2;

	static bool CommandInputStart;
	static int CurrentCommandInputCount;
	static int CurrentCommandInputCount2;

public:

	static void Update();             //更新処理


	//ボタン入力取得処理
	static bool GetButtonDown(int button, int cnum);   //押した瞬間

	//ボタン
	static int GetButtonNums(int player_num, int count);

	//
	static void SetCommandInputStart(bool trigger);

	static void SetButtonNumber(int player_num, int array[]);
	static void SetRandomNumber(bool flg);

	static int GetRandCount(int player_num);

	static void SetCurrentCommandInputCount(int player_num, int CommandNum);

	static int GetCommandInputCompleted();
	static void SetCommandInputCompleted(bool VictoryCheckInit);

private:

	//ボタン配列範囲チェック
	static bool CheckButtonRange(int button);
};
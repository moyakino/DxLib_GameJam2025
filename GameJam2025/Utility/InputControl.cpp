#include"InputControl.h"
#include"DxLib.h"

//静的メンバ変数定義
bool InputControl::now_button[16] = {};
bool InputControl::old_button[16] = {};

int InputControl::XInputButtonArrayPlayer[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int InputControl::RandNum[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
bool InputControl::RandomNumberPassed = false;
int InputControl::RandCount = 0;
bool InputControl::CommandInputCompleted = false;

//PAD２
//静的メンバ変数定義
bool InputControl::now_button2[16] = {};
bool InputControl::old_button2[16] = {};

int InputControl::XInputButtonArrayPlayer2[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int InputControl::RandNum2[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
bool InputControl::RandomNumberPassed2 = false;
int InputControl::RandCount2 = 0;
bool InputControl::CommandInputCompleted2 = false;

bool InputControl::CommandInputStart = false;
int InputControl::CurrentCommandInputCount = 5;
int InputControl::CurrentCommandInputCount2 = 5;

//入力機能：更新処理
void InputControl::Update()
{
	//XInputコントローラーの入力値を取得する
	XINPUT_STATE input_state = {};
	XINPUT_STATE input_state2 = {};
	GetJoypadXInputState(DX_INPUT_PAD1, &input_state);
	GetJoypadXInputState(DX_INPUT_PAD2, &input_state2);

	/* パッド 1*/

	//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button[i] = now_button[i];
		now_button[i] = (bool)input_state.Buttons[i];
		/* ここにnow_buttonのi番目を配列に保存する*/

		/* コマンド入力受付開始 */
		if (CommandInputStart == true)
		{
			/* 今入力されているボタンの数がコマンドの数を超えないようにする */
			if (CurrentCommandInputCount != RandCount)
			{
				/* どこのボタンが押されているか？ */
				if (now_button[i] == true && old_button[i] == false)
				{
					if (i >= 0 && i < 4)
					{
						if (RandNum[RandCount] == i)
						{
							XInputButtonArrayPlayer[i] = i;
							++RandCount;
						}
					}
					else if (i > 11 && i < 16)
					{
						if (RandNum[RandCount] == (i - 8))
						{
							XInputButtonArrayPlayer[i - 8] = i;
							++RandCount;
						}
					}
				}
			}
			else
			{
				/* 入力が完了した */
				CommandInputCompleted = true;
				/* 初期化 */
				RandCount = 0;

				for (int j = 0; j < 8; j++)
				{
					XInputButtonArrayPlayer[j] = -1;
				}
			}
		}
		else
		{
			RandCount = 0;
			/* 受付開始前に入力が取られている */
			for (int j = 0; j < 8; j++)
			{
				XInputButtonArrayPlayer[j] = -1;
			}
		}
	}

	/*パッド２*/

		//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button2[i] = now_button2[i];
		now_button2[i] = (bool)input_state2.Buttons[i];
		/* ここにnow_buttonのi番目を配列に保存する*/

		if (CommandInputStart == true)
		{
			/* 今入力されているボタンの数がコマンドの数を超えないようにする */
			if (CurrentCommandInputCount2 != RandCount2)
			{
				/* どこのボタンが押されているか？ */
				if (now_button2[i] == true && old_button2[i] == false)
				{
					if (i >= 0 && i < 4)
					{
						if (RandNum2[RandCount2] == i)
						{
							XInputButtonArrayPlayer2[i] = i;
							++RandCount2;
						}
					}
					else if (i > 11 && i < 16)
					{
						if (RandNum2[RandCount2] == (i - 8))
						{
							XInputButtonArrayPlayer2[i - 8] = i;
							++RandCount2;
						}
					}
				}
			}
			else
			{
				/* 入力が完了した */
				CommandInputCompleted2 = true;

				/* 初期化 */
				RandCount2 = 0;

				for (int j = 0; j < 8; j++)
				{
					XInputButtonArrayPlayer2[j] = -1;
				}
			}
		}
		else
		{
			RandCount2 = 0;
			for (int j = 0; j < 8; j++)
			{
				XInputButtonArrayPlayer2[j] = -1;
			}
		}
	}
}

//ボタン取得：押した瞬間
bool InputControl::GetButtonDown(int button, int cnum)
{
	switch (cnum)
	{
	case 0:
		return CheckButtonRange(button) && (now_button[button] && !old_button[button]);

		break;
	case 1:
		return CheckButtonRange(button) && (now_button2[button] && !old_button2[button]);

		break;
	default:
		break;
	}
}

int InputControl::GetButtonNums(int player_num, int count)
{
	switch (player_num)
	{
	case 0:
		return XInputButtonArrayPlayer[count];
		break;
	case 1:
		return XInputButtonArrayPlayer2[count];
		break;
	default:
		break;
	}
}

void InputControl::SetCommandInputStart(bool trigger)
{
	CommandInputStart = trigger;
}

void InputControl::SetButtonNumber(int player_num, int array[])
{
	switch (player_num)
	{
	case 0:
		/* Player 1 */
		if (RandomNumberPassed == false)
		{
			for (int i = 0; i < 8; i++)
			{
				RandNum[i] = array[i];
			}
		}
		RandomNumberPassed = true;
		break;

		/* Player 2 */
	case 1:
		if (RandomNumberPassed2 == false)
		{
			for (int i = 0; i < 8; i++)
			{
				RandNum2[i] = array[i];
			}
		}
		RandomNumberPassed2 = true;
		break;

	default:
		break;
	}

	
}

void InputControl::SetRandomNumber(bool flg)
{
	RandomNumberPassed = flg;
	RandomNumberPassed2 = flg;
}

int InputControl::GetRandCount(int player_num)
{
	switch (player_num)
	{
	case 0:
		return RandCount;
		break;
	case 1:
		return RandCount2;
		break;
	default:
		break;
	}
	
}

void InputControl::SetCurrentCommandInputCount(int player_num, int CommandNum)
{
	switch (player_num)
	{
	case 0:
		CurrentCommandInputCount = CommandNum;
		break;
	case 1:
		CurrentCommandInputCount2 = CommandNum;
		break;
	default:
		break;
	}
}

/* 勝敗判定 */
int InputControl::GetCommandInputCompleted()
{
	/* 引き分け */
	if ((CommandInputCompleted == true) && (CommandInputCompleted2 == true))
	{
		return 0;
	}
	/* Player1 勝利 Player2 敗北 */
	else if ((CommandInputCompleted == true) && (CommandInputCompleted2 == false))
	{
		return 1;
	}
	/* Player2 勝利 Player1 敗北 */
	else if ((CommandInputCompleted2 == true) && (CommandInputCompleted == false))
	{
		return 2;
	}
	/* 判定中 */
	else
	{
		return 3;
	}
}

/* 勝敗判定用変数の初期化 */
void InputControl::SetCommandInputCompleted(bool VictoryCheckInit)
{
	CommandInputCompleted = VictoryCheckInit;
	CommandInputCompleted2 = VictoryCheckInit;
}

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}

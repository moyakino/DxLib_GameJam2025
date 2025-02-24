#include"InputControl.h"
#include"DxLib.h"

//静的メンバ変数定義
bool InputControl::now_button[16] = {};
bool InputControl::old_button[16] = {};
float InputControl::trigger[2] = {};
Vector2D InputControl::stick[2] = {};

int InputControl::XInputButtonArrayPlayer[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int InputControl::RandNum[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
bool InputControl::RandomNumberPassed = false;
int InputControl::RandCount = 0;

//PAD２
//静的メンバ変数定義
bool InputControl::now_button2[16] = {};
bool InputControl::old_button2[16] = {};
float InputControl::trigger2[2] = {};
Vector2D InputControl::stick2[2] = {};

int InputControl::XInputButtonArrayPlayer2[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
int InputControl::RandNum2[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
bool InputControl::RandomNumberPassed2 = false;
int InputControl::RandCount2 = 0;

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
				/* 初期化 */
				RandCount = 0;
			}
		}	
	}

	//トリガー入力値の更新（0.0ｆ～1.0ｆに範囲を制限する）
	trigger[0] = (float)input_state.LeftTrigger / (float)UCHAR_MAX;
	trigger[1] = (float)input_state.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新（-1.0ｆ～1.0ｆに範囲を制限する）
	if (input_state.ThumbLX > 0.0f)
	{
		stick[0].x = (float)input_state.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick[0].x = -((float)input_state.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state.ThumbLY > 0.0f)
	{
		stick[0].y = (float)input_state.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick[0].y = -((float)input_state.ThumbLY / (float)SHRT_MIN);
	}

	//右スティック入力値の更新（-1.0～1.0fに範囲を制限する）
	if (input_state.ThumbRX > 0.0f)
	{
		stick[1].x = (float)input_state.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick[1].x = -((float)input_state.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state.ThumbRY > 0.0f)
	{
		stick[1].y = (float)input_state.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick[1].y = -((float)input_state.ThumbRY / (float)SHRT_MIN);
	}


	/*パッド２*/

		//ボタン入力値の更新
	for (int i = 0; i < 16; i++)
	{
		old_button2[i] = now_button2[i];
		now_button2[i] = (bool)input_state2.Buttons[i];
		/* ここにnow_buttonのi番目を配列に保存する*/

		/* 今入力されているボタンの数がコマンドの数を超えないようにする */
		if (CurrentCommandInputCount2 != RandCount2)
		{
			/* どこのボタンが押されているか？ */
			if (now_button[i] == true && old_button[i] == false)
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
			/* 初期化 */
			RandCount2 = 0;
		}
	}

	//トリガー入力値の更新（0.0ｆ～1.0ｆに範囲を制限する）
	trigger2[0] = (float)input_state2.LeftTrigger / (float)UCHAR_MAX;
	trigger2[1] = (float)input_state2.RightTrigger / (float)UCHAR_MAX;

	//左スティック入力値の更新（-1.0ｆ～1.0ｆに範囲を制限する）
	if (input_state2.ThumbLX > 0.0f)
	{
		stick2[0].x = (float)input_state2.ThumbLX / (float)SHRT_MAX;
	}
	else
	{
		stick2[0].x = -((float)input_state2.ThumbLX / (float)SHRT_MIN);
	}
	if (input_state2.ThumbLY > 0.0f)
	{
		stick2[0].y = (float)input_state2.ThumbLY / (float)SHRT_MAX;
	}
	else
	{
		stick2[0].y = -((float)input_state2.ThumbLY / (float)SHRT_MIN);
	}

	//右スティック入力値の更新（-1.0～1.0fに範囲を制限する）
	if (input_state2.ThumbRX > 0.0f)
	{
		stick2[1].x = (float)input_state2.ThumbRX / (float)SHRT_MAX;
	}
	else
	{
		stick2[1].x = -((float)input_state2.ThumbRX / (float)SHRT_MIN);
	}
	if (input_state2.ThumbRY > 0.0f)
	{
		stick2[1].y = (float)input_state2.ThumbRY / (float)SHRT_MAX;
	}
	else
	{
		stick2[1].y = -((float)input_state2.ThumbRY / (float)SHRT_MIN);
	}
}

//ボタン取得：押してる間
bool InputControl::GetButton(int button, int cnum)
{
	switch (cnum)
	{
	case 0:
		return CheckButtonRange(button) && (now_button[button] && old_button[button]);
		break;
	case 1:
		return CheckButtonRange(button) && (now_button2[button] && old_button2[button]);
		break;
	default:
		break;
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

//ボタン取得：離した瞬間
bool InputControl::GetButtonUp(int button, int cnum)
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

//左トリガー取得
float InputControl::GetLeftTrigger()
{
	return trigger[0];
}

//右トリガー取得
float InputControl::GetRightTrigger()
{
	return trigger[1];
}

//左スティック取得
Vector2D InputControl::GetLeftStick()
{
	return stick[0];
}

//右スティック取得
Vector2D InputControl::GetRightStick()
{
	return stick[1];
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
				RandNum[i] = array[i];
			}
		}
		RandomNumberPassed2 = true;
		break;

	default:
		break;
	}

	
}

int InputControl::GetRandCount()
{
	return RandCount;
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

//ボタン配列範囲チェック
bool InputControl::CheckButtonRange(int button)
{
	return (0 <= button && button < 16);
}

#include "InputControl.h"
#include "DxLib.h"

/* 静的メンバ変数定義 */
/* クラスのインスタンスのポインタ */
/* (クラスのオブジェクトのポインタ) */
InputControl* InputControl::instance = nullptr;

/* リソース管理クラスのインスタンス取得する処理 */
InputControl* InputControl::GetInstance()
{
	/* インスタンス(オブジェクト)が無ければ、生成する */
	if (instance == nullptr)
	{
		instance = new InputControl();
	}

	/* 自分自身のポインタを返却する */
	return instance;
}

/* リソース管理クラスのインスタンス(オブジェクト)を削除する処理*/
void InputControl::DeleteInstance()
{
	/* インスタンス(オブジェクト)が存在していれば、削除する */
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

/* 更新 */
void InputControl::Update()
{
	KeyUpdate();

	MouseUpdate();

	JoypadUpdate();
}

/* キー更新処理 */
void InputControl::KeyUpdate()
{
	/* 前回の入力値の更新 */
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	/* 現在の入力値の更新 */
	GetHitKeyStateAll(now_key);
}

/* マウス更新処理 */
void InputControl::MouseUpdate()
{
	/* 前回の入力値の更新 */
	memcpy(old_mouse, now_mouse, (sizeof(char) * D_MOUSE_MAX));

	/* 現在の入力値の更新 */
	for (int i = 0; i < D_MOUSE_MAX; i++)
	{
		/* ビット演算でもできる */
		//now_mouse[i] = (now_mouse[i] & (GetMouseInput() & ((bool)MOUSE_INPUT_LEFT << i)) != FALSE);
		if (GetMouseInput() == i)
		{
			now_mouse[i] = 1;
		}
		else
		{
			now_mouse[i] = 0;
		}
	}

	/* 	マウスカーソルの位置を引数参照で取得する */
	int x, y;
	GetMousePoint(&x, &y);
	cursor.x = (float)x;
	cursor.y = (float)y;
}

/* ジョイパッド更新処理 */
void InputControl::JoypadUpdate()
{
	/* XInput用 */
	XINPUT_STATE x_input{};

	/* XInputの入力キー取得 */
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &x_input);
	for (int i = 0; i < D_JOYPAD_BUTTON_MAX; i++)
	{
		old_pad[i] = now_pad[i];
		now_pad[i] = x_input.Buttons[i];

		/*if (x_input.Buttons[i] == TRUE)
		{
			now_pad[i] = TRUE;
		}
		else
		{
			now_pad[i] = FALSE;
		}*/
	}


	/* 左スティック */
	Lstick.x = StickNormalize(x_input.ThumbLX);
	Lstick.y = StickNormalize(x_input.ThumbLY);

	/* 右スティック */
	Rstick.x = StickNormalize(x_input.ThumbRX);
	Rstick.y = StickNormalize(x_input.ThumbRY);

	/* 左トリガー */
	Trigger[0] = TriggerNormalize(x_input.LeftTrigger);
	Trigger[1] = TriggerNormalize(x_input.RightTrigger);
}

/* キーが押されているか確認する処理 */
bool InputControl::GetKey(int key_code) const
{
	return CheckKeyCodeRange(key_code) &&
		((now_key[key_code] == TRUE) && (old_key[key_code] == TRUE));
}

/* キーが押された瞬間か確認する処理 */
bool InputControl::GetKeyDown(int key_code) const
{
	return CheckKeyCodeRange(key_code) &&
		((now_key[key_code] == TRUE) && (old_key[key_code] == FALSE));
}

/* キーが離された瞬間か確認する処理 */
bool InputControl::GetKeyUp(int key_code) const
{
	return CheckKeyCodeRange(key_code) &&
		((now_key[key_code] == FALSE) && (old_key[key_code] == TRUE));
}

/* キーコードの範囲内か確認する処理 */
bool InputControl::CheckKeyCodeRange(int key_code) const
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}

/* マウスが押されているか確認する処理 */
bool InputControl::GetMouse(int mouse_code) const
{
	return ((now_mouse[mouse_code] == TRUE) && (old_mouse[mouse_code] == TRUE));
}

/* マウスが押された瞬間か確認する処理 */
bool InputControl::GetMouseDown(int mouse_code) const
{
	return ((now_mouse[mouse_code] == TRUE) && (old_mouse[mouse_code] == FALSE));
}

/* マウスが離された瞬間か確認する処理 */
bool InputControl::GetMouseUp(int mouse_code) const
{
	return ((now_mouse[mouse_code] == FALSE) && (old_mouse[mouse_code] == TRUE));
}

/* マウスカーソルの縦横の位置を取得する処理 */
Vector2D InputControl::GetMouseCursor()
{
	return cursor;
}

/* ボタンが押された瞬間か確認する処理 */
bool InputControl::GetButton(int button_code) const
{
	return ((now_pad[button_code] == TRUE) && (old_pad[button_code] == FALSE));
}

/* ボタンが押されているか確認する処理 */
bool InputControl::GetPressed(int button_code) const
{
	return ((now_pad[button_code] == TRUE) && (old_pad[button_code] == TRUE));
}

/* ボタンが離された瞬間か確認する処理 */
bool InputControl::GetRelease(int button_code) const
{
	return ((now_pad[button_code] == FALSE) && (old_pad[button_code] == TRUE));
}

/* 左スティックの縦横の位置を取得する処理 */
Vector2D InputControl::GetLstick() const
{
	return Lstick;
}

/* 右スティックの縦横の位置を取得する処理 */
Vector2D InputControl::GetRstick() const
{
	return Rstick;
}

/* 右トリガーの値を取得する */
float InputControl::GetRTrigger() const
{
	return Trigger[1];
}

/* 左トリガーの値を取得する */
float InputControl::GetLTrigger() const
{
	return Trigger[0];
}

/* スティックの傾き具合を丸め込み */
float InputControl::StickNormalize(short value)
{
	if (value < 0)
	{
		return -(static_cast<float>(value) / static_cast<float>(SHRT_MIN));
	}
	else
	{
		return (static_cast<float>(value) / static_cast<float>(SHRT_MAX));
	}
}

/* トリガーの傾き具合を丸め込み */
float InputControl::TriggerNormalize(unsigned char value)
{
	return (static_cast<float>(value) / static_cast<float>(UCHAR_MAX));
}
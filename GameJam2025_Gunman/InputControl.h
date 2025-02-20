#pragma once

#include "Vector2D.h"

/* マクロ定義 */
#define D_KEYCODE_MAX (256)				/* キーコード最大数 */
#define D_MOUSE_MAX (8)					/* マウス最大数 */
#define D_JOYPAD_BUTTON_MAX (16)		/* ジョイパッドのボタンの最大数 */
#define D_JOYPAD_STICK_X (1)			/* ジョイパッドのスティックのX軸 */
#define D_JOYPAD_STICK_Y (2)			/* ジョイパッドのスティックのY軸 */

/* 入力制御クラス */
class InputControl
{
private:

	/* 自クラスのポインタ(アドレスの先にインスタンスを生成する) */
	static InputControl* instance;

	/* キーボード入力値 */
	char now_key[D_KEYCODE_MAX] = {};	/* 今回の入力値 */
	char old_key[D_KEYCODE_MAX] = {};	/* 前回の入力値 */

	/* マウス入力値 */
	char now_mouse[D_MOUSE_MAX] = {};	/* 今回の入力値 */
	char old_mouse[D_MOUSE_MAX] = {};	/* 前回の入力値 */
	Vector2D cursor;					/* マウスカーソルの縦横の入力値 */

	/* パッド入力値 */
	char now_pad[D_JOYPAD_BUTTON_MAX] = {};	/* 今回の入力値 */
	char old_pad[D_JOYPAD_BUTTON_MAX] = {};	/* 前回の入力値 */
	Vector2D Lstick;						/* Lスティックの縦横の入力値 */
	Vector2D Rstick;						/* Rスティックの縦横の入力値 */
	float Trigger[2] = {};					/* トリガー */

private:

	/* コンストラクタをprivateにすることで、*/
	/* 自クラスのメンバ関数でしかインスタンスを生成できないようにする */
	InputControl() = default;

	/* コピーガード */
	/* クラス外でインスタンスを生成して渡すことができないようにする */
	InputControl(InputControl& v) = default;
	InputControl& operator = (const InputControl& v) = default;


public:

	/* ～コピーガード */
	~InputControl() = default;

public:

	/* インスタンスを取得する処理 */
	static InputControl* GetInstance();

	/* インスタンスを削除する処理 */
	static void DeleteInstance();

public:

	/* 更新処理 */
	void Update();

	/* キー入力更新処理 */
	void KeyUpdate();

	/* マウス入力更新処理 */
	void MouseUpdate();

	/* ジョイパッド入力更新処理 */
	void JoypadUpdate();

	/* キー入力状態を取得する */
	bool GetKey(int key_code) const;	/* 押している間 */
	bool GetKeyDown(int key_code) const;/* 押した瞬間 */
	bool GetKeyUp(int key_code) const;	/* 離した瞬間 */

	/* マウス入力状態を取得する */
	bool GetMouse(int mouse_code) const;	/* 押している間 */
	bool GetMouseDown(int mouse_code) const;/* 押した瞬間 */
	bool GetMouseUp(int mouse_code) const;	/* 離した瞬間 */

	/* マウス縦横軸の位置を取得する */
	Vector2D GetMouseCursor();

	/* ジョイパッド入力状態を取得する */
	bool GetButton(int button_code) const;	/* 押した瞬間 */
	bool GetPressed(int button_code) const;	/* 押している間 */
	bool GetRelease(int button_code) const;	/* 離した瞬間 */
	Vector2D GetRstick() const;				/* 右スティックの縦軸値を取得する */
	Vector2D GetLstick() const;				/* 左スティックの縦軸値を取得する */
	float GetRTrigger() const;		/* 右トリガーの値を取得する */
	float GetLTrigger() const;		/* 左トリガーの値を取得する */

private:

	/* キー入力の範囲を確認する */
	bool CheckKeyCodeRange(int key_code) const;

	/* スティックの傾き具合を丸め込み */
	float StickNormalize(short value);

	/* トリガーの傾き具合を丸め込み */
	float TriggerNormalize(unsigned char value);
};
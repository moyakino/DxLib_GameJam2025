#include "GameObject.h"
#include "ResourceManager.h"
#include "InputControl.h"
#include "DxLib.h"

/* コンストラクタ */
GameObject::GameObject() :
	location(0.0f),
	box_size(0.0f),
	image(NULL),
	flip_flag(FALSE)
{

}

/* デストラクタ */
GameObject::~GameObject()
{

}

/* 初期化処理 */
void GameObject::Initialize()
{
	image = NULL;

	box_size = Vector2D(32.0f);

	location = box_size;
}

/* 更新処理 */
void GameObject::Update()
{

}

/* 描画処理 */
void GameObject::Draw() const
{
	/* 入力情報の取得 */
	InputControl* input = InputControl::GetInstance();

	/* メンバの情報を基に画像を描画する */
	DrawRotaGraphF(location.x, location.y, 1.0, 0.0, image, TRUE, flip_flag);

	DrawFormatString(0, 0, GetColor(255, 0, 0), "%0.1f\n", input->GetMouseCursor().x);
	DrawFormatString(0, 26, GetColor(255, 0, 0), "%0.1f\n", input->GetLstick().x);
	DrawFormatString(0, 46, GetColor(255, 0, 0), "%d\n", input->GetMouse(MOUSE_INPUT_LEFT));
	DrawFormatString(0, 66, GetColor(255, 0, 0), "%0.1f\n", input->GetLTrigger());
	DrawFormatString(0, 86, GetColor(255, 0, 0), "%d\n", input->GetButton(XINPUT_BUTTON_A));

	/* 当たり判定の矩形情報を描画する */
	Vector2D upper_left = location - (box_size / 2.0f);
	Vector2D lower_right = location + (box_size / 2.0f);
	DrawBoxAA(upper_left.x, upper_left.y, lower_right.x, lower_right.y, GetColor(255, 0, 0), FALSE);
}

/* 終了時処理 */
void GameObject::Finalize()
{

}

/* 位置情報の取得する */
Vector2D GameObject::GetLocation() const
{
	return this->location;
}

/* 矩形の大きさを取得する  */
Vector2D GameObject::GetBoxSize() const
{
	return this->box_size;
}

/* 位置情報の設定 */
void GameObject::SetLocation(const Vector2D& location)
{
	this->location = location;
}
#pragma once

#include "Vector2D.h"

/* ゲームオブジェクトクラス(画面に出てくるオブジェクトの親クラス) */
class GameObject
{
protected:

	/* 位置座標情報 */
	Vector2D location;

	/* 矩形の大きさ */
	Vector2D box_size;

	/* 描画する画像データ */
	int image;

	/* 描画反転フラグ */
	int flip_flag;

public:

	/* Constructor */
	GameObject();

	/* Destructor */
	virtual ~GameObject();

	/* 初期化処理 */
	virtual void Initialize();

	/* 更新処理 */
	virtual void Update();

	/* 描画処理 */
	virtual void Draw() const;

	/* 終了時処理 */
	virtual void Finalize();

public:

	/**/
	Vector2D GetLocation() const;

	/**/
	Vector2D GetBoxSize() const;

	/**/
	void SetLocation(const Vector2D& location);
};
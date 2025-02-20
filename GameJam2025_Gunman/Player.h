#pragma once

#include "GameObject.h"
#include <vector>

class Player : public GameObject
{
private:

	/* 加速度 */
	Vector2D velocity;

	/* アニメーションデータ */
	std::vector<int> animation_data;

	/* アニメーションの時間 */
	int animation_count;

public:

	/* */
	Player();

	/* */
	virtual ~Player();

	/* 初期化処理 */
	virtual void Initialize() override;

	/* 更新処理 */
	virtual void Update() override;

	/* 描画処理 */
	virtual void Draw() const override;

	/* 終了時処理 */
	virtual void Finalize() override;

private:

	/* 移動処理 */
	void Movement();

	/* アニメーションの制御 */
	void AnimationControl();

};
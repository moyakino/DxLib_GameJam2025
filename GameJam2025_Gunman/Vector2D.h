#pragma once


class Vector2D
{
public:

	/* 座標 location */
	float x;
	float y;

public:

	/* Constructor 引数無し */
	Vector2D();

	/* Constructor 引数 1 */
	/* scalarとは1つの数値で示される定数や変数のこと */
	Vector2D(float scalar);

	/* Constructor 引数 2 */
	Vector2D(float mx, float my);

	/* Destructor */
	~Vector2D();

public:

	/* = 代入 */
	Vector2D& operator = (const Vector2D& location);

	/* Add 足し算 */
	const Vector2D operator + (const Vector2D& location) const;
	/* Add 足して代入 */
	Vector2D& operator += (const Vector2D& location);

	/* Sub 減算 */
	const Vector2D operator - (const Vector2D& location) const;
	/* Sub 引いて代入 */
	Vector2D& operator -= (const Vector2D& location);

	/* Multi 掛け算 */
	const Vector2D operator * (const float& scalar) const;
	/* Multi 掛け算 */
	const Vector2D operator * (const Vector2D& location) const;
	/* Multi 掛けて代入 */
	Vector2D& operator *= (const float& scalar);
	/* Multi 掛けて代入 */
	Vector2D& operator *= (const Vector2D& location);

	/* Div 割り算 */
	const Vector2D operator / (const float& scalar) const;
	/* Div 割り算 */
	const Vector2D operator / (const Vector2D& location) const;
	/* Div 割って代入 */
	Vector2D& operator /= (const float& scalar);
	/* Div 割って代入 */
	Vector2D& operator /= (const Vector2D& location);

	/* 引数の値をint型にCastする */
	void ToInt(int* x, int* y) const;
};
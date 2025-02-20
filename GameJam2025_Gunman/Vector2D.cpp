#include "Vector2D.h"
#include "UserTemplate.h"

/* Constructor 引数無し */
Vector2D::Vector2D() : x(0.0f), y(0.0f)
{

}

/* Constructor 引数 1 */
Vector2D::Vector2D(float scalar) : x(scalar), y(scalar)
{

}

/* Constructor 引数 2 */
Vector2D::Vector2D(float mx, float my) : x(mx), y(my)
{

}

/* Destructor */
Vector2D::~Vector2D()
{

}

/* = 代入 */
Vector2D& Vector2D::operator=(const Vector2D& location)
{
	this->x = location.x;
	this->y = location.y;

	return *this;
}

/* Add 足し算 */
const Vector2D Vector2D::operator+(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x + location.x;
	result.y = this->y + location.y;

	return result;
}

/* Add 足して代入 */
Vector2D& Vector2D::operator+=(const Vector2D& location)
{
	this->x += location.x;
	this->y += location.y;

	return *this;
}

/* Sub 減算 */
const Vector2D Vector2D::operator-(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x - location.x;
	result.y = this->y - location.y;

	return result;
}

/* Sub 引いて代入 */
Vector2D& Vector2D::operator-=(const Vector2D& location)
{
	this->x -= location.x;
	this->y -= location.y;

	return *this;
}

/* Multi 掛け算 */
const Vector2D Vector2D::operator*(const float& scalar) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * scalar;
	result.y = this->y * scalar;

	return result;
}

/* Multi 掛け算 */
const Vector2D Vector2D::operator*(const Vector2D& location) const
{
	Vector2D result = Vector2D(0.0f);

	result.x = this->x * location.x;
	result.y = this->y * location.y;

	return result;
}

/* Multi 掛けて代入 */
Vector2D& Vector2D::operator*=(const float& scalar)
{
	this->x *= scalar;
	this->y *= scalar;

	return *this;
}

/* Multi 掛けて代入 */
Vector2D& Vector2D::operator*=(const Vector2D& location)
{
	this->x *= location.x;
	this->y *= location.y;

	return *this;
}

/* Div 割り算 */
const Vector2D Vector2D::operator/(const float& scalar) const
{
	if (Abs(scalar) < 1e-6f)
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / scalar, this->y / scalar);
}

/* Div 割り算 */
const Vector2D Vector2D::operator/(const Vector2D& location) const
{
	if ((Abs(location.x) < 1e-6f) || (Abs(location.y) < 1e-6f))
	{
		return Vector2D(0.0f);
	}

	return Vector2D(this->x / location.x, this->y / location.y);
}

/* Div 割って代入 */
Vector2D& Vector2D::operator/=(const float& scalar)
{
	if (Abs(scalar) < 1e-6f)
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x = scalar;
		this->y = scalar;
	}

	return *this;
}

/* Div 割って代入 */
Vector2D& Vector2D::operator/=(const Vector2D& location)
{
	if ((Abs<float>(location.x) < 1e-6f) || (Abs<float>(location.y) < 1e-6f))
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}
	else
	{
		this->x /= location.x;
		this->y /= location.y;
	}

	return *this;
}

/* 引数の値をint型にCastする */
void Vector2D::ToInt(int* x, int* y) const
{
	*x = static_cast<int>(this->x);
	*y = static_cast<int>(this->y);
}
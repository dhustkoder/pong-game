#ifndef BALL_H
#define BALL_H
#include "shape.h"

constexpr float ballVelocity = 4.0F;
constexpr float ballRadius = 7.0F;

class Ball : public Shape
{
public:
	// give window size.
	Ball(const float winWidth, const float winHeight);
	void treatCollisionWith(const Shape &collidedShape);
	virtual void update();
private:
	const float m_maxBottom, m_maxRight;

	Ball(const Ball&) = delete;
	Ball(Ball&&) = delete;
};












#endif
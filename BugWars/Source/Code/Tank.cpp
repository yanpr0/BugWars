#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"

void Tank::OnUpdate(float dt)
{
}

Point Tank::CalcShootDirection() const
{
	return Point{ 1, 0 };
}

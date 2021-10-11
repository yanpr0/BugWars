#include "pch.h"
#include "BulletBase.h"
#include "GameBase.h"
#include "TankBase.h"

const float BulletBase::s_Velocity = 200.0f;
const int BulletBase::s_FramesToLive = 300;

void BulletBase::Start(Point dir)
{
	direction = dir.Normalized();
	position = g_GameBase->tank->position;

	OnStart(dir);
}

void BulletBase::Update(float dt)
{
	framesToLive--;

	position = position + direction * s_Velocity * dt;

	OnUpdate(dt);

	if (framesToLive <= 0)
		OnLifeEnd();
}

Texture* BulletBase::GetTexture() const
{
	return g_GameBase->bulletTexture;
}

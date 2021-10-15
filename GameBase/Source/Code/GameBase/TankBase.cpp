#include "pch.h"
#include "TankBase.h"
#include "BulletBase.h"
#include "Globals.h"
#include "GameBase.h"

const int TankBase::s_ShootPeriodFrames = 120;
const float TankBase::s_Velocity = 180.0f;

void TankBase::Update(float dt)
{
	static int frame_counter = 0;
	frame_counter++;

	static int frame_last_shot = 0;
	if (frame_counter - frame_last_shot >= s_ShootPeriodFrames)
	{
		frame_last_shot = frame_counter;
		Shoot();
	}

	if (g_GameBase->tankRoute.empty())
		return;

	auto& destination = g_GameBase->tankRoute.back();

	auto dir = (destination.destination - position).Normalized();

	position = position + dir * dt * s_Velocity;
	angle = 90.0f + atan2(dir.y, dir.x) * 180.0f / std::numbers::pi_v<float>;

	if (destination.numFramesToGo-- <= 0)
		g_GameBase->tankRoute.pop_back();

	OnUpdate(dt);
}

void TankBase::Shoot()
{
	auto bullet = g_GameBase->creators.bullet_creator();
	g_GameBase->AddObject(bullet);
	bullet->Start(CalcShootDirection());
	numShots++;
}

Texture* TankBase::GetTexture() const
{
	return g_GameBase->tankTexture;
}
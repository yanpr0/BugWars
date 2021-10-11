#include "pch.h"
#include "BugBase.h"
#include "Globals.h"
#include "GameBase.h"

const float BugBase::s_Velocity = 100.0f;

void BugBase::Update(float dt)
{
	OnUpdate(dt);

	BugBase* target = FindBugToEat();
	if (!target)
		return;

	auto vec = target->position - position;
	float len2 = vec.Length2();
	float r = GetRadius();
	float _2r2 = r * r * 2 * 2;
	if (len2 < _2r2)
		OnEat(*this, *target);

	auto dir = vec.Normalized();
	position = position + dir * s_Velocity * dt;
	if (dir.x != 0.0f)
		angle = 90.0f + atan2(dir.y, dir.x) * 180.0f / std::numbers::pi_v<float>;
}

Texture* BugBase::GetTexture() const
{
	return g_GameBase->bugTexture;
}

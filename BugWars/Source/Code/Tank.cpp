#include "pch.h"
#include "Tank.h"
#include "Globals.h"
#include "Game.h"
#include "Bullet.h"
#include "Bug.h"

#include <numeric>
#include <optional>
#include <utility>

IMPLEMENT_RTTI(Tank);

void Tank::OnUpdate(float dt)
{
}

BugBase* Tank::GetBugToShoot() const
{
    Bug* bug = nullptr;
    float min_d = std::numeric_limits<float>::max();

	for (auto obj : g_Game->objects)
		if (obj->GetRTTI() == Bug::s_RTTI)
        {
            if (auto d = position.Distance(obj->position); d < min_d)
            {
                bug = static_cast<Bug*>(obj);
			    min_d = d;
            }
        }

	return bug;
}

Point Tank::CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const
{
    auto d = target_pos.Distance(position);

    if (d < 1e-4)
    {
        return {1, 0};
    }

    auto default_dir = (target_pos - position).Normalized();

	auto dx = target_pos.x - position.x;
    auto dy = target_pos.y - position.y;
    auto vx = target_vel * target_dir.x;
    auto vy = target_vel * target_dir.y;

    auto D_ = dx * dx * (bullet_vel * d - (dy * vx - dx * vy)) * (bullet_vel * d + (dy * vx - dx * vy));

    if (D_ < 0)
    {
        return default_dir;
    }

    auto sqrt_D_ = sqrt(D_);

    auto get_dir_time = [d, dx, dy, vx, vy, bullet_vel](float sqrt_D_) -> std::optional<std::pair<Point, float>> {
        auto vel_x = (dy * dy * vx - dx * dy * vy + sqrt_D_) / (d * d);

        auto t = dx / (vel_x - vx);

        if (t < 0)
        {
            return {};
        }

        auto vel_y_2 = bullet_vel * bullet_vel - vel_x * vel_x;

        if (vel_y_2 < 0)
        {
            return {};
        }

        return {Point{vel_x, sqrt(vel_y_2)}.Normalized(), t};
    };

    auto ans1 = get_dir_time(sqrt_D_);
    auto ans2 = get_dir_time(-sqrt_D_);

    if (!ans1)
    {
        return ans2 ? ans2->first : default_dir;
    }
    if (!ans2)
    {
        return ans1 ? ans1->first : default_dir;
    }

    auto [dir1, t1] = *ans1;
    auto [dir2, t2] = *ans2;

    return t1 < t2 ? dir1 : dir2;
}


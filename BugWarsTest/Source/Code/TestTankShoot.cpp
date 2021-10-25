#include "pch.h"
#include "Tank.h"

bool WillHitTarget(Point tank_pos, Point target_pos, Point target_dir,
	float target_vel, float bullet_vel)
{
	target_dir = target_dir.Normalized();
	Tank tank;

	tank.position = tank_pos;
	auto shoot_dir = tank.CalcShootDirection(target_pos, target_dir, target_vel, bullet_vel).Normalized();

	const uint max_step_count = 10000;
	const float dt = 0.1f;

	auto bullet_pos = tank_pos;

	for (uint i = 0; i < max_step_count; i++)
	{
		target_pos = target_pos + target_dir * target_vel * dt;
		bullet_pos = bullet_pos + shoot_dir * bullet_vel * dt;

		const float eps = 1.0f;
		if (target_pos.Distance2(bullet_pos) < eps)
		{
			return true;
		}
	}

	return false;
}

TEST(TankShoot_1)
{
	//      |
	// t    b
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 10, 0 }, { 0, -1 }, 1.0f, 2.0f));
}

TEST(TankShoot_2)
{
	// t    b
	//      |
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 10, 0 }, { 0, 1 }, 1.0f, 1.347f));
}

TEST(TankShoot_3)
{
	// t    b
	//      |
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 10, 0 }, { 0, 1 }, 0.5f, 1.5f));
}

TEST(TankShoot_4)
{
	//     
	// t   \
	//      b   
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 5, 5 }, { -1, -1 }, 1.0f, 3.0f));
}

TEST(TankShoot_5)
{
	//     \
	//      b
	// t    
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 5, -5 }, { -1, -1 }, 1.0f, 2.0f));
}

TEST(TankShoot_6)
{
	//      b
	// t   / 
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 5, -5 }, { -1, 1 }, 1.0f, 2.0f));
}

TEST(TankShoot_7)
{
	//      t  
	//   b
	//    \
	//
	CHECK_EQUAL(true, WillHitTarget({ 5, -5 }, { 0, 0 }, { 1, 1 }, 1.5f, 1.8f));
}

TEST(TankShoot_9)
{
	//   b-   t  
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { -10, 0 }, { 1, 0 }, 0.001f, 1.0f));
}

TEST(TankShoot_10)
{
	//        t  
	//        |  
	//        b  
	CHECK_EQUAL(true, WillHitTarget({ 0, 0 }, { 0, 10 }, { 0, -1 }, 10.0f, 0.0001f));
}

TEST(TankShoot_11)
{
	//        t  
	//          
	//        b 
	//        |
	CHECK_EQUAL(true, WillHitTarget({ 0, -10 }, { 0, 10 }, { 0, 1 }, 1.0f, 1.1f));
}
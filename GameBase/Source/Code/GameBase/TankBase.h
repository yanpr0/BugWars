#pragma once
#include "GameObject.h"

struct BugBase;

struct TankBase : public GameObject
{
	virtual void Update(float dt) override final;
	virtual Texture* GetTexture() const override final;

	virtual void OnUpdate(float dt) = 0;
	// Get a bug to shoot 
	virtual BugBase* GetBugToShoot() const = 0;
	// Calculate shooting direction from the tank's center
	virtual Point CalcShootDirection(Point target_pos, Point target_dir, float target_vel, float bullet_vel) const = 0;

	void Shoot();

	static const int s_ShootPeriodFrames;
	static const float s_Velocity;


	int score = 0;
	int numShots = 0;
};
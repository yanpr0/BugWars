#pragma once
#include "GameObject.h"

struct TankBase : public GameObject
{
	virtual void Update(float dt) override final;
	virtual Texture* GetTexture() const override final;

	virtual void OnUpdate(float dt) = 0;
	// Calculate shooting direction from the tank's center
	virtual Point CalcShootDirection() const = 0;

	void Shoot();

	static const int s_ShootPeriodFrames;
	static const float s_Velocity;


	int score = 0;
	int numShots = 0;
};
#pragma once
#include "GameBase/TankBase.h"

struct Tank : public TankBase
{
	virtual void OnUpdate(float dt) override;
	// Calculate shooting direction from the tank's center
	virtual Point CalcShootDirection() const override;
};
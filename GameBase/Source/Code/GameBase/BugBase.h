#pragma once
#include "GameObject.h"

struct BugBase : public GameObject
{
	virtual void Update(float dt) override final;
	virtual Texture* GetTexture() const override final;

	virtual void OnUpdate(float dt) = 0;
	// Search another bug which is older
	// The bug will go towards it and try to eat it
	virtual BugBase* FindBugToEat() const = 0;
	// Happens when two bugs try to eat each other
	virtual void OnEat(BugBase& first, BugBase& second) = 0;
	
	static const float s_Velocity;

	Point direction;
};

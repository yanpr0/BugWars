#pragma once
#include "GameObject.h"

struct BulletBase : public GameObject
{
	void Start(Point direction);

	virtual void Update(float dt) override final;
	virtual Texture* GetTexture() const override final;

	virtual void OnStart(Point direction) = 0;
	virtual void OnUpdate(float dt) = 0;
	virtual void OnLifeEnd() = 0;

	static const float s_Velocity;
	static const int s_FramesToLive;

	Point direction;
	int framesToLive = s_FramesToLive;
};
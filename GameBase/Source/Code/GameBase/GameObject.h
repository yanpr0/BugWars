#pragma once
#include "RTTIObject.h"
#include "Point.h"

struct Texture;

struct GameObject : public RTTIObject
{
	GameObject();
	virtual ~GameObject() = default;

	virtual void Update(float dt) = 0;
	virtual Texture* GetTexture() const = 0;

	Point GetSize() const;
	float GetRadius() const;

	Point position; // Anchor is in the middle of the image
	float angle; // Angle in degrees
	uint id;
	bool visible;
	bool disabled;
};
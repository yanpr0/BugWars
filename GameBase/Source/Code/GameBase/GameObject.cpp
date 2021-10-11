#include "pch.h"
#include "GameObject.h"
#include "Texture.h"

GameObject::GameObject()
	: visible(true)
{
	static int id_counter = 0;
	id = id_counter++;
}

Point GameObject::GetSize() const
{
	return GetTexture()->size;
}

float GameObject::GetRadius() const
{
	return GetSize().x / 2;
}
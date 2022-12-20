#include "pch.h"
#include "Game.h"
#include "GameBase/Framework.h"
#include "GameBase/Log.h"
#include "Tank.h"
#include "Bug.h"
#include "Bullet.h"

Game* g_Game;

Game::Game()
	: GameBase({ [] {return new Tank; },
				 [] {return new Bug; },
				 [] {return new Bullet; } })
{
	g_Game = this;
}

Game::~Game()
{
	for (auto obj : objects)
	{
		delete obj;
	}
}

void Game::OnUpdate(float dt)
{
	int size = 0;
	for (auto obj : objects)
	{
		if (obj->disabled)
		{
			delete obj;
		}
		else
		{
			objects[size++] = obj;
		}
	}
	objects.resize(size);

	auto is_in_sight = [this](GameObject* obj) {
		auto [x, y] = obj->position;
		auto [w, h] = framework->screenSize;
		auto [x0, y0] = tank->position;
		auto r = obj->GetRadius();
		return abs(x - x0) < w / 2 + r && abs(y - y0) < h / 2 + r;
	};

	//PIXScopedEvent(PIX_COLOR_INDEX(5), __FUNCTION__);
	for (auto obj : objects)
	{
		if (framework && tank)
		{
			obj->visible = is_in_sight(obj);
		}
		obj->Update(dt);
	}
}

void Game::OnRender() const
{
	for (auto obj : objects)
		if (obj->visible)
			DoRender(obj);
}

void Game::AddObject(GameObject* object)
{
	objects.push_back(object);
	//if (object->GetRTTI() == Bug::s_RTTI)
	//	Log("I'm a bug");
}

void Game::OnBugsSpawned()
{
}


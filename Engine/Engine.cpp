// Engine.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Engine.h"

#include <iostream>

namespace nu
{
	bool Engine::Initialize()
	{
		m_renderer.Initialize("Game Engine", 1920, 1024);
		m_input.Initialize();

		return true;
	}

	void Engine::Shutdown()
	{

	}

	void Engine::Update()
	{
		m_input.Update();
		m_time.Tick();
	}

}
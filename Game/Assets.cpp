#include "Assets.h"

using namespace nu;

namespace assets
{
	Mesh playerMesh{ { Vector2{2,0}, Vector2{-2,2}, Vector2{-1, 0}, Vector2(-2,-2), Vector2 (2,0)}, Color{0.0f, 0.0f, 1.0f}};
	Model playerModel{ std::vector<Mesh>{playerMesh} };
}
#pragma once

#include "Object.h"

class Crate {
	Object object;
public:
	bool Collected(const Object& player);
	void DrawCrate(Graphics& gfx);
};
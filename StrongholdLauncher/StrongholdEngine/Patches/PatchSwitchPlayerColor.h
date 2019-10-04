#pragma once
#include "Patch.h"

class PatchSwitchPlayerColor
	: public Patch
{
	REGISTER(PatchSwitchPlayerColor);

public:
	void enable() override;
	void frame();

	void switchUnits(int playerFrom, int playerTo);
};

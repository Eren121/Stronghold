#pragma once
#include "Patch.h"

class PatchBanditUnitEditor
	: public Patch
{
	REGISTER(PatchBanditUnitEditor);

	bool enabled = false;

public:
	void enable() override;
};

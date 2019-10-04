#pragma once
#include "Patch.h"

class Keyboard
	: public Patch
{
	REGISTER(Keyboard);

private:
	static bool keyboardLastFrame[256];
	static bool keyboard[256];

	void frame();

public:
	Keyboard() = default;
	~Keyboard() override = default;
	void enable() override;

	inline static bool isKeyJustDown(DWORD virtualKey) {
		return keyboard[virtualKey];
	}
};
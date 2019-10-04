#include "pch.h"
#include "Keyboard.h"
#include "PatchScreenUpdate.h"

bool Keyboard::keyboardLastFrame[] = {};
bool Keyboard::keyboard[] = {};

void Keyboard::enable()
{
	PatchScreenUpdate::registerScreenUpdate([this]() {
		frame();
	});
}

void Keyboard::frame()
{
	// GetKeyboardState don't work, maybe because game update and peek the state
	//GetKeyboardState(reinterpret_cast<PBYTE>(keyboard));
	

	for (int i = 0; i < sizeof keyboard; i++) {
			
		keyboard[i] = static_cast<bool>(GetAsyncKeyState(i));
		bool down = keyboard[i];

		if (down && keyboardLastFrame[i])
			keyboard[i] = false;

		keyboardLastFrame[i] = down;
	}
}
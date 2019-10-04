#include "pch.h"
#include "Instrumentation/Address.h"
#include "PatchBanditUnitEditor.h"
#include "PatchScreenUpdate.h"
#include "Keyboard.h"

void PatchBanditUnitEditor::enable()
{
	static bool& enabled = this->enabled;

	addr::ASMADDR address = addr::ASMADDR::exe(0x369430, 5);
	address.BeforePatch([]() {
	
		if (enabled) {
			*reinterpret_cast<int32_t*>(addr::ESP + 8) = 0;
		}
	}, PATCH_DEFAULT | PATCH_CAPTUREREGISTERS);

	PatchScreenUpdate::registerScreenUpdate([]() {
		if (Keyboard::isKeyJustDown(VK_F2)) {
			enabled = !enabled;
		}
	});
}

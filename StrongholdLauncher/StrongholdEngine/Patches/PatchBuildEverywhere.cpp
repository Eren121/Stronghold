#include "pch.h"
#include "Patch.h"
#include "sh2/Buildings.h"
#include <cstdio>
#include <iostream>
#include <sstream>
#include <vector>
#include "Instrumentation/Address.h"
#include "Functional.h"
#include "PatchScreenUpdate.h"
#include "Keyboard.h"

class PatchBuildEverywhere
	: public Patch
{
	REGISTER(PatchBuildEverywhere);

	struct BuildingSize {
		int32_t* addressX;
		int32_t* addressY;
		int originalX;
		int originalY;

		void zero() {
			*addressX = 1;
			*addressY = 1;
		}

		void restore() {
			*addressX = originalX;
			*addressY = originalY;
		}
	};

	std::vector<BuildingSize> buildingSizes = {};
	bool enabled = false;

public:
	~PatchBuildEverywhere() override = default;

	void enable() override
	{
		addr::ASMADDR address = addr::ASMADDR::exe(0x71608, 6);
		static decltype(buildingSizes)* vecPointer = &buildingSizes;

		address.BeforePatch([]() {

			// ESI+34 contains pointer to X construction size
			// ESI+38 contains pointer to Y construction size
			// EDX contains X construction size value
			// EAX contains Y construction size value
			int32_t* pointer = reinterpret_cast<int32_t*>(reinterpret_cast<char*>(addr::ESI) + 0x34);
			int x = addr::EDX, y = addr::EAX;

			vecPointer->push_back({ pointer, pointer + 1, x, y });

			//info() << "Registering building " << reinterpret_cast<const char*>(addr::ESI + 4);

		}, PATCH_DEFAULT | PATCH_CAPTUREREGISTERS);

		PatchScreenUpdate::registerScreenUpdate([this]() {
			toggle();
		});
	}

	void toggle()
	{
		if (!Keyboard::isKeyJustDown(VK_F1)) {
			return;
		}

		enabled = !enabled;

		if (enabled) {
			call_each(buildingSizes, &BuildingSize::zero);
		}
		else {
			call_each(buildingSizes, &BuildingSize::restore);
		}
	}
};
#include "pch.h"
#include "PatchSwitchPlayerColor.h"
#include "Instrumentation/Address.h"
#include "PatchScreenUpdate.h"
#include "Keyboard.h"

/// All units are stored as this:
/// Unit *units = new Units[100];
/// 
/// Buffer of fixed size
/// Append one unit:
/// for(int i = 0; i < 100; i++) {
///    if(units[i] == nullptr)
///        units[i] = new Unit;
/// }
///
/// When units are destroyed, pointer to it is just set back to null (and probably memory is destroyed)
/// units[unit_to_delete] = nullptr; 
///
/// Apparently CHUNKS are 4096 units length (linked list of array of chunks of 4096 for memory management)


void PatchSwitchPlayerColor::enable()
{
	PatchScreenUpdate::registerScreenUpdate([this]() { frame(); });
}

void PatchSwitchPlayerColor::frame()
{

	if (!Keyboard::isKeyJustDown(VK_F3)) {
		return;
	}

	switchUnits(1, 5);
	switchUnits(6, 1);
	switchUnits(9, 6);
}

void PatchSwitchPlayerColor::switchUnits(int playerFrom, int playerTo)
{
#pragma pack(push, 1)
	struct Unit {
		int8_t data[380];
		int color;
		int8_t data2[808-380-sizeof(int)];
		int player;
	};
#pragma pack(pop)
	// Static address
	// staticVar -> 
	//
	//
	addr::ASMADDR allUnitsPointer = addr::ASMADDR::exe(0x6E8730, 4);
	void* ptr = *reinterpret_cast<void**>(allUnitsPointer.getAddress());

	if (!ptr) {
		return;
	}

	Unit** allUnits = reinterpret_cast<Unit**>(reinterpret_cast<char*>(ptr) + 4);
	const int chunkLength = 1000; // Also work only for 4096 first units

	for (int i = 0; i < chunkLength; i++) {

		if (allUnits[i] != nullptr) {
			Unit* unit = allUnits[i];

			if (unit->player == playerFrom) {
				unit->color = playerTo;
				unit->player = playerTo;
			}
		}
	}
}

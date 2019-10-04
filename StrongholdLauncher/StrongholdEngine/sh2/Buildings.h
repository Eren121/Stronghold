#pragma once

#include "../pch.h"

class Building
{
private:
	char* address;

	template<typename T>
	inline T* offset(int offset) const {
		return reinterpret_cast<T*>(address + strlen(address) + offset);
	}

	enum {
		OFFSET_BUILDING_SIZE_X = 36,
		OFFSET_BUILDING_SIZE_Y = 40,
		OFFSET_GUI_TYPE = 45,
		OFFSET_LIFE
	};

	enum GuiType {
		GUI_MARKET = 1,
		GUI_FOOD = 7,
		GUI_CONSTRUCT = 8, /* And Also 9 */
		GUI_ARMOURY = 10,
		GUI_INN = 11,
		GUI_TAXES = 16
	};

public:
	inline Building(int address)
		: address(reinterpret_cast<char*>(reinterpret_cast<int>(GetModuleHandle(NULL)) + address))
	{
	}

	inline const char* getBuildingName() const {
		return address;
	}
	/**
	 * Red Square on Ground when placing building
	 * Can be useful for mappers
	 *
	 * When  value is lower than original building: may be visual artefacts
	 * When Building placement size is zero: the building may be placed amost anywhere
	 */
	inline int getConstructionSizeX() const {
		return *offset<int>(OFFSET_BUILDING_SIZE_X);
	}

	inline int getConstructionSizeY() const {
		return *offset<int>(OFFSET_BUILDING_SIZE_Y);
	}

	inline void setConstructionSize(int x, int y) {
		*offset<int>(OFFSET_BUILDING_SIZE_X) = x;
		*offset<int>(OFFSET_BUILDING_SIZE_Y) = y;
	}

	/**
	 * Gui Type when clicking on building
	 * When a type of gui is set, the game consider that the original building is placed so not constructible (for example treasury)
	 */
	inline int getGuiType() const {
		return *offset<int>(OFFSET_GUI_TYPE);
	}

	inline void setGuiType(int guiType) const  {
		*offset<int>(OFFSET_GUI_TYPE) = guiType;
	}

	/**
	 * BUILDING LIFE
	 * 0: Infinite life
	 * Negative value: The building is automatically destroyed when positioned (useful for mapper to create ruined towers)
	 */
	inline float getMaxLife() const {
		return *offset<float>(OFFSET_LIFE);
	}

	inline void setMaxLife(float maxLife) const {
		*offset<float>(OFFSET_LIFE) = maxLife;
	}
};

namespace buildings
{
	extern Building TowerGreat;
	extern Building TowerLookout;

	extern Building MarketWoodPrice;
};
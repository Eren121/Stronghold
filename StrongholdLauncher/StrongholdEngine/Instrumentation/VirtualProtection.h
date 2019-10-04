#pragma once

#include "../pch.h"

/////////////////://///////
/// VirtualProtect RAII //
//////////////////////////
class VirtualProtection
{
private:
	LPVOID lpAddress;
	DWORD dwSize;
	DWORD flNewProtect;
	DWORD flOriginalProtection;

public:
	VirtualProtection(LPVOID lpAddress, DWORD dwSize, DWORD flProtect);
	VirtualProtection(const VirtualProtection&) = delete;
	VirtualProtection(VirtualProtection&&) = delete;
	~VirtualProtection();

	VirtualProtection& operator=(VirtualProtection&&) = delete;
	VirtualProtection& operator=(const VirtualProtection&) = delete;
};
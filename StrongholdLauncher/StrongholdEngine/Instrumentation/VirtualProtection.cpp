#include "pch.h"
#include "VirtualProtection.h"
#include <iostream>

VirtualProtection::VirtualProtection(LPVOID lpAddress, DWORD dwSize, DWORD flProtect)
: lpAddress(lpAddress),
	dwSize(dwSize),
	flNewProtect(flProtect),
	flOriginalProtection(0)
{
	if (!VirtualProtect(lpAddress, dwSize, flNewProtect, &flOriginalProtection)) {
		std::cerr << "VirtualProtect error" << std::endl;
	}
}

VirtualProtection::~VirtualProtection()
{
	if (!VirtualProtect(lpAddress, dwSize, flOriginalProtection, &flNewProtect)) {
		std::cerr << "VirtualProtect error" << std::endl;
	}
}
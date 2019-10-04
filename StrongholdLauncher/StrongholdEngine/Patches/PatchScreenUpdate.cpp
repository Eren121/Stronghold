#include "pch.h"
#include "PatchScreenUpdate.h"
#include "Functional.h"
#include "Instrumentation/Address.h"

std::vector < std::function<void()>> PatchScreenUpdate::callbacks;

void PatchScreenUpdate::enable()
{
	LoadLibraryA(addr::FileRequired("dragonfly.dll").c_str());
	addr::ASMADDR address = addr::ASMADDR::fromLib(0x00028010, 10, "dragonfly.dll");
	address.BeforePatch([]() { call_each(callbacks); });
}
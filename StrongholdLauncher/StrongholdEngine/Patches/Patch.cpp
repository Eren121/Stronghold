#include "pch.h"
#include "Patch.h"
#include <iostream>

Patch::~Patch()
{
}

void Patch::registerPatch(Patch* patch, const char* patchName)
{
	std::cout << "Registering patch " << patchName << std::endl;
	getPatches().emplace_back(patch);
}
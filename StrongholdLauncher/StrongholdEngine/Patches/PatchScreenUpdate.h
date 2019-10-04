#pragma once
#include "../pch.h"
#include "Patch.h"
#include "../sh2/Buildings.h"
#include <sstream>
#include <intrin.h>
#include <functional>
#include <vector>

class PatchScreenUpdate
	: public Patch
{
	REGISTER(PatchScreenUpdate);

private:
	static std::vector < std::function<void()>> callbacks;
	
public:
	PatchScreenUpdate() = default;
	~PatchScreenUpdate() override = default;

	void enable() override;


	inline static void registerScreenUpdate(std::function<void()> f) {
		callbacks.push_back(f);
	}
};
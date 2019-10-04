#pragma once
#include "../pch.h"
#include <vector>
#include <memory>

template<typename T>
class InstanciationCallback
{
public:
	static int i;

private:
	static int trigger();
};

template<typename T>
int InstanciationCallback<T>::trigger()
{
	T::__register_patch();
	return 0;
}

template<typename T>
int InstanciationCallback<T>::i = InstanciationCallback<T>::trigger();


#define REGISTER(Class)										\
	friend class InstanciationCallback<Class>;				\
	static void __register_patch() {						\
		InstanciationCallback<Class>::i++;					\
		Patch::registerPatch(new Class, #Class);			\
	}


class Patch
{
protected:
	static void registerPatch(Patch* patch, const char* patchName);

public:
	Patch() = default;
	virtual ~Patch() = 0;

	static inline auto& getPatches() {
		static std::vector<std::unique_ptr<Patch>> patches;
		return patches;
	}

	virtual void enable() = 0;
};
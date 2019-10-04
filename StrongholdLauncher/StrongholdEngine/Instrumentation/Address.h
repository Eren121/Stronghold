#pragma once
#include "../pch.h"

#include <string>

enum PatchFlags {
	PATCH_NOFLAGS = 0x0,
	PATCH_PRESERVEREGISTERS = 0x1, /* Preserve Registers */
	PATCH_CAPTUREREGISTERS = 0x2, /* Store ESP that it should be at this point */

	/* The jmp back asm code may not be executed if the instruction contained originally a "ret"
	 * It does no verifications and should no be a problem (because it's never executed) and simplify this API
	 */

	PATCH_DEFAULT = PATCH_PRESERVEREGISTERS
};

namespace addr
{
	std::string FileRequired(const std::string& name);

	inline DWORD GetCallOrJumpOffset(DWORD dwSource, DWORD dwDestination)
	{
		const DWORD jmp_size = 5; /* Size of jmp instruction */
		return dwDestination - (dwSource + jmp_size);
	}

	inline void RelativeCallOrJump(DWORD dwCallAddress, DWORD dwDestination)
	{
		DWORD dwRelativeAddr = GetCallOrJumpOffset(dwCallAddress, dwDestination);
		*(DWORD*)((BYTE*)dwCallAddress + 1) = dwRelativeAddr;
	}

	extern DWORD EAX, EBX, ECX, EDX, ESP, ESI;

	typedef void(*CBFUNCTION)();

	class ASMADDR {
	private:
		DWORD address;
		DWORD size;

	public:

		inline static ASMADDR exe(DWORD address, DWORD size)
		{
			return ASMADDR(reinterpret_cast<DWORD>(GetModuleHandle(NULL)) + address, size);
		}

		inline static ASMADDR fromLib(DWORD address, DWORD size, const std::string& name)
		{
			return ASMADDR(reinterpret_cast<DWORD>(GetModuleHandleA(name.c_str())) + address, size);
		}

		ASMADDR(DWORD address, DWORD size);
		
		inline DWORD getAddress() const { return address;  }
		inline DWORD getSize() const { return size; }

		inline void setAddress(DWORD address) { this->address = address;  }
		inline void setSize(DWORD size) { this->size = size;  }

		// Add callback function to call before this ASM instruction execute
		void BeforePatch(CBFUNCTION callbackFunction, DWORD flags = PATCH_DEFAULT);
	};

	struct ASMPROC {
	private:
		ASMADDR entryPoint; // Minimum size >= 5 to override without separate an asm instruction
		ASMADDR ret; // Does not contains the "ret" instruction directly, but instruction located at ret + retSize is end of "ret" instruction
	
	public:
		ASMPROC(const ASMADDR& entryPoint, const ASMADDR& ret);

		inline const ASMADDR& getEntryPoint() const { return entryPoint; }
		inline const ASMADDR& getRet() const { return ret; }

		inline void setEntryPoint(const ASMADDR& entryPoint) { this->entryPoint = entryPoint; }
		inline void setRet(const ASMADDR& ret) { this->ret = ret; }
	};
}

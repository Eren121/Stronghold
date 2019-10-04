#include "pch.h"

#include "Address.h"
#include "ASM.h"
#include "VirtualProtection.h"

#include <list>
#include <vector>
#include <sstream>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

namespace addr
{
	DWORD EAX = 0, EBX = 0, ECX = 0, EDX = 0, ESP = 0, ESI = 0;

	ASMADDR::ASMADDR(DWORD address, DWORD size)
		: address(address),
		  size(size)
	{
	}

	void ASMADDR::BeforePatch(CBFUNCTION callbackFunction, DWORD flags)
	{
		// Steps:
		// 1. Create custom code (call callback function /and eventually save registers, stack) + reserve memory to jmp back
		// 2. Allocate memory to store the custom code
		// 3. End of custom code jump back to after the overrided asm instructions to continue the procedure (not executed if original instruction contains a "ret", its O.K.)
		// 4. Save + Override ASM code location to jump to custom code

		/// 1. ///

		std::list<CHAR> bytes = { call, 0, 0, 0, 0 }; // Custom code that will be allocated at unknow memory address for now.
		decltype(bytes)::iterator bytesCall = bytes.begin(); // Store iterator (never invalidated that's why LIST)

		if (flags & PATCH_PRESERVEREGISTERS) { // Preserve Registers: Wrap most of the code (in fact callback call) code between PUSHA and POPA

			bytes.insert(bytes.begin(), pusha);
			bytes.insert(bytes.end(), popa);
		}

		if (flags & PATCH_CAPTUREREGISTERS) { // Get ESP Value: Save ESP value into a pre-reserved Global variable (translated into a memory location) directly before ANY code, and before PUSHA/POPA that will also modify ESP
										 // Compiler may add stack-protector. To get arguments location

			//std::vector<CHAR> esp = { '\x89', '\x25', 0, 0, 0, 0 }; // Reserve 4 bytes to store ESP address
			//*(DWORD**)(esp.data() + 2) = &ESP;
			std::vector<CHAR> esp;

			std::vector<std::pair<DWORD*, std::string>> registers {
				{&EAX, "\xA3"},
				{&EBX, "\x89\x1D"},
				{&ECX, "\x89\x0D"},
				{&EDX, "\x89\x15"},
				{&ESI, "\x89\x35"},
				{&ESP, "\x89\x25"}
			};

			for (auto [reg, instrs] : registers) {

				esp.insert(esp.end(), instrs.begin(), instrs.end());
				esp.insert(esp.end(), reinterpret_cast<char*>(&reg), reinterpret_cast<char*>(&reg + 1));
			}

			bytes.insert(bytes.begin(), esp.begin(), esp.end());
		}

		// Original overwritten code
		bytes.insert(bytes.end(), (CHAR*)address, (CHAR*)address + size);

		std::vector<CHAR> jmpBackBytes = { jmp, 0, 0, 0, 0 };
		bytes.insert(bytes.end(), jmpBackBytes.begin(), jmpBackBytes.end());
		decltype(bytes)::iterator jmpBack = std::next(bytes.end(), -5);

		/* MEMORY EDITING */

		/// 2. ///

		LPVOID customCodeAddr = VirtualAlloc(NULL, bytes.size(), MEM_COMMIT, PAGE_EXECUTE_READWRITE);

		/// 3. ///

		// Fill custom code memory
		std::copy(bytes.begin(), bytes.end(), (CHAR*)customCodeAddr);
			
		//Make sure the original function is writable and readable
		VirtualProtection proc((LPVOID)address, size, PAGE_EXECUTE_READWRITE);

		// Fill original memory
		*(BYTE*)address = jmp;
		RelativeCallOrJump(address, (DWORD)customCodeAddr);

		/// 4. ///

		// Call callback functions with relative address
		RelativeCallOrJump((DWORD)customCodeAddr + std::distance(bytes.begin(), bytesCall), (DWORD)callbackFunction);

		// Go back to original function with relative address
		RelativeCallOrJump((DWORD)customCodeAddr + std::distance(bytes.begin(), jmpBack), (DWORD)address + size);
	}

	ASMPROC::ASMPROC(const ASMADDR& entryPoint, const ASMADDR& ret)
		: entryPoint(entryPoint),
		  ret(ret)
	{
	}

	std::string FileRequired(const std::string& name)
	{
		// Search at first in same directory than running executable
		fs::path path = fs::current_path();
		path = path.parent_path();
		path = path.append("Stronghold2.exe");

		if (fs::exists(path)) {

			return path.string();
		}

		// Alternative last chance hard-coded path
		fs::path hardcoded = R"end(C:\Program Files (x86)\Steam\steamapps\common\Stronghold 2\Stronghold2.exe)end";

		if (fs::exists(hardcoded)) {

			return hardcoded.string();
		}

		std::stringstream ss;
		ss << "Can't find Stronghold2.exe" << std::endl
			<< "Searched " << path
			<< " and " << hardcoded;

		throw std::runtime_error(ss.str());
	}
}
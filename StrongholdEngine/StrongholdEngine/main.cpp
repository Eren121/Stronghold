#include "main.h"
#include "stats.h"
#include <stdio.h>
#include <Psapi.h>
#include <iostream>

static_assert(sizeof(void*) == 4, "Stronghold 2.exe is 32 bits process: this need to be compiled also in 32 bits");

int main(int argc, char* argv[])
{
    unsigned long baseAddress(0);
    
    std::cout << "Finding window..." << std::endl;
	HWND hwnd = FindWindowA(nullptr, "teeeeest"); // HWND (Windows window) by Window Name

	// Check if HWND found the Window
	if(!hwnd) {
		std::cout << "Can't find Process." << std::endl;
	}
    else {
		DWORD procID; // A 32-bit unsigned integer, DWORDS are mostly used to store Hexadecimal Addresses
        
        std::cout << "Getting thread process id..." << std::endl;
		GetWindowThreadProcessId(hwnd, &procID); // Getting our Process ID, as an ex. like 000027AC
        
        std::cout << "Opening process..." << std::endl;
		HANDLE handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procID); // Opening the Process with All Access

		if(!handle) {
			std::cout << "Can't open Process." << std::endl;
		}
        else {
            
            std::cout << "Getting base address..." << std::endl;
            baseAddress = getProcessBaseAddress(handle);
            
            if(!baseAddress) {
                std::cerr << "Error while getting base address" << std::endl;
            }
            else {
                displayUnits(handle, reinterpret_cast<char*>(baseAddress));
            }
        }
    }
    
    system("pause");
    return 0;
}

unsigned int getProcessBaseAddress(HANDLE hProcess)
{
    HMODULE pHmodule;
    ULONG cb = 0;
    
    GetLastError();
    
    if(EnumProcessModulesEx(hProcess, &pHmodule, sizeof(HMODULE), &cb, LIST_MODULES_32BIT)) {
        return reinterpret_cast<unsigned int>(pHmodule);
    }
    else {
        std::cerr << "Erreur while getting base address of process" << std::endl;
        std::cerr << GetLastError() << std::endl;
        return 0;
    }
}

std::map<std::string, char*> loadUnitAddresses(const std::string& fileName)
{
    std::ifstream file(fileName.c_str());
    std::map<std::string, char*> units;
    
    if(!file.is_open()) {
        std::cerr << "Erreur opening units.txt" << std::endl;
        exit(-1);
    }
    
    std::string unitName;
    int address;

    while(file >> unitName >> std::hex >> address) {
        
        units[unitName] = reinterpret_cast<char*>(address);
    }
    
    return units;
}
#include "stats.h"
#include "main.h"
#include <iostream>

void displayUnits(HANDLE handle, char* baseAddress)
{
    std::cout << "-------------- Display units ----------" << std::endl;
    
    std::map<std::string, char*> units(loadUnitAddresses("C:/Users/Moi/Documents/StrongholdEngine/StrongholdEngine/units_map.txt"));
	char unit[255]; // We store the Value we read from the Process here
    
    for(const std::pair<std::string, char*>& entry : units) {
        
        ReadProcessMemory(handle, (char*)(baseAddress + reinterpret_cast<int>(entry.second)), unit, sizeof(unit), 0);
        
        if(strcmp(unit, entry.first.c_str()) != 0) {
            std::cerr << "Bad unit mapped" << std::endl;
            std::cerr << "'" << entry.first << "' in file and '" << unit << "' in memory" << std::endl;
        }
        else {
            std::cout << "Found unit: " << unit << std::endl;
            
            float* unitHealth = reinterpret_cast<float*>(unit + 0x10 * 4 + 0x4 * 3);
            float* unitDamage = reinterpret_cast<float*>(unit + 0x10 * 8 + 0x4 * 3);
            float* unitSpeed = reinterpret_cast<float*>(unit + 0x10 * 4);
            //int* unitId = reinterpret_cast<int*>(unit + 0x10);
            
            std::cout << "Health: " << *unitHealth << std::endl;
            std::cout << "Damage (melee): " << *unitDamage << std::endl;
            std::cout << "Speed: " << *unitSpeed << std::endl;
            //std::cout << "ID: " << *unitId << std::endl;
        }
    }
}

#ifndef MAIN_H
#define MAIN_H

#include <Windows.h>
#include <map>
#include <string>
#include <fstream>

unsigned int getProcessBaseAddress(HANDLE hProcess);
std::map<std::string, char*> loadUnitAddresses(const std::string& fileName);

#endif // MAIN_H
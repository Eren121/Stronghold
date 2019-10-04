#pragma once

#include <string>
#include <exception>
#include <Windows.h>

class Launcher
{
private:
	std::string executable; // Path of executable
	STARTUPINFOA startupInfo;
	PROCESS_INFORMATION processInformation;
	HANDLE childRead, childWrite;

public:
	class Exception
		: public std::exception {
	private:
		std::string message;

	public:
		Exception(const std::string& message);
		~Exception() override;

		const char* what() const noexcept override;
	};

	Launcher(const std::string& path);
	~Launcher();

	Launcher(const Launcher&) = delete;			// Non-copyable
	Launcher(Launcher&&) = delete;
	Launcher& operator=(const Launcher&) = delete;
	Launcher& operator=(Launcher&&) = delete;

	void launchAndPause();						// Launch process and pause process
	void resume();								// Resume process
	void waitFinish();							// Wait the process to finish (blocking function)
	void killProcess();							// Kill the process
	DWORD getProcessId() const;
};


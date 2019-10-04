#include "Launcher.h"

Launcher::Launcher(const std::string& path)
	: executable(path)
{
}

Launcher::~Launcher()
{
	killProcess();
}

void Launcher::launchAndPause()
{
	SECURITY_ATTRIBUTES sa = {};
	sa.bInheritHandle = TRUE;

	if (!CreatePipe(&childRead, &childWrite, &sa, 0)) {
		throw Exception("CreatePipe");
	}

	startupInfo.cb = sizeof(startupInfo);
	startupInfo.dwFlags = STARTF_USESTDHANDLES;
	startupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
	startupInfo.hStdOutput = childWrite;
	startupInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);

	BOOL processCreated = CreateProcessA(
		executable.c_str(),
		NULL,
		NULL,
		NULL,
		TRUE,
		CREATE_SUSPENDED, // Pause process after launch
		NULL,
		NULL,
		&startupInfo,
		&processInformation
	);

	if (!processCreated) {
		throw Exception("CreateProcessA");
	}
}

void Launcher::resume()
{
	if (ResumeThread(processInformation.hThread) == -1)
		throw Exception("ResumeThread");
}

void Launcher::waitFinish()
{
	DWORD dwRead, dwWritten;
	CHAR chBuf[256];
	BOOL bSuccess = FALSE;
	HANDLE hParentStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD total_available_bytes;

	while (true) {

		if (FALSE == PeekNamedPipe(childRead,
			0,
			0,
			0,
			&total_available_bytes,
			0))
		{
			// Handle failure.
			throw Exception("PeekNamedPipe");
		}
		else if (total_available_bytes > 0)
		{
			// Read data from pipe ...

			bSuccess = ReadFile(childRead, chBuf, sizeof chBuf, &dwRead, NULL);
			if (!bSuccess || dwRead == 0) break;

			bSuccess = WriteFile(hParentStdOut, chBuf, dwRead, &dwWritten, NULL);
			if (!bSuccess) break;
		}
		
		if (WaitForSingleObject(processInformation.hProcess, 100) == WAIT_FAILED) {
			throw Exception("WaitForSingleObject");
		}
	}
}

void Launcher::killProcess()
{
	TerminateProcess(processInformation.hProcess, 1);
	CloseHandle(processInformation.hProcess);
	CloseHandle(childRead);
	CloseHandle(childWrite);
}

DWORD Launcher::getProcessId() const
{
	return processInformation.dwProcessId;
}

Launcher::Exception::Exception(const std::string& message)
	: message(message)
{
	this->message += exception::what();
}

Launcher::Exception::~Exception()
{
}

const char* Launcher::Exception::what() const noexcept
{
	return message.c_str();
}

#include "Launcher.h"
#include "injector/injector.h"
#include <stdexcept>
#include <sstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::string findStrongholdPath()
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

void launcher()
{
	TCHAR currentFileName[MAX_PATH];
	fs::path currentPath;
	Launcher launcher(findStrongholdPath());
	injector_t* injector;

	GetModuleFileName(NULL, currentFileName, MAX_PATH);
	currentPath = currentFileName;
	currentPath = currentPath.parent_path();
	currentPath = currentPath.append("StrongholdEngine.dll");

	std::cout << "DLL Search path: " << currentPath << std::endl;

	launcher.launchAndPause();

	/* attach to a process whose process id is 1234. */
	if (injector_attach(&injector, launcher.getProcessId()) != 0) {

		std::ostringstream ss;
		ss << "ATTACH ERROR: "
			<< injector_error();

		throw std::runtime_error(ss.str());
	}

	/* inject a shared library into the process. */
	if (injector_inject(injector, currentPath.string().c_str()) != 0) {

		std::ostringstream ss;
		ss << "INJECT ERROR: "
			<< injector_error();

		throw std::runtime_error(ss.str());
	}


	launcher.resume();
	launcher.waitFinish();

	/* cleanup */
	injector_detach(injector);
}

int main()
{
	try {

		launcher();
		return EXIT_SUCCESS;
	}
	catch (const std::exception& exception) {

		std::cerr << "Fatal error: " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}
}
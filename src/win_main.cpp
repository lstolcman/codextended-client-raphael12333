#include "shared.h"
#include "Commctrl.h"
#include "ShlObj.h"
#include "Shlwapi.h"
#include "Shellapi.h"

static int(__stdcall *entryPoint)(HINSTANCE, HINSTANCE, LPSTR, int) = (int(__stdcall*)(HINSTANCE, HINSTANCE, LPSTR, int))0x4640B0;

char sys_cmdline[MAX_STRING_CHARS];

extern "C" bool bClosing = false;

extern HMODULE hModule;
HINSTANCE hInst;
#ifdef DEBUG
HMODULE hLogFile;
#endif

std::vector<threadInfo_t> threadsinfo;

void Sys_Unload()
{
	bClosing = true;
	static bool unloaded = false;

	if (unloaded)
		return;
	unloaded = true;

#ifdef DEBUG
	_CrtDumpMemoryLeaks();
	CloseHandle(hLogFile);
#endif
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	hInst = hInstance;
	strncpy(sys_cmdline, lpCmdLine, sizeof(sys_cmdline) - 1);

	void MSS32_Hook();
	MSS32_Hook();

	extern bool mss32_original_loaded;
	if (!mss32_original_loaded)
		return 0;

	return entryPoint(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}
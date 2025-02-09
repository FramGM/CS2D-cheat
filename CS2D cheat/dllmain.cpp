
#include <windows.h>
#include <iostream>

class Player
{
public:
	int& m_iClip2()
	{
		return *reinterpret_cast<int*>(this + 0x14);
	}

	int& m_iClip1()
	{
		return *reinterpret_cast<int*>(this + 0x18);
	}
};

DWORD Main(HINSTANCE HModule)
{
	//AllocConsole();
	//SetConsoleTitleA("neir0cum");
	//freopen_s(reinterpret_cast<FILE**> stdin, "CONIN$", "r", stdin);
	//freopen_s(reinterpret_cast<FILE**> stdout, "CONOUT$", "w", stdout);

	while (true)
	{
		auto pCS2D = (uintptr_t)GetModuleHandleA("CS2D.exe");
		uintptr_t pPlayerUnk = *(uintptr_t*)(pCS2D + 0x4A58F8);
		printf("pPlayerUnk: %x\n", pPlayerUnk);
		Player* pPlayer = *reinterpret_cast<Player**>(pPlayerUnk + 0x24C);
		printf("pPlayer: %p\n", (void**)pPlayer);

		if (!pPlayer)
			continue;
		pPlayer->m_iClip1() = 9999;
		pPlayer->m_iClip2() = 9999;
	}

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hModule);

		HANDLE hMainThread = CreateThread(NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Main), hModule, 0, NULL);

		if (hMainThread != nullptr)
			CloseHandle(hMainThread);
	}

	return TRUE;
}
#include <windows.h>
#include <iostream>

int uPlayerOffset = 0x4A58F8;

struct Vector2D
{
	Vector2D(float y, float x) { this->y = y; this->x = x; };

	float x = 0.0f, y = 0.0f;
};

class C_Weapon
{
public:
	char pad_0000[20]; //0x0000
	int32_t m_iClip2; //0x0014
	int32_t m_iClip1; //0x0018
	char pad_001C[1000]; //0x001C
}; //Size: 0x0404

class C_Player
{
public:
	char pad_0000[112]; //0x0000
	float m_flGameTime; //0x0070
	char pad_0074[352]; //0x0074
	Vector2D m_vecOrigin; //0x01D4
	char pad_01DC[112]; //0x01DC
	C_Weapon* m_pWeapon; //0x024C
	char pad_0250[3564]; //0x0250
}; //Size: 0x103C

DWORD Main(HINSTANCE HModule)
{
	AllocConsole();
	SetConsoleTitleA("neir0cum");
	freopen_s(reinterpret_cast<FILE**> stdin, "CONIN$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**> stdout, "CONOUT$", "w", stdout);
	auto pCS2D = (uintptr_t)GetModuleHandleA("CS2D.exe");

	while (true)
	{
		C_Player* pPlayer = *reinterpret_cast<C_Player**>(pCS2D + uPlayerOffset);
		printf("pPlayerUnk: %x\n", pPlayer);

		if (!pPlayer)
			continue;

		printf("X pos: %lf\tY pos: %lf", pPlayer->m_vecOrigin.x, pPlayer->m_vecOrigin.y);

		auto pWeapon = pPlayer->m_pWeapon;
		if (!pWeapon)
			continue;

		pWeapon->m_iClip1 = 9999;
		pWeapon->m_iClip2 = 9999;
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
module;

#include "../include.h"

#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>

#include "../sdk/sdk.h"

export module hook;
import memory;
import util;

#define DEFINE_HOOK( name, retType, ... ) \
using name##_t = retType(*)( __VA_ARGS__ ); \
name##_t m_o##name; \
retType name(__VA_ARGS__)

export namespace Hooks {
	// basic vmt, do not use this. Please...
	uintptr_t VMTHook(void* base, size_t index, uintptr_t hookPtr) {
		uintptr_t table = *(uintptr_t*)(base);
		uintptr_t functionPtr = table + index * sizeof(uintptr_t);
		uintptr_t original = *(uintptr_t*)(functionPtr);

		DWORD old;
		VirtualProtect((LPVOID)functionPtr, sizeof(uintptr_t), PAGE_EXECUTE_READWRITE, &old);
		*(uintptr_t*)(functionPtr) = (uintptr_t)hookPtr;
		VirtualProtect((LPVOID)functionPtr, sizeof(uintptr_t), old, &old);

		return original;
	}

	bool Setup();
	void Restore();

	DEFINE_HOOK(CreateMove, uintptr_t*, CInput*, int, float, bool);
	DEFINE_HOOK(Present, HRESULT, IDXGISwapChain*, UINT, UINT);

	LRESULT __stdcall WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	WNDPROC m_oWndProc;
}

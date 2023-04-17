import hook;
import memory;
import mizu;
import util;
import render;

#include "../include.h"
#include "../sdk/sdk.h"

#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include <dxgi.h>

#include "../deps/imgui/imgui.h"

void LeakSwapchain() {
	/* This cannot be called in DllMain https://learn.microsoft.com/en-us/windows/win32/direct3ddxgi/d3d10-graphics-programming-guide-dxgi#dxgi-responses-from-dllmain */
	Render::m_window = FindWindowW(L"Respawn001", NULL);

	D3D_FEATURE_LEVEL featureLevel;
	const D3D_FEATURE_LEVEL featureLevels[] = { D3D_FEATURE_LEVEL_11_0 };

	DXGI_RATIONAL refreshRate;
	refreshRate.Numerator = 60;
	refreshRate.Denominator = 1;

	DXGI_MODE_DESC bufferDesc;
	bufferDesc.Width = 100;
	bufferDesc.Height = 100;
	bufferDesc.RefreshRate = refreshRate;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SAMPLE_DESC sampleDesc;
	sampleDesc.Count = 1;
	sampleDesc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC swapChainDesc;
	swapChainDesc.BufferDesc = bufferDesc;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = Render::m_window;
	swapChainDesc.Windowed = 1;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	HRESULT hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0, featureLevels, 1, D3D11_SDK_VERSION, &swapChainDesc, &Render::m_swapChain, &Render::m_device, &featureLevel, &Render::m_context);
	if (FAILED(hr)) {
		// same format as %08X for std::format is { :08X }
		Util::Log<LOG_ERROR>("failed to create device and swapchain!");
		printf("HRESULT: 0x%08X\n", hr);
		return;
	}

	Util::Log("swapchain: 0x{:X}", (uintptr_t)Render::m_swapChain);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

bool Hooks::Setup() {
	m_oCreateMove = (CreateMove_t)VMTHook(SDK::m_input, 4, (uintptr_t)CreateMove);
	Util::Log("hooks::setup: CreateMove {:#x}!", (uintptr_t)m_oCreateMove);

	Util::Log("hooks::setup done!\n");
	return true;
}

void Hooks::Restore() {
	// restore vmt
	// ...

	// unhook the wndproc
	SetWindowLongPtrA(Render::m_window, GWLP_WNDPROC, (LONG_PTR)m_oWndProc);
}

uintptr_t* Hooks::CreateMove(CInput* input, int sequence, float inputSampleTime, bool active) {
	const auto pseudoMD5 = m_oCreateMove(input, sequence, inputSampleTime, active);

	static bool leaked = false;
	if (!leaked) {
		LeakSwapchain();
		m_oPresent = (Present_t)VMTHook(Render::m_swapChain, 8, (uintptr_t)Present);
		Util::Log("hooks::setup: Present {:#x}!", (uintptr_t)m_oPresent);
		leaked = true;
	}

	CUserCmd* cmd = input->GetUserCmd(-1, sequence);
	if (!Mizu::OnTick(cmd)) {
		Mizu::Reset();
		return pseudoMD5;
	}

	//
	// features
	//

	return pseudoMD5;
}

HRESULT Hooks::Present(IDXGISwapChain* swapChain, UINT syncInterval, UINT flags) {
	Render::Run();
	return m_oPresent(swapChain, syncInterval, flags);
}

LRESULT __stdcall Hooks::WndProc(const HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(m_oWndProc, hWnd, uMsg, wParam, lParam);
}
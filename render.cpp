import mizu;
import hook;
import render;
import util;

import visuals;

#include "include.h"
#include "util/hash.h"

#pragma comment (lib, "d3d11.lib")
#include <d3d11.h>
#include <dxgi.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx11.h>
#include <imgui/imgui_impl_win32.h>

#include "../sdk/sdk.h"

void Render::D3DInit() {
	if (m_d3dInitalized)
		return;

	// get window size
	RECT rect;
	if (!GetClientRect(m_window, &rect)) {
		Util::Log<LOG_ERROR>(_("failed to get window rect!"));
		return;
	}

	m_screenSize.x = (int)(rect.right - rect.left);
	m_screenSize.y = (int)(rect.bottom - rect.top);
	Util::Log(_("window size: {}, {}"), m_screenSize.x, m_screenSize.y);

	if (FAILED(m_swapChain->GetDevice(__uuidof(ID3D11Device), (void**)(&m_device)))) {
		Util::Log<LOG_ERROR>(_("failed to get device from swapchain!"));
		return;
	}

	if (!m_device) {
		Util::Log<LOG_ERROR>(_("failed to get device from swapchain!"));
		return;
	}

	m_device->GetImmediateContext(&m_context);

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags = ImGuiConfigFlags_NoMouseCursorChange;
	io.IniFilename = NULL;

	// style colors
	ImGui::StyleColorsDark();

	if (!ImGui_ImplWin32_Init(m_window)) {
		Util::Log<LOG_ERROR>(_("failed to initialize imgui win32!"));
		return;
	}

	if (!ImGui_ImplDX11_Init(m_device, m_context)) {
		Util::Log<LOG_ERROR>(_("failed to initialize imgui dx11!"));
		return;
	}

	Hooks::m_oWndProc = (WNDPROC)(SetWindowLongPtr(m_window, GWLP_WNDPROC, (LONG_PTR)Hooks::WndProc));
	m_d3dInitalized = true;
	Util::Log(_("d3d::setup done!\n"));
}

void Render::Run()
{
	D3DInit();

	if (!m_d3dInitalized)
		return;

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::IsKeyReleased(VK_INSERT) || ImGui::IsKeyReleased(VK_ESCAPE))
		m_menuOpen = !m_menuOpen;

	// - menu codenz starts here duh
	if (m_menuOpen) {
		ImGui::Begin(_("mizu"), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);
		ImGui::Text(_("Hello, world!"));
		ImGui::BeginGroup();
		ImGui::Checkbox(_("Box ESP"), &Visuals::Config::box);
		ImGui::EndGroup();
	}
	// - menu codenz ends here duh

	// features need sdk to be initalized
	if (SDK::m_updated) {
		Visuals::Run();
	}

	ImGui::Render();
	//m_context->OMSetRenderTargets(1, &m_renderTargetView, NULL);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

bool Render::WorldToScreen(const Vector_t position, Point_t& screen)
{
	if (!SDK::m_viewMatrixPtr) {
		Util::Log<LOG_ERROR>(_("WorldToScreen: m_viewMatrixPtr is null!"));
		return false;
	}

	bool onScreen = true;
	const auto& viewMatrix = *SDK::m_viewMatrixPtr;
	float w = viewMatrix[3].Dot(Vector4_t(position, 1.f));
	if (w < 0.001f) {
		if (w == 0.f)
			w += FLT_EPSILON;
		onScreen = false;
	}

	screen = { m_screenSize / 2 };

	const float x = (viewMatrix.data[0].Dot(position) + viewMatrix.data[0][3]) / w;
	const float y = (viewMatrix.data[1].Dot(position) + viewMatrix.data[1][3]) / w;
	screen.x += (int)(x * screen.x);
	screen.y -= (int)(y * screen.y);

	return onScreen;
}
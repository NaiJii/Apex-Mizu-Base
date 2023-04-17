module;

#include <d3d11.h>
#include "sdk/sdk.h"

export module render;

export namespace Render {
	bool m_d3dInitalized = false;
	HWND m_window;
	IDXGISwapChain* m_swapChain;
	ID3D11Device* m_device;
	ID3D11DeviceContext* m_context;
	ID3D11RenderTargetView* m_renderTargetView;

	bool m_menuOpen = true;
	Point_t m_screenSize = { 0, 0 };

	void D3DInit();
	void Run();

	bool WorldToScreen(const Vector_t position, Point_t& screen);
}
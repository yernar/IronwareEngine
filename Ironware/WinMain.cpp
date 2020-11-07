#include <Windows.h>

LRESULT CALLBACK WndProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_CLOSE:
		PostQuitMessage( 1 );
		break;
	default:
		break;
	}
	return DefWindowProc( hWnd, msg, wParam, lParam );
}

int CALLBACK WinMain( 
	_In_ HINSTANCE hInstance, 
	_In_opt_ HINSTANCE hPrevInstance, 
	_In_ LPSTR lpCmdLine, 
	_In_ int nShowCmd 
)
{
	constexpr auto pClassName = "CNIronware";
	constexpr auto pWindowName = "Ironware Engine";

	//////////////////////////////////////////////////////////////////////////
	// Register Windows Class
	// -----------------------------------------------------------------------
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof( wc );
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = nullptr;
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = pClassName;
	wc.hIcon = nullptr;
	RegisterClassEx( &wc );

	//////////////////////////////////////////////////////////////////////////
	// Create Window Instance
	// -----------------------------------------------------------------------  
	HWND hWnd = CreateWindowEx(
		0, pClassName,
		pWindowName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		0, 0, 640, 480,
		nullptr, nullptr,
		hInstance, nullptr
	);
	//////////////////////////////////////////////////////////////////////////
	// Show the Window
	// -----------------------------------------------------------------------
	ShowWindow( hWnd, SW_SHOW );

	//////////////////////////////////////////////////////////////////////////
	// Process Message
	// -----------------------------------------------------------------------
	MSG msg;
	BOOL res;
	while( ( res = GetMessage( &msg, nullptr, 0, 0 ) ) > 0 )
	{
		if( res == -1 )
		{
			return -1;
		}
		TranslateMessage( &msg );
		DispatchMessage( &msg );
	}
	
	return msg.wParam;
}
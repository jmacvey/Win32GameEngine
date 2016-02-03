//-----------------------------------------------------------------
// Game Wrapper Object
// C++ Header - Wrapper.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Wrapper.h"

//----------------------------------------------------------------
// Static Variables initialization
//----------------------------------------------------------------
//std::tr1::shared_ptr<GEN::GameEngine> GEN::Wrapper::m_pGame(nullptr);
//std::tr1::shared_ptr<GEN::Wrapper> GEN::Wrapper::m_pWrapper(nullptr);


//----------------------------------------------------------------
// Wrapper Class method Definitions
//----------------------------------------------------------------

//----------------------------------------------------------------
// Constructor(s) / Destructor
//----------------------------------------------------------------

GEN::Wrapper::Wrapper(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPTSTR szWindowClass,
	LPTSTR szTitle, WORD wIcon, WORD wSmallIcon, int iWidth, int iHeight) :
	// initialization list
	m_pGame(nullptr), //m_pWrapper(this),
	m_hInstance(hInstance), m_lpfnWndProc(lpfnWndProc),
	m_hWindow(NULL),
	m_wIcon(wIcon), m_wSmallIcon(wSmallIcon),
	m_iWidth(iWidth), m_iHeight(iHeight),
	m_iFrameDelay(DEFAULT_FRAME_DELAY)
{

	// swap the static pointer
	// m_pWrapper = std::tr1::shared_ptr<Wrapper>(this);
	// Set the member variables for the game engine
	if (lstrlen(szWindowClass) > 0)
		lstrcpy(m_szWindowClass, szWindowClass);
	if (lstrlen(szTitle) > 0)
		lstrcpy(m_szTitle, szTitle);
}

GEN::Wrapper::~Wrapper()
{
}

//----------------------------------------------------------------
// General Methods
//----------------------------------------------------------------


LRESULT GEN::Wrapper::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		// Set the game window and start the game
		SetWindow(hWindow);
		// give the engine its specs
		SetEngineWindowSpecs();
		// give it the offscreen DC
		SetOffscreenDC();
		// Start the game engine
		m_pGame->GameStart(hWindow);
		return 0;
	case WM_DESTROY:
		// End the game and exit the application
		m_pGame->GameEnd();
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

BOOL GEN::Wrapper::InitializeWindow(int iCmdShow)
{
	WNDCLASSEX    wndclass;

	// Create the window class for the main window
	// we effectively create a window with properties given by the game engine
	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = m_lpfnWndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = m_hInstance;
	wndclass.hIcon = LoadIcon(m_hInstance,
		MAKEINTRESOURCE(GetIcon()));
	wndclass.hIconSm = LoadIcon(m_hInstance,
		MAKEINTRESOURCE(GetSmallIcon()));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = m_szWindowClass;

	// Register the window class
	if (!RegisterClassEx(&wndclass))
		return FALSE;

	// Calculate the window size and position based upon the game size
	int iWindowWidth = m_iWidth + GetSystemMetrics(SM_CXFIXEDFRAME) * 2,
		iWindowHeight = m_iHeight + GetSystemMetrics(SM_CYFIXEDFRAME) * 2 +
		GetSystemMetrics(SM_CYCAPTION);
	if (wndclass.lpszMenuName != NULL)
		iWindowHeight += GetSystemMetrics(SM_CYMENU);
	int iXWindowPos = (GetSystemMetrics(SM_CXSCREEN) - iWindowWidth) / 2,
		iYWindowPos = (GetSystemMetrics(SM_CYSCREEN) - iWindowHeight) / 2;

	// Create the window
	m_hWindow = CreateWindow(m_szWindowClass, m_szTitle, WS_POPUPWINDOW |
		WS_CAPTION | WS_MINIMIZEBOX, iXWindowPos, iYWindowPos, iWindowWidth,
		iWindowHeight, NULL, NULL, m_hInstance, (LPVOID)this);
	if (!m_hWindow)
		return FALSE;

	// Show and update the window
	ShowWindow(m_hWindow, iCmdShow);
	UpdateWindow(m_hWindow);

	return TRUE;
}

void GEN::Wrapper::SetEngineWindowSpecs()
{
	m_pGame->SetWindow(m_hWindow);
	m_pGame->SetHeight(m_iHeight);
	m_pGame->SetWidth(m_iWidth);
	m_pGame->SetInstance(m_hInstance);
	//m_pGame->SetIcon(GetIcon());
	//m_pGame->SetSmallIcon(GetSmallIcon());
};

void GEN::Wrapper::SetOffscreenDC()
{
	HDC hOffscreenDC = CreateCompatibleDC(GetDC(m_hWindow));
	HBITMAP hOffscreenBitmap = CreateCompatibleBitmap(GetDC(m_hWindow),
		m_iWidth, m_iHeight);
	// select the bitmap into the dc
	SelectObject(hOffscreenDC, hOffscreenBitmap);
	// store the values
	m_pGame->SetOffScreenDC(hOffscreenDC);
	m_pGame->SetOffscreenBitmap(hOffscreenBitmap);
}



//--------------------------------------------------------------
// Virtual Override Methods
//--------------------------------------------------------------

BOOL GEN::Wrapper::GameInitialize(HINSTANCE hInstance)
{
	//typedef std::tr1::shared_ptr<GEN::Wrapper> sp_Wrap;

	//m_pWrapper = sp_Wrap(this);
	// Create the game engine
	GEN::GameEngine* cGameEngine = new GEN::GameEngine();
	// swap it with the data member
	m_pGame = std::tr1::shared_ptr<GameEngine>(cGameEngine);
	cGameEngine = nullptr;
	if (m_pGame == NULL)
		return FALSE;

	// Set the frame rate
	SetFrameRate(5);

	return TRUE;
}


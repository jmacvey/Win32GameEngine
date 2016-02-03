//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - GameEngine.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------
#include "GameEngine.h"

//-----------------------------------------------------------------
// Static Variable Initialization
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// GameEngine Constructor(s)/Destructor
//-----------------------------------------------------------------
GEN::GameEngine::GameEngine() :
	// initialize list
	m_bSleep(FALSE), m_hWindow(NULL),
	m_hInstance(NULL),
	m_iWidth(0), m_iHeight(0),
	m_hOffscreenBitmap(NULL), m_hOffscreenDC(NULL),
	m_mpMIDIPlayer(nullptr)
	//, m_wIcon(0), m_wSmallIcon(0)
{
	typedef std::tr1::shared_ptr<MIDIPlayer> MidiPtr;

	m_mpMIDIPlayer = MidiPtr(new MIDIPlayer());
}

GEN::GameEngine::~GameEngine()
{
}

//-----------------------------------------------------------------
// Game Engine General Methods
//-----------------------------------------------------------------


LRESULT GEN::GameEngine::HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam)
{
	// Route Windows messages to game engine member functions
	switch (msg)
	{
	case WM_SETFOCUS:
		// Activate the game and update the Sleep status
		GameActivate(hWindow);
		SetSleep(FALSE);
		return 0;
	case WM_KILLFOCUS:
		// Deactivate the game and update the Sleep status
		GameDeactivate(hWindow);
		SetSleep(TRUE);
		return 0;
	case WM_PAINT:
		HDC         hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hWindow, &ps);

		// Paint the game
		GamePaint(hDC);

		EndPaint(hWindow, &ps);
		return 0;
	case MM_MCINOTIFY:
		if (LOWORD(wParam) == MCI_NOTIFY_SUCCESSFUL)
		{
			if (GetMIDIPlayer() != nullptr)
				GetMIDIPlayer()->Restart(hWindow);
		}
		return 0;
		// Mouse Input Cases
	case WM_LBUTTONDOWN:
		// handle mouse button 
		MouseButtonDown(LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;
	case WM_LBUTTONUP:
		MouseButtonUp(LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;
	case WM_RBUTTONDOWN:
		MouseButtonDown(LOWORD(lParam), HIWORD(lParam), FALSE);
		return 0;
	case WM_RBUTTONUP:
		MouseButtonUp(LOWORD(lParam), HIWORD(lParam), FALSE);
		return 0;
	case WM_MOUSEMOVE:
		MouseMove(LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	return DefWindowProc(hWindow, msg, wParam, lParam);
}

//-----------------------------------------------------------------
// Game Engine Virtual Override Methods
//-----------------------------------------------------------------

void GEN::GameEngine::GameStart(HWND hWindow)
{
	srand(GetTickCount());
}

void GEN::GameEngine::GameActivate(HWND hWindow)
{
	HDC   hDC;
	RECT  rect;
	// Draw activation text on the game screen
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("BOOM_SHACKKA"), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GEN::GameEngine::GameDeactivate(HWND hWindow)
{
	HDC   hDC;
	RECT  rect;

	// Draw deactivation text on the game screen
	GetClientRect(hWindow, &rect);
	hDC = GetDC(hWindow);
	DrawText(hDC, TEXT("SHAZAM."), -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	ReleaseDC(hWindow, hDC);
}

void GEN::GameEngine::GameEnd()
{
}

void GEN::GameEngine::GamePaint(HDC hDC)
{
}

void GEN::GameEngine::GameCycle()
{

	HDC   hDC;
	// Draw the snowflake icon at random positions on the game screen
	hDC = GetDC(m_hWindow);
	int iX = rand() % GetWidth();
	int iY = rand() % GetHeight();
	DrawIcon(hDC, iX, iY,
		(HICON)(WORD)GetClassLong(m_hWindow, GCL_HICON));
	ReleaseDC(m_hWindow, hDC);
}



//------------------------------------------------------------------
// Keyboard and Mouse Functions
//------------------------------------------------------------------
void GEN::GameEngine::HandleKeys() {}

// Mouse input methods
void GEN::GameEngine::MouseButtonDown(int x, int y, BOOL bLeft) {}
void GEN::GameEngine::MouseButtonUp(int x, int y, BOOL bLeft) {}
void GEN::GameEngine::MouseMove(int x, int y) {}

//-----------------------------------------------------------------
// Double buffer animation methods
//-----------------------------------------------------------------

void GEN::GameEngine::BltOffscreenBuffer()
{
	HDC hdc = GetDC(GetWindow());
	// Paint game to offscreen buffer
	GamePaint(m_hOffscreenDC);

	// blit the offscreen bitmap image to the game screen
	BitBlt(hdc, 0, 0, m_iWidth, m_iHeight,
		m_hOffscreenDC, 0, 0, SRCCOPY);

	// cleanup
	ReleaseDC(GetWindow(), hdc);
}

//---------------------------------------------
// Various Function Specification
//---------------------------------------------

/** Function TextOut:
@hDC		The device context handle
@X			X-Coordinate for top-left corner of box
@Y			Y-Coordinate for top-left corner of box
@LPWCSTR	Long-Pointer to unicode C-String
@c			number of characters in space
*/

/** Function MoveToEx:
@hDC		Device context handle
@X			X-Coordinate of pen
@Y			Y-Coordinate of pen
@lpPPoint	previous point in the coordinate
@return		pen is pointed at that point in client window */

/** Function Rectangle:
@hDC		Device context handle
@xLeft		left x coordinate
@yTop		top y coordinate
@xRight		Right x coordinate
@yBottom	Bottom yCoordinate */

/** Function FillRect:
@hDC		Device context handle
@LPRC		long pointer to rect struct
@HBRUSH		brush used to fill the rectangle */

/** Function Ellipse:
@hDC		Device context handle
@rest		Same as rectangle params */

/** Arcs, chords, and pies can be down similarly */

/** Function Polygon:
@hDC		Device context handle
@points		Array of POINT objects
@iCount		sizeOfArray */

/** Function CreatePen:
@iPenStyle	PS_SOLD | PS_BLACK | PS_DOT | PS_DASHDOT | PS_DASHDOTDOT | PS_NULL
@iWidth		pen width in logical units (pixels)
@COLORREF	RGB color of pen
@return		HPEN	*/

/** Function CreateBrush:
@COLORREF	RGB color of brush
@return		HBRUSH */

/** SelectObject:
@hDC		device context handle
@hOBJ		handle to object */
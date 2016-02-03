//-----------------------------------------------------------------
// Game Engine Object
// C++ Source - GameEngine.cpp
//-----------------------------------------------------------------
// Game Wrapper Object
// C++ Header - GameWrapper.h
//-----------------------------------------------------------------

#ifndef _WRAPPER_H
#define _WRAPPER_H

//-----------------------------------------------------------------
// Namespace GEN - Game Engine Namespace
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Windows.h"
#include "GameEngine.h" // the game wrapper encapsulates an engine
#include <memory>
#include "GEN_NameSpace.h"
#include "GameInterface.h"

//-----------------------------------------------------------------
// Forward Declarations
//-----------------------------------------------------------------


LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

//-----------------------------------------------------------------
// Class Declaration
//-----------------------------------------------------------------

class GEN::Wrapper : public GameInterface
{
private:
	//static pointers to the wrapper and game
	//static std::tr1::shared_ptr<GEN::Wrapper> m_pWrapper; // RAII Implementation
	//static std::tr1::shared_ptr<GEN::GameEngine> m_pGame;
	static const int DEFAULT_FRAME_DELAY = 50;

	// WIN32 API Data Members
	//std::tr1::shared_ptr<GEN::Wrapper> m_pWrapper;
	std::tr1::shared_ptr<GEN::GameEngine> m_pGame;
	HINSTANCE           m_hInstance;
	WNDPROC				m_lpfnWndProc;
	HWND                m_hWindow;
	WORD	            m_wIcon, m_wSmallIcon;
	int                 m_iWidth, m_iHeight;
	int                 m_iFrameDelay;
	TCHAR               m_szWindowClass[32];
	TCHAR               m_szTitle[32];

public:
	// Constructor(s) / Destructor
	Wrapper(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPTSTR szWindowClass, LPTSTR szTitle,
		WORD wIcon, WORD wSmallIcon, int iWidth = 640, int iHeight = 480);
	virtual ~Wrapper();
	LRESULT HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);
	BOOL	InitializeWindow(int iCmdShow);

	// WIN API Accessor/ Mutator Methods
	HINSTANCE GetInstance() const { return m_hInstance; };
	HWND      GetWindow() const { return m_hWindow; };
	void      SetWindow(HWND hWindow) { m_hWindow = hWindow; };

	LPTSTR    GetTitle() { return m_szTitle; };
	WORD      GetIcon() const { return m_wIcon; };
	WORD      GetSmallIcon() const { return m_wSmallIcon; };
	int       GetWidth() const { return m_iWidth; };
	int       GetHeight() const { return m_iHeight; };
	int       GetFrameDelay() const { return m_iFrameDelay; };
	void      SetFrameRate(int iFrameRate) {
		m_iFrameDelay = 1000 /
			iFrameRate;
	};

	// Game Engine initialization methods
	void	  SetEngineWindowSpecs();
	void	  SetOffscreenDC();
	// Static member accessors
	//static std::tr1::shared_ptr<GEN::GameEngine>& GetEngine() { return m_pGame; };
	//static std::tr1::shared_ptr<GEN::Wrapper>& GetWrapper() { return m_pWrapper; };
	//static void SetEngine(std::tr1::shared_ptr<GEN::GameEngine> pNewEngine) {
	//m_pGame = pNewEngine;
	//}
	std::tr1::shared_ptr<GEN::GameEngine> GetEngine() { return m_pGame; };
	void SetEngine(std::tr1::shared_ptr<GEN::GameEngine> pEngine)
	{
		m_pGame = pEngine;
	};

	// TO-DO: Override the following virtual functions 
	// for game-specific wrappers

	virtual BOOL GameInitialize(HINSTANCE hInstance);
};

#endif

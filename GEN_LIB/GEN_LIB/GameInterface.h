//----------------------------------------------------------------
// C++ Object - GameInterface
// C++ Header File - GameInterface.h
//----------------------------------------------------------------


#ifndef _GAME_INTERFACE_H
#define _GAME_INTERFACE_H


//----------------------------------------------------------------
// Include Files
//----------------------------------------------------------------

#include "Windows.h"
#include "GameEngine.h"
#include <memory>

//----------------------------------------------------------------
// Class Declaration
//----------------------------------------------------------------

class GameInterface
{

public:
	// Interface function for creating wrapper to games in static library
	//static std::tr1::shared_ptr<GameInterface> Create_Wrapper(HINSTANCE hInstance, 
	//	WNDPROC lpfnWndProc, LPTSTR szWindowClass, LPTSTR szTitle,
	//	WORD wIcon, WORD wSmallIcon, int iWidth = 640, int iHeight = 480, UINT uiGameID = IDG_BLIZZARD);
	virtual ~GameInterface();
	virtual LRESULT HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
	virtual BOOL	InitializeWindow(int iCmdShow) = 0;

	// WIN API Accessor/ Mutator Methods
	virtual HINSTANCE GetInstance() const = 0;
	virtual HWND      GetWindow() const = 0;
	virtual void      SetWindow(HWND hWindow) = 0;

	virtual LPTSTR    GetTitle() = 0;
	virtual WORD      GetIcon() const = 0;
	virtual WORD      GetSmallIcon() const = 0;
	virtual int       GetWidth() const = 0;
	virtual int       GetHeight() const = 0;
	virtual int       GetFrameDelay() const = 0;
	virtual void      SetFrameRate(int iFrameRate) = 0;

	// Game Engine initialization methods
	virtual void SetEngineWindowSpecs() = 0;
	virtual std::tr1::shared_ptr<GEN::GameEngine> GetEngine() = 0;
	virtual void SetEngine(std::tr1::shared_ptr<GEN::GameEngine> pEngine) = 0;

	// TO-DO: Override the following virtual functions 
	// for game-specific wrappers

	virtual BOOL GameInitialize(HINSTANCE hInstance) = 0;
};




#endif


//-----------------------------------------------------------------
// Game Engine Object
// C++ Header - GameEngine.h
//-----------------------------------------------------------------

#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

//-----------------------------------------------------------------
// Namespace GEN - Game Engine Namespace
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "Windows.h"
#include <memory>
#include "GEN_NameSpace.h"
#include "MIDIPlayer.h"
#include "SpriteManager.h"

//-----------------------------------------------------------------
// Windows Function forward Declarations
//-----------------------------------------------------------------

//LRESULT CALLBACK WndProc(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

//-----------------------------------------------------------------
// Game Engine Function Declarations
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// GameEngine Class
//-----------------------------------------------------------------

/**
 * This class defines the GameEngine in the GEN (Game Engine namespace)
 * It is the main class responsible for the management of all aspects 
 * associated with the game.
 */
class GEN::GameEngine
{
private:
	BOOL m_bSleep;
	HWND m_hWindow;
	HINSTANCE m_hInstance;
	int m_iWidth, m_iHeight;
	//WORD m_wIcon, m_wSmallIcon;

	// offscreen device context (reduces flicker in frame animation)
	HDC		m_hOffscreenDC;
	HBITMAP	m_hOffscreenBitmap;

	// MIDIPlayer
	std::tr1::shared_ptr<MIDIPlayer> m_mpMIDIPlayer;
public:
	// Constructor(s)/Destructor

	/**
	 * Default constructor.
	 */
	GameEngine();
	virtual ~GameEngine();
	// General Methods

	/**
	 * The primary event handler for the window.  It returns a signed result
	 * of message processing and assists the wndProc function generated by the user
	 * in any driver files.
	 * @param hWindow handle to the window associated with this procedure
	 * @param the message from the message queue
	 * @param wParam the 32-bit value associated with the message.
	 * @param lParam the 32-bit value associated with the message.
	 */
	LRESULT HandleEvent(HWND hWindow, UINT msg, WPARAM wParam, LPARAM lParam);

	/**
	 * Getter function for the sleep flag. 
	 * @return true if the engine is sleeping.  False otherwise 
	 */
	BOOL      GetSleep() { return m_bSleep; };

	/**
	 * Setter function for the sleep flag 
	 * @param bSleep the sleep flag.
	 */
	void      SetSleep(BOOL bSleep) { m_bSleep = bSleep; };
	
	/**
	 * Setter function for the window flag.
	 * @param hWindow the handle to the window associated with this engine.
	 */
	void	  SetWindow(HWND hWindow) { m_hWindow = hWindow; };

	/**
	 * Getter function for the height
	 * @return the height of the window.
	 */
	int		  GetHeight() const { return m_iHeight; };

	/**
	 * Setter function for the height of the window.
	 * @param iHeight the height of the window
	 */
	void	  SetHeight(int iHeight) { m_iHeight = iHeight; };

	/**
	 * Getter function for the width of the window.
	 * @return the width of the window.
	 */
	int		  GetWidth() const { return m_iWidth; };

	/**
	 * Setter function for the width of the window.
	 * @return the width of the window.
	 */
	void	  SetWidth(int iWidth) { m_iWidth = iWidth; };

	/**
	 * Getter function for the window
	 * @return a handle to the window. 
	 */
	HWND	  GetWindow() { return m_hWindow; };

	/**
	 * Getter function for the instance.
	 * @return the instance.
	 */
	HINSTANCE GetInstance() { return m_hInstance; };

	/**
	 * Setter function for the instance
	 * @param hInstance handle to the instance
	 */
	void	  SetInstance(HINSTANCE hInstance) { m_hInstance = hInstance; };
	//void	  InitializeScreenBuffer();
	/*void	  SetIcon(WORD wIcon) { m_wIcon = wIcon; };
	void	  SetSmallIcon(WORD wIcon) { m_wSmallIcon = wIcon; };
	WORD	  GetIcon(WORD wIcon) { return m_wIcon; };
	WORD	  GetSmallIcon(WORD wIcon) { return m_wSmallIcon; };*/

	
	/**
	 * Setter function for the offscreen device context 
	 * @param hOffscreenDC the offscreen device context
	 */
	void	  SetOffScreenDC(HDC hOffscreenDC) {
		m_hOffscreenDC = hOffscreenDC;
	};

	/**
	 * Setter for the offscreen bitmap
	 * @param hOffscreenBitmap handle to the bitmap
	 */
	void	  SetOffscreenBitmap(HBITMAP hOffscreenBitmap) {
		m_hOffscreenBitmap = hOffscreenBitmap;
	};

	/**
	 * "Blits" the offscren buffer to the screen to reduce flickering. 
	 */
	void	  BltOffscreenBuffer();

	/**
	 * Getter method for the MIDI player
	 * @return a pointer to the midi-player (protected pointer)
	 */
	std::tr1::shared_ptr<MIDIPlayer> GetMIDIPlayer() { return m_mpMIDIPlayer; };

	// Virtual Game Engine Functions 
	// TO DO: Override these functions with game-specific code

	/**
	 * Method that initializes all the game data. 
	 */
	virtual void GameStart(HWND hWindow);

	/**
	 * Ends the game
	 */
	virtual void GameEnd();

	/**
	 * Activates the game; this method is called when the game window gains focus.
	 */
	virtual void GameActivate(HWND hWindow);

	/**
	 * Deactivates the game.  This method is called when the game window loses focus.
	 */
	virtual void GameDeactivate(HWND hWindow);

	/**
	 * Paints the game (used for graphics rendering).
	 * @param hDC the handle to the device context.
	 */
	virtual void GamePaint(HDC hDC);

	/**
	 * Cycles the game, updating graphics contexts and data as needed
	 */
	virtual void GameCycle();

	/**
	 * Handles all keyboard and mouse functions necessary for the game
	 */
	virtual void HandleKeys();

	/**
	 * Responds to mouse button down event.
	 * @param x the x-coordinate on the client rectangle where mouse was clicked 
	 * @param y the y-coordinate on the client rectangle where the mouse was clicked
	 */
	virtual void MouseButtonDown(int x, int y, BOOL bLeft);

	/**
	 * Responds to the mouse button up event.
	 * @param x the x-coordinate on the client rectangle where mouse was released.
	 * @param y the y-coordinate on the client rectangle where the mouse was released.
	 */
	virtual void MouseButtonUp(int x, int y, BOOL bLeft);

	/**
	 * Responds to the mouse movement
	 * @param x the current x-coordiante of the mouse during movement.
	 * @param y the current y-coordiante of the mouse during movement.
	 */
	virtual void MouseMove(int x, int y);
};

#endif
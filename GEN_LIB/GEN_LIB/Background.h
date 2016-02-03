//-----------------------------------------------------------------
// Background Object
// C++ Header - Background.h
//-----------------------------------------------------------------

#ifndef _BACKGROUND_H
#define _BACKGROUND_H

//-----------------------------------------------------------------
// Namespace GEN - Game Engine Namespace
//-----------------------------------------------------------------

namespace GEN { class Background; }


//-----------------------------------------------------------
// Include Files
//-----------------------------------------------------------

#include "Windows.h"
#include "Bitmap.h"
#include <memory>

//-----------------------------------------------------------
// Background Class Declaration
//-----------------------------------------------------------

/**
 * This class provides the base class for all background associated with the gameContext.  
 * It provides default implementations for drawing single-color bitmaps 
 */
class GEN::Background
{
protected:
	// Member variables
	typedef std::tr1::shared_ptr<Bitmap> BitmapPtr;
	int			m_iWidth, m_iHeight;
	COLORREF	m_crColor;
	BitmapPtr		m_pBitmap;
public:
	// Constructor(s)/Destructor
	Background();
	/**
	 * Constructor.
	 * @param iWidth the width of the background
	 * @param iHeight the height of the background
	 * @param color the color of the background
	 */
	Background(int iWidth, int iHeight, COLORREF color);

	/**
	 * Constructor for a background composed of a bitmap. 
	 * @param pBitmap the pointer to a bitmap
	 */
	Background(BitmapPtr pBitmap);
	virtual ~Background();

	// General Methods
	/**
	 * Updates the background.  Implementing classes should override for
	 * customizability
	 */
	virtual void Update();

	/**
	 * Draws the background given a handle to a device context.  Implementing
	 * classes should override for customizability. 
	 * @param hDC the handle to the device context
	 */
	virtual void Draw(HDC hDC);

	// accessor methods

	/**
	 * Getter method for the width of the background.
	 * @return the width of the background 
	 */
	int GetWidth() const { return m_iWidth; };

	/**
	 * Getter method for the height of the background.
	 * @return the height of the background
	 */
	int GetHeight() const { return m_iHeight; };
}; // end class definition

#endif


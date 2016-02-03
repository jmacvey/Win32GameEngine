#ifndef _BITMAP_H
#define _BITMAP_H

//---------------------------------------------------------
// Include Files
//---------------------------------------------------------

#include "Windows.h"

//---------------------------------------------------------
// BitMap Class Declaration
//---------------------------------------------------------

/**
 * This class provides the template for an object meant to wrap around
 * a bitmap file.  This ultimately lends to animation capabilities
 * for all sprites in 2-D animation 
 */
class Bitmap
{
private:
	/* Class stores its own handle. */
	HBITMAP m_hBitmap;

	/* Height and Width specifications*/
	int m_iWidth, m_iHeight;

	/**
	 * Frees any memory associated with this bitmap
	 */
	void free();
public:
	// Constructor(s)/Destructor

	/**
	 * Default Constructor 
	 */
	Bitmap();

	/**
	 * Constructor that constructs the bitmap based on a resource ID 
	 * @param uiResID the resource ID associated with the bitmap.
	 * It should be documented in the resouce folder of this project.
	 */
	Bitmap(UINT uiResID);

	/**
	 * Constructor for the bitmap from a file.
	 * @param hDC the handle to the device context for the bitmap 
	 * @param szFileName path to the file.
	 */
	Bitmap(HDC hDC, LPTSTR szFileName);

	/**
	 * Alternate constructor for the bitmap from a resource ID when 
	 * the instance must be provided for proper rendering.
	 * @param uiResID the resource iD
	 * @param hInstance the handle to the instance of this application.
	 */
	Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance);

	/**
	 * Alternate constructor for a plain color bitmap 
	 * @param hDC the handle to the device context.
	 * @param iWidth the width of the bitmap
	 * @param iHeight the height of the bitmap
	 * @param crColor the color of the bitmap
	 */
	Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor = RGB(0, 0, 0));
	virtual ~Bitmap();

	//General Methods

	/**
	 * Creates a bitmap object from a file name
	 * @param hDC the handle to the device context
	 * @param szFileName the path to the file
	 * @return true if the bitmap is successfully created. False otherwise
	 */
	BOOL create(HDC hDC, LPTSTR szFileName);


	/**
	 * Creates a bitmap object from a resolution ID
	 * @param hDC the handle to the device context
	 * @param uiResID the resource ID associated with the bitmap
	 * @param hInstance the instance associated with this bitmap.
	 * @return true if the bitmap is successfully created. False otherwise
	 */
	BOOL create(HDC hDC, UINT uiResID, HINSTANCE hInstance);

	/**
	 * Creates a bitmap object from a resolution ID
	 * @param hDC the handle to the device context
	 * @param iWidth the width of the bitmap
	 * @param iHeight the height of the bitmap
	 * @param crColor the color of the bitmap
	 * @return true if the bitmap is successfully created. False otherwise
	 */
	BOOL create(HDC hDC, int iWidth, int iHeight, COLORREF crColor);


	/**
	 * Draws the entire bitmap to the window designated by a device context.
	 * @param hDC the handle to the device context
	 * @param x the coordinate on the view corresponding to 
	 *    upper left-hand x-coordinate of the bitmap
	 * @param y the coordinate on the view corresponding to
	 *    upper left-hand y-coordinate of the bitmap
	 * @param bTrans whether or not to make this bitmap transparent
	 * @param crTransColor the color to make transparent (magenta)
	 */
	void Draw(HDC hDC, int x, int y, BOOL bTrans = FALSE,
		COLORREF crTransColor = RGB(255, 0, 255)) const;

	/**
	 * Draws only a part of the bitmap to the window designated by a device context.
	 * @param hDC the handle to the device context
	 * @param x the coordinate on the view corresponding to
	 *    upper left-hand x-coordinate of the bitmap
	 * @param y the coordinate on the view corresponding to
	 *    upper left-hand y-coordinate of the bitmap
	 * @param xPart the x-coordinate to draw to
	 * @param yPart the y-coordinate to draw to
	 * @param wPart the width of the destination and source rectangle
	 * @param hPart the height of the destination and source rectangle
	 * @param bTrans whether or not to make this bitmap transparent
	 * @param crTransColor the color to make transparent (magenta)
	 */
	void DrawPart(HDC hDC, int x, int y, int xPart, int yPart, int wPart, int hPart,
		BOOL bTrans, COLORREF crTransColor = RGB(255, 0, 255)) const;

	/**
	 * Getter function for the width of the bitmap.
	 * @return the width of the bitmap
	 */
	int GetWidth() const { return m_iWidth; };
	
   /**
	* Getter function for the height of the bitmap.
	* @return the height of the bitmap
	*/
	int GetHeight() const { return m_iHeight; };
}; // end BitMap

#endif

// Bitmap object 
// C++ Source - Bitmap.cpp

//---------------------------------------------------------
// Include Files
//---------------------------------------------------------

#include "Bitmap.h"

//---------------------------------------------------------
// Constructor(s)/Destructor
//---------------------------------------------------------

Bitmap::Bitmap() : // initialization list
	m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{}

// Create a Bitmap from a file
Bitmap::Bitmap(HDC hDC, LPTSTR szFileName) :
	m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Bitmap::create(hDC, szFileName);
}

// Create a Bitmap from a resource
Bitmap::Bitmap(HDC hDC, UINT uiResID, HINSTANCE hInstance)
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Bitmap::create(hDC, uiResID, hInstance);
}

//Create a blank Bitmap from scratch
Bitmap::Bitmap(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
	: m_hBitmap(NULL), m_iWidth(0), m_iHeight(0)
{
	Bitmap::create(hDC, iWidth, iHeight, crColor);
}

Bitmap::Bitmap(UINT uiResID)
{
	m_hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(uiResID));
	BITMAP bm;
	GetObject(m_hBitmap, sizeof(BITMAP), &bm);
	m_iHeight = bm.bmHeight;
	m_iWidth = bm.bmWidth;
}

Bitmap::~Bitmap()
{
	free();
}

//---------------------------------------------------------
// Bitmap Helper methods
//---------------------------------------------------------

void Bitmap::free()
{
	//Delete the Bitmap graphics object
	if (m_hBitmap != NULL)
	{
		DeleteObject(m_hBitmap);
		m_hBitmap = NULL;
	}
}

//---------------------------------------------------------
// Bitmap General Methods
//---------------------------------------------------------

BOOL Bitmap::create(HDC hDC, LPTSTR szFileName)
{
	// Free any previous Bitmap info
	free();

	// open the Bitmap file
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ,
		FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	// ensure valid handle value
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	// create a Bitmap file header
	BITMAPFILEHEADER	bmfHeader;
	DWORD				dwBytesRead;
	// read the fileHeader into the bmfHeader;
	BOOL bOK = ReadFile(hFile, &bmfHeader, sizeof(BITMAPFILEHEADER),
		&dwBytesRead, NULL);
	// ensure the header was read in correctly
	if ((!bOK) || (dwBytesRead != sizeof(BITMAPFILEHEADER)) ||
		(bmfHeader.bfType != 0x4D42)) // 0x4D42 = BM 
	{
		CloseHandle(hFile);
		return FALSE;
	}
	// create a Bitmap info buffer
	BITMAPINFO* pBitmapInfo = (new BITMAPINFO);
	if (pBitmapInfo != NULL)
	{
		// read the Bitmap info header
		bOK = ReadFile(hFile, pBitmapInfo, sizeof(BITMAPINFOHEADER),
			&dwBytesRead, NULL);
		// ensure read success
		if ((!bOK) || (dwBytesRead != sizeof(BITMAPINFOHEADER)))
		{
			CloseHandle(hFile);
			free();
			return FALSE;
		}

		// Store the width and height of the btimap
		m_iWidth = (int)pBitmapInfo->bmiHeader.biWidth;
		m_iHeight = (int)pBitmapInfo->bmiHeader.biHeight;

		// get handle to the Bitmap and copy image bits
		PBYTE pBitmapBits;
		m_hBitmap = CreateDIBSection(hDC, pBitmapInfo,
			DIB_RGB_COLORS,
			(PVOID*)&pBitmapBits, NULL, 0);
		if ((m_hBitmap != NULL) && (pBitmapBits != NULL))
		{
			// point the file header to  
			SetFilePointer(hFile, bmfHeader.bfOffBits, NULL,
				FILE_BEGIN);
			// copy image bits to pBitmapBits
			bOK = ReadFile(hFile, pBitmapBits, pBitmapInfo->bmiHeader.biSizeImage,
				&dwBytesRead, NULL);
			if (bOK)
				return TRUE;
		}
	}
	// something went wrong, so cleanup
	free();
	return FALSE;
}

BOOL Bitmap::create(HDC hDC, UINT uiResID, HINSTANCE hInstance)
{
	// free any previous DIB info
	free();

	// find Bitmap resources
	HRSRC hResInfo = FindResource(hInstance, MAKEINTRESOURCE(uiResID), RT_BITMAP);
	if (hResInfo == NULL)
		return FALSE;

	// load the Bitmap resource
	HGLOBAL hMemBitmap = LoadResource(hInstance, hResInfo);
	if (hMemBitmap == NULL)
		return FALSE;

	// lock the resource and access entire Bitmap image
	PBYTE pBitmapImage = (BYTE*)LockResource(hMemBitmap);
	if (pBitmapImage == NULL)
	{
		FreeResource(hMemBitmap);
		return FALSE;
	}

	// store the width and height of the Bitmap
	BITMAPINFO* pBitmapInfo = (BITMAPINFO*)pBitmapImage;
	m_iHeight = pBitmapInfo->bmiHeader.biHeight;
	m_iWidth = pBitmapInfo->bmiHeader.biWidth;

	//get a handle to the Bitmap and copy image bits
	PBYTE pBitmapBits;
	m_hBitmap = CreateDIBSection(hDC, pBitmapInfo, DIB_RGB_COLORS,
		(PVOID*)&pBitmapBits, NULL, 0);
	if ((m_hBitmap != NULL) && (pBitmapBits != NULL))
	{
		const PBYTE pTempBits = pBitmapImage + pBitmapInfo->bmiHeader.biSize +
			pBitmapInfo->bmiHeader.biClrUsed * sizeof(RGBQUAD);
		CopyMemory(pBitmapBits, pTempBits, pBitmapInfo->bmiHeader.biSizeImage);

		// unlock and free Bitmap graphics object
		UnlockResource(hMemBitmap);
		FreeResource(hMemBitmap);
		return TRUE;
	}
	// something went wrong, so cleanup
	UnlockResource(hMemBitmap);
	FreeResource(hMemBitmap);
	return FALSE;
}

BOOL Bitmap::create(HDC hDC, int iWidth, int iHeight, COLORREF crColor)
{
	// create a blank Bitmap
	m_hBitmap = CreateCompatibleBitmap(hDC, iWidth, iHeight);
	if (m_hBitmap == NULL)
	{
		return FALSE;
	}

	// set the width and height
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	// create a emory device context to draw on the Bitmap
	HDC hMemDC = CreateCompatibleDC(hDC);

	// create a solid brush to fill the Bitmap
	HBRUSH hBrush = CreateSolidBrush(crColor);

	// select the Bitmap into the device context
	HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

	// Fill the Bitmap with a solid color
	RECT rcBitmap = { 0, 0, m_iWidth, m_iHeight };
	FillRect(hMemDC, &rcBitmap, hBrush);

	//cleanup
	SelectObject(hMemDC, hOldBitmap);
	DeleteDC(hMemDC);
	DeleteObject(hBrush);
	return TRUE;
}

void Bitmap::Draw(HDC hDC, int x, int y, BOOL bTrans, COLORREF crTransColor) const
{
	DrawPart(hDC, x, y, 0, 0,
		GetWidth(), GetHeight(), bTrans, crTransColor);
}

void Bitmap::DrawPart(HDC hDC, int x, int y, int xPart, int yPart,
	int wPart, int hPart, BOOL bTrans, COLORREF crTransColor) const
{
	if (m_hBitmap != NULL)
	{
		// Create a memory device context for the bitmap
		HDC hMemDC = CreateCompatibleDC(hDC);

		// Select the bitmap into the device context
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemDC, m_hBitmap);

		// Draw the bitmap to the destination device context
		if (bTrans)
			TransparentBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart,
				wPart, hPart, crTransColor);
		else
			BitBlt(hDC, x, y, wPart, hPart, hMemDC, xPart, yPart, SRCCOPY);

		// Restore and delete the memory device context
		SelectObject(hMemDC, hOldBitmap);
		DeleteDC(hMemDC);
	}
}
//---------------------------------------------------------
// Function Definitions
//---------------------------------------------------------


/** Function ReadFile:
@hFile					handle to a file
@lpBuffer				long pointer to a buffer that recieves data from file
@nNumberOfBytesToread	number of bytes to be read
@lpNumberOfBytesREad	pointer to variable that receives number of bytes read
@lpOverlapped			pointer to overlapped structure (or NULL)
*/

/** Function CreateDIBSecton:
@HDC					handle to device context
@BitmapINFO				pointer to a Bitmap info
@UINT					type of data contained in the bmiColors array of structure pointed to by pbmi
@**ppvBits				pointer to variable that receives a pointer to location of DIB bit values
@hSection				handle to file-mapping object or NULL
@dwOffset				offset from beginning of file-mpping object referenced by hsection
@return:				handle to newly created DIB, and *ppvBits points to Bitmap bit values
*/

/** Function SetFilePointer:
@hFile					handle to the file
@lDistanceToMove		the low order 32-bits of a singed value that specified the no. bytes to move the file pointer
@lpDistanceTOMoveHigh	the high order 32-bits of signed 64-bit distance to move
@dwMoveMethod			starting point for the file poiner to move
@return					the return value is low-order DWORD of the new file pointer
*/
//-----------------------------------------------------------
// C++ Source File - Background.cpp
//-----------------------------------------------------------

//-----------------------------------------------------------
// Include Files
//-----------------------------------------------------------

#include "Background.h"

//-----------------------------------------------------------
// Constructor(s) / Destructor Definitions
//-----------------------------------------------------------

GEN::Background::Background() :
	m_iWidth(0), m_iHeight(0),
	m_crColor(0), m_pBitmap(NULL)
{
}

GEN::Background::Background(int iWidth, int iHeight, COLORREF crColor) :
	m_iWidth(iWidth), m_iHeight(iHeight),
	m_crColor(crColor), m_pBitmap(NULL)
{
}

GEN::Background::Background(BitmapPtr pBitmap) :
	m_iWidth(0), m_iHeight(0),
	m_crColor(0), m_pBitmap(pBitmap)
{
	// set width and height
	m_iWidth = m_pBitmap->GetWidth();
	m_iHeight = m_pBitmap->GetHeight();
}



GEN::Background::~Background() {
}

//-----------------------------------------------------------
// General Methods Definitions
//-----------------------------------------------------------

void GEN::Background::Update()
{
	// Do nothing
}

void GEN::Background::Draw(HDC hDC)
{
	if (m_pBitmap != NULL)
	{
		m_pBitmap->Draw(hDC, 0, 0);
	}
	else
	{
		RECT	rect = { 0, 0, m_iHeight, m_iWidth };
		HBRUSH	hBrush = CreateSolidBrush(m_crColor);
		FillRect(hDC, &rect, hBrush);
		DeleteObject(hBrush);
	}
}

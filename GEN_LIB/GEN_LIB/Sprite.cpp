//------------------------------------------------------------
// Sprite.cpp - C++ Source File
//------------------------------------------------------------

//------------------------------------------------------------
// Include Files
//------------------------------------------------------------

#include "Sprite.h"

//------------------------------------------------------------
// Constructor(s) / Destructor Section
//------------------------------------------------------------

GEN::Sprite::Sprite(std::tr1::shared_ptr<Bitmap> pBitmap)
{
	//initialize member variables
	m_pBitmap = pBitmap;
	SetRect(&m_rcPosition, 0, 0, pBitmap->GetWidth(), pBitmap->GetHeight());
	m_ptVelocity.x = m_ptVelocity.y = 0;
	m_iZOrder = 0;
	SetRect(&m_rcBounds, 0, 0, 640, 480);
	m_baBoundsAction = BA_STOP;
	m_bHidden = FALSE;
	CalcCollisionRect();
	m_iNumFrames = 1;
	m_iCurFrame = 0;
	m_iFrameDelay = 0;
	m_iFrameTrigger = 0;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
}

GEN::Sprite::Sprite(std::tr1::shared_ptr<Bitmap> pBitmap, const RECT& rcBounds, BOUNDSACTION baBoundsAction)
{

	m_pBitmap = pBitmap;
	//Calculate a random position
	int iXPos = rand() % (rcBounds.right - rcBounds.left);
	int iYPos = rand() % (rcBounds.bottom - rcBounds.top);

	//initialize member variables
	SetRect(&m_rcPosition, iXPos, iYPos, iXPos + m_pBitmap->GetWidth(),
		iYPos + m_pBitmap->GetHeight());
	m_ptVelocity.x = m_ptVelocity.y = 0;
	m_iZOrder = 0;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_bHidden = FALSE;
	CalcCollisionRect();
	m_iNumFrames = 1;
	m_iCurFrame = 0;
	m_iFrameDelay = 0;
	m_iFrameTrigger = 0;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
}

GEN::Sprite::Sprite(std::tr1::shared_ptr<Bitmap> pBitmap, const POINT& ptPosition, const POINT& ptVelocity, int iZOrder,
	const RECT& rcBounds, BOUNDSACTION baBoundsAction)
{
	m_pBitmap = pBitmap;

	// set position rect
	SetRect(&m_rcPosition, ptPosition.x, ptPosition.y,
		ptPosition.x + pBitmap->GetWidth(), ptPosition.y + pBitmap->GetHeight());
	// velocity
	m_ptVelocity.x = ptVelocity.x;
	m_ptVelocity.y = ptVelocity.y;
	m_iZOrder = iZOrder;
	CopyRect(&m_rcBounds, &rcBounds);
	m_baBoundsAction = baBoundsAction;
	m_bHidden = FALSE;
	CalcCollisionRect();
	m_iNumFrames = 1;
	m_iCurFrame = 0;
	m_iFrameDelay = 0;
	m_iFrameTrigger = 0;
	m_bDying = FALSE;
	m_bOneCycle = FALSE;
}



GEN::Sprite::~Sprite()
{}

SPRITEACTION GEN::Sprite::Update()
{

	// see if sprite needs to die
	if (m_bDying)
		return SA_KILL;
	// Update frame if necessary
	UpdateFrame();
	//Update position
	POINT ptNewPos, ptSpriteSize, ptBoundsSize;
	ptNewPos.x = m_rcPosition.left + m_ptVelocity.x;
	ptNewPos.y = m_rcPosition.top + m_ptVelocity.y;
	ptSpriteSize.x = m_rcPosition.right - m_rcPosition.left;
	ptSpriteSize.y = m_rcPosition.bottom - m_rcPosition.top;
	ptBoundsSize.x = m_rcBounds.right - m_rcBounds.left;
	ptBoundsSize.y = m_rcBounds.bottom - m_rcBounds.top;

	//check the bounds
	switch (m_baBoundsAction)
	{
	case BA_WRAP:
	{
		if ((ptNewPos.x + ptSpriteSize.x) < m_rcBounds.left)
		{
			ptNewPos.x = m_rcBounds.right;
		}
		else if ((ptNewPos.x > m_rcBounds.right))
		{
			ptNewPos.x = m_rcBounds.left - ptSpriteSize.x;
		}
		if ((ptNewPos.y + ptSpriteSize.y) < m_rcBounds.top)
		{
			ptNewPos.y = m_rcBounds.bottom;
		}
		else if ((ptNewPos.y) > m_rcBounds.bottom)
		{
			ptNewPos.y = m_rcBounds.top - ptSpriteSize.y;
		}
	}
	break;
	case BA_BOUNCE:
	{
		BOOL bBounce = FALSE;
		POINT ptNewVelocity = m_ptVelocity;
		if (ptNewPos.x <= m_rcBounds.left)
		{
			bBounce = TRUE;
			ptNewPos.x = m_rcBounds.left;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		else if ((ptNewPos.x + ptSpriteSize.x) >= m_rcBounds.right)
		{
			bBounce = TRUE;
			ptNewPos.x = m_rcBounds.right - ptSpriteSize.x;
			ptNewVelocity.x = -ptNewVelocity.x;
		}
		if (ptNewPos.y <= m_rcBounds.top)
		{
			bBounce = TRUE;
			ptNewPos.y = m_rcBounds.top;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		else if ((ptNewPos.y + ptSpriteSize.y) >= m_rcBounds.bottom)
		{
			bBounce = TRUE;
			ptNewPos.y = m_rcBounds.bottom - ptSpriteSize.y;
			ptNewVelocity.y = -ptNewVelocity.y;
		}
		if (bBounce)
		{
			SetVelocity(ptNewVelocity);
		}
	}
	break;
	case BA_DIE:
	{
		if ((ptNewPos.x + ptSpriteSize.x) < m_rcBounds.left ||
			ptNewPos.x > m_rcBounds.right ||
			(ptNewPos.y + ptSpriteSize.y) < m_rcBounds.top ||
			ptNewPos.y > m_rcBounds.bottom)
			return SA_KILL;
	}
	break;
	//default stop
	default:
	{
		SetVelocity(0, 0);
		if (ptNewPos.x < m_rcBounds.left ||
			ptNewPos.x + ptSpriteSize.x > m_rcBounds.right)
		{
			ptNewPos.x = max(m_rcBounds.left,
				min(ptNewPos.x, m_rcBounds.right - ptSpriteSize.x));
		}
		if (ptNewPos.y < m_rcBounds.top ||
			ptNewPos.y + ptSpriteSize.y > m_rcBounds.bottom)
		{
			ptNewPos.y = max(m_rcBounds.top,
				min(ptNewPos.y, m_rcBounds.bottom - ptSpriteSize.y));
		}
	}
	}
	// end switch 
	SetPosition(ptNewPos);
	return SA_NONE;
}

void GEN::Sprite::Draw(HDC hDC)
{
	// Draw the sprite if it isn't hidden
	if (m_pBitmap != NULL && !m_bHidden)
	{
		// Draw the appropriate frame, if necessary
		if (m_iNumFrames == 1)
			m_pBitmap->Draw(hDC, m_rcPosition.left, m_rcPosition.top, TRUE);
		else
			m_pBitmap->DrawPart(hDC, m_rcPosition.left, m_rcPosition.top,
				0, m_iCurFrame * GetHeight(), GetWidth(), GetHeight(), TRUE);
	}
}


void GEN::Sprite::CalcCollisionRect()
{
	int iXShrink = (m_rcPosition.left - m_rcPosition.right) / 12;
	int iYShrink = (m_rcPosition.top - m_rcPosition.bottom) / 12;
	CopyRect(&m_rcCollision, &m_rcPosition);
	InflateRect(&m_rcCollision, iXShrink, iYShrink);
}

BOOL GEN::Sprite::TestCollision(SpritePtr pTestSprite)
{
	RECT rcTest = pTestSprite->GetCollision();
	POINT	 rcSize;
	rcSize.x = pTestSprite->GetWidth();
	rcSize.y = pTestSprite->GetHeight();
	if (IsOffScreen(rcTest, rcSize))
	{
		// don't want offscreen objects to collide
		return FALSE;
	}
	else
	{
		return ((m_rcCollision.left <= rcTest.right) &&
			(rcTest.left <= m_rcCollision.right) &&
			(m_rcCollision.top <= rcTest.bottom) &&
			(rcTest.top <= m_rcCollision.bottom));
	}
}

BOOL GEN::Sprite::IsOffScreen(const RECT& rcPosition, const POINT& ptSize) const {
	// Tests whether sprite is off the map
	return ((rcPosition.left + ptSize.x <= m_rcBounds.left) ||
		(rcPosition.left >= m_rcBounds.right) ||
		(rcPosition.top + ptSize.y <= m_rcBounds.top) ||
		(rcPosition.top >= m_rcBounds.right));
}
//------------------------------------------------------------
//Accessor Methods
//------------------------------------------------------------

//Position Methods

void GEN::Sprite::SetPosition(const POINT& ptPosition)
{
	OffsetRect(&m_rcPosition, ptPosition.x - m_rcPosition.left,
		ptPosition.y - m_rcPosition.top);
	CalcCollisionRect();
}

void GEN::Sprite::SetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x - m_rcPosition.left,
		y - m_rcPosition.top);
	CalcCollisionRect();
}

void GEN::Sprite::SetPosition(const RECT& rcPosition)
{
	CopyRect(&m_rcPosition, &rcPosition);
	CalcCollisionRect();
}

void GEN::Sprite::OffsetPosition(int x, int y)
{
	OffsetRect(&m_rcPosition, x, y);
	CalcCollisionRect();
}


//Velocity methods

void GEN::Sprite::SetVelocity(int x, int y)
{
	m_ptVelocity.x = x;
	m_ptVelocity.y = y;
}

void GEN::Sprite::SetVelocity(const POINT& ptVelocity) {
	m_ptVelocity.x = ptVelocity.x;
	m_ptVelocity.y = ptVelocity.y;
}

BOOL GEN::Sprite::IsPointInside(int x, int y)
{
	POINT ptPoint;
	ptPoint.x = x;
	ptPoint.y = y;
	return PtInRect(&m_rcPosition, ptPoint);
}

void GEN::Sprite::SetNumFrames(int iNumFrames, BOOL bOneCycle)
{
	// set the one cycle member
	m_bOneCycle = bOneCycle;
	// Set the number of frames
	m_iNumFrames = iNumFrames;
	// Recalculate the position
	RECT rect = GetPosition();
	rect.bottom = rect.top + ((rect.bottom - rect.top) / iNumFrames);
	SetPosition(rect);
}

void GEN::Sprite::UpdateFrame()
{
	if ((m_iFrameDelay >= 0) && (--m_iFrameTrigger <= 0))
	{
		// Reset the frame trigger;
		m_iFrameTrigger = m_iFrameDelay;

		// Increment the frame
		if (++m_iCurFrame >= m_iNumFrames)
		{
			if (m_bOneCycle)
			{
				m_bDying = TRUE;
			}
			m_iCurFrame = 0;
		}
	}
}

SpritePtr GEN::Sprite::AddSprite()
{
	return nullptr;
}
//------------------------------------------------------------
// Sprite.h - C++ Header File
//------------------------------------------------------------


//------------------------------------------------------------
// Description
//------------------------------------------------------------

/**  Sprite class used for animated graphical object manipulation

Key Responsibilities:
(1) Position
(2) Velocity
(3) Z-Order
(4) Bounding rectangle
(5) Bounds action
(6) Hidden/visible
(7) Frame number / delay
(8) Dying or cycle

*/


#ifndef _SPRITE_H
#define _SPRITE_H

//------------------------------------------------------------
// Include Files
//------------------------------------------------------------

#include "Bitmap.h"
#include "Windows.h"
#include <memory>


//------------------------------------------------------------
// Other Declarations
//------------------------------------------------------------


namespace GEN
{
	class Sprite;
}

typedef std::shared_ptr<GEN::Sprite> SpritePtr;

typedef enum BOUNDSACTION
{
	BA_STOP = 0,
	BA_WRAP = 1,
	BA_BOUNCE = 2,
	BA_DIE = 3
};


typedef WORD SPRITEACTION;
const SPRITEACTION	SA_NONE = 0x0000L,
SA_KILL = 0x0001L,
SA_ADDSPRITE = 0x0002L;

//------------------------------------------------------------
// Class Declaration
//------------------------------------------------------------
class GEN::Sprite
{
protected:
	// Member variables
	std::tr1::shared_ptr<Bitmap>	m_pBitmap;
	RECT			m_rcPosition;
	POINT			m_ptVelocity;
	int				m_iZOrder;
	RECT			m_rcBounds;
	BOUNDSACTION 	m_baBoundsAction;
	BOOL			m_bHidden;
	RECT			m_rcCollision;
	int				m_iNumFrames = 1;
	int				m_iCurFrame;
	int				m_iFrameDelay;
	int				m_iFrameTrigger;

	BOOL			m_bDying;
	BOOL			m_bOneCycle;

	// Utility methods
	virtual void UpdateFrame();
public:
	// Constructor(s) / Destructor
	Sprite(std::tr1::shared_ptr<Bitmap> pBitmap);
	Sprite(std::tr1::shared_ptr<Bitmap> pBitmap, const RECT& rcBounds,
		BOUNDSACTION baBoundsAction = BA_STOP);
	Sprite(std::tr1::shared_ptr<Bitmap> pBitmap, const POINT& ptPosition, const POINT& ptVelocity, int iZOrder,
		const RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);
	virtual ~Sprite();

	// General Methods
	virtual SPRITEACTION	Update();
	void					Draw(HDC hDC);
	BOOL					IsPointInside(int x, int y);
	virtual SpritePtr AddSprite();

	// Accessor Methods
	// Position
	RECT		GetPosition() const { return m_rcPosition; };
	void		SetPosition(int x, int y);
	void		SetPosition(const POINT& ptPosition);
	void		SetPosition(const RECT& rcPosition);
	void		OffsetPosition(int x, int y);
	// Velocity
	POINT		GetVelocity() const { return m_ptVelocity; };
	void		SetVelocity(int x, int y);
	void		SetVelocity(const POINT& ptVelocity);

	// Z-Order
	BOOL		GetZOrder() const { return m_iZOrder; };
	void		SetZOrder(int iZOrder) { m_iZOrder = iZOrder; };

	// Bounds
	void		SetBounds(const RECT& rcBounds) { CopyRect(&m_rcBounds, &rcBounds); };
	void		SetBoundsAction(BOUNDSACTION ba) { m_baBoundsAction = ba; };

	// Hidden check
	BOOL		IsHidden() const { return m_bHidden; };
	void		SetHidden(BOOL bHidden) { m_bHidden = bHidden; };

	// Width and height check
	int			GetWidth() const { return m_pBitmap->GetWidth(); };
	int			GetHeight() const { return (m_pBitmap->GetHeight() / m_iNumFrames); };

	// Collision
	RECT		GetCollision() const { return m_rcCollision; };
	BOOL		TestCollision(SpritePtr pTestSprite);
	virtual	void CalcCollisionRect();
	BOOL		IsOffScreen(const RECT& rcPosition, const POINT& ptSize) const;

	// animated frame delay
	void SetNumFrames(int iNumFrames, BOOL bOneCycle = FALSE);
	void SetFrameDelay(int iFrameDelay) { m_iFrameDelay = iFrameDelay; };
	std::tr1::shared_ptr<Bitmap> GetBitmap() { return m_pBitmap; };

	// set kill flag
	void Kill() { m_bDying = TRUE; };



}; // end sprite declaration


#endif
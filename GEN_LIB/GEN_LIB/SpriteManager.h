//------------------------------------------------------------
// C++ GEN Namespace - SpriteManager class
// C++ Header File - SpriteManager.h
//------------------------------------------------------------

#ifndef _SPRITE_MANAGER_H
#define _SPRITE_MANAGER_H

//------------------------------------------------------------
// Include Files
//------------------------------------------------------------

#include "Windows.h"
#include <vector>
#include "Sprite.h"
#include <memory>
#include <algorithm>

//------------------------------------------------------------
// Forward Namespace declar
//------------------------------------------------------------

namespace GEN { class SpriteManager; }

//------------------------------------------------------------
// SpriteManager Class declaration
//------------------------------------------------------------

class GEN::SpriteManager
{
private:
	// Sprite vector sorted in corresponding Z-order
	std::vector<SpritePtr> m_vSprites;

	// sprite collision utility method
	BOOL CheckSpriteCollision(SpritePtr pTestSprite);

	HINSTANCE m_hInstance;
	HWND	  m_hWindow;
public:
	// Constructor(s) / Destructor 
	SpriteManager(HINSTANCE hInstance, HWND hWindow);
	virtual ~SpriteManager();

	// Methods of Sprite Creation
	SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap);
	SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap, const RECT& rcBounds,
		BOUNDSACTION baBoundsAction = BA_STOP);
	SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap, const POINT& ptPosition, const POINT& ptVelocity, int iZOrder,
		const RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP);

	// General methods
	HINSTANCE GetInstance() { return m_hInstance; };
	HWND	  GetWindow() { return m_hWindow; };

	// Sprite Methods
	void	  AddSprite(SpritePtr pSprite);
	void	  DrawSprites(HDC hDC);
	void	  UpdateSprites();
	void	  CleanupSprites();
	SpritePtr IsPointInSprite(int x, int y);

	// TO DO : Update these two functions for Drawing
	virtual BOOL SpriteCollision(SpritePtr pSpriteHitter, SpritePtr pSpriteHittee);
	virtual void SpriteDying(SpritePtr pSprite);
};


#endif

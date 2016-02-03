//-----------------------------------------------------------------
// C++ GEN Namespace, SpriteManager class
// C++ Source File - SpriteManager.cpp
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Include Files
//-----------------------------------------------------------------

#include "SpriteManager.h"

//-----------------------------------------------------------------
// Constructor(s) / Destructor Definition
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// Sprite Management Methods
//-----------------------------------------------------------------

GEN::SpriteManager::SpriteManager(HINSTANCE hInstance, HWND hWindow) :
	m_hInstance(hInstance), m_hWindow(hWindow) {}

GEN::SpriteManager::~SpriteManager()
{}


BOOL GEN::SpriteManager::CheckSpriteCollision(SpritePtr pTestSprite)
{
	// see if sprite has collided with any other sprites
	std::vector<SpritePtr>::iterator siSprite;
	for (siSprite = m_vSprites.begin(); siSprite < m_vSprites.end(); ++siSprite)
	{
		// make sure not to check for collision with itself
		if (pTestSprite != (*siSprite))
		{
			if (pTestSprite->TestCollision(*siSprite))
			{
				// collision detected
				return SpriteCollision((*siSprite), pTestSprite);
			}
		}
	}
	// else no collision
	return FALSE;
}

void GEN::SpriteManager::AddSprite(SpritePtr pSprite)
{
	if (pSprite != NULL)
	{
		if (!m_vSprites.empty())
		{
			// find spot in sprite vector to insert sprite by z-order
			std::vector<SpritePtr>::iterator siSprite;
			for (siSprite = m_vSprites.begin(); siSprite != m_vSprites.end(); ++siSprite)
			{
				if (pSprite->GetZOrder() < (*siSprite)->GetZOrder())
				{
					// insert sprite into sprite vector
					siSprite = m_vSprites.insert(siSprite, pSprite);
					return;
				}
			}
			// if past for loop, the ZOrder is highest, so add to end of vector
			m_vSprites.push_back(pSprite);
		}
		else
		{
			m_vSprites.push_back(pSprite);
		}
	}
}


void GEN::SpriteManager::DrawSprites(HDC hDC)
{
	if (!m_vSprites.empty())
	{
		std::vector<SpritePtr>::iterator siSprite;
		for (siSprite = m_vSprites.begin(); siSprite < m_vSprites.end(); ++siSprite)
		{
			(*siSprite)->Draw(hDC);
		}
	}
}


void GEN::SpriteManager::UpdateSprites() {
	// check to see if sprites vector needs to grow
	if (m_vSprites.size() >= (m_vSprites.capacity() / 2))
	{
		m_vSprites.reserve(m_vSprites.capacity() * 2);
	}

	// Update the sprites in sprite vector
	RECT			rcOldSpritePos;
	SPRITEACTION	saSpriteAction;
	std::vector<SpritePtr>::iterator siSprite = m_vSprites.begin();
	while (siSprite < m_vSprites.end())
	{
		// save old sprite pos in case restoration necessary
		rcOldSpritePos = (*siSprite)->GetPosition();

		// update the sprite
		saSpriteAction = (*siSprite)->Update();

		// handle the SA_ADDSPRITE action
		if (saSpriteAction & SA_ADDSPRITE)
		{
			// allow the sprite to add it's sprite
			AddSprite((*siSprite)->AddSprite());
		}

		// handle the SA_KILL sprite action
		if (saSpriteAction & SA_KILL)
		{
			SpriteDying(*siSprite);
			siSprite = m_vSprites.erase(siSprite);
		}
		if (siSprite != m_vSprites.end())
		{
			// check if sprite collided with any others
			if (CheckSpriteCollision(*siSprite))
			{
				// restore old sprite position
				(*siSprite)->SetPosition(rcOldSpritePos);
				++siSprite;
			}
			else
			{
				++siSprite;
			}
		}
	}
}

void GEN::SpriteManager::CleanupSprites()
{
	// delete and remove sprites in sprite vector
	std::vector<SpritePtr>::iterator siSprite = m_vSprites.begin();
	while (siSprite != m_vSprites.end())
	{
		siSprite = m_vSprites.erase(siSprite);
	}
}

SpritePtr GEN::SpriteManager::IsPointInSprite(int x, int y)
{
	// see if a point is in a sprite in the sprite vector
	if (!m_vSprites.empty())
	{
		std::vector<SpritePtr>::reverse_iterator siSprite;
		for (siSprite = m_vSprites.rbegin(); siSprite != m_vSprites.rend(); ++siSprite)
		{
			if (!(*siSprite)->IsHidden() && (*siSprite)->IsPointInside(x, y))
			{
				return (*siSprite);
			}
		}
	}
	return NULL;
}


BOOL GEN::SpriteManager::SpriteCollision(SpritePtr pSpriteHitter, SpritePtr pSpriteHittee)
{
	return FALSE;
};

void GEN::SpriteManager::SpriteDying(SpritePtr pSprite) {};


SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap)
{
	return SpritePtr(new GEN::Sprite(pBitmap));
}


SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap, const RECT& rcBounds,
	BOUNDSACTION baBoundsAction = BA_STOP)
{
	return SpritePtr(new GEN::Sprite(pBitmap, rcBounds, baBoundsAction));
}

SpritePtr CreateSprite(std::tr1::shared_ptr<Bitmap> pBitmap, const POINT& ptPosition, const POINT& ptVelocity, int iZOrder,
	const RECT& rcBounds, BOUNDSACTION baBoundsAction = BA_STOP)
{
	return SpritePtr(new GEN::Sprite(pBitmap, ptPosition, ptVelocity, iZOrder, rcBounds, baBoundsAction));
}
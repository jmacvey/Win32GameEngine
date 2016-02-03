#include "GameInterface.h"
//#include "UFO_Wrapper.h"




GameInterface::~GameInterface()
{};


//std::tr1::shared_ptr<GameInterface> GameInterface::Create_Wrapper(HINSTANCE hInstance, WNDPROC lpfnWndProc, LPTSTR szWindowClass, LPTSTR szTitle,
//	WORD wIcon, WORD wSmallIcon, int iWidth, int iHeight, UINT uiGameID)
//{
//	std::tr1::shared_ptr<GameInterface> spInterface(nullptr);
//	/*switch (uiGameID)
//	{
//		case IDG_UFO:
//			spInterface = std::tr1::shared_ptr<GameInterface>(new GEN::UFO_Wrapper(hInstance, lpfnWndProc,
//				szWindowClass, szTitle, wIcon, wSmallIcon, iWidth, iHeight));
//			break;
//		default:
//			spInterface = std::tr1::shared_ptr<GameInterface>(new GEN::Wrapper(hInstance, lpfnWndProc,
//				szWindowClass, szTitle, wIcon, wSmallIcon, iWidth, iHeight));
//			/*break;
//	}
//	return spInterface;
//}

/* std::tr1::shared_ptr<GameInterface> GameInterface::GetInterface()
{
return sm_pInterface;
} */


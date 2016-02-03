//--------------------------------------------------------
// C++ Source - MIDIPlayer.cpp
//--------------------------------------------------------

//--------------------------------------------------------
// Include Files
//--------------------------------------------------------

#include "MIDIPlayer.h"

//--------------------------------------------------------
// Constructor(s) / Destructor
//--------------------------------------------------------

MIDIPlayer::MIDIPlayer() :
	m_mciDeviceID(NULL), m_mciLastError(0)
{
}


MIDIPlayer::MIDIPlayer(LPCTSTR lpstrDeviceType, LPCTSTR lpstrElement)
{
	// Set values for open parms
	m_mciOpenParms.lpstrDeviceType = lpstrDeviceType;
	m_mciOpenParms.lpstrElementName = lpstrElement;

	if ((m_mciLastError =
		mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
			(DWORD_PTR)&m_mciOpenParms) == 0))
	{
		m_mciDeviceID = m_mciOpenParms.wDeviceID;
	}
}

MIDIPlayer::~MIDIPlayer()
{
	Close();
}

//--------------------------------------------------------
// General Methods
//--------------------------------------------------------

BOOL MIDIPlayer::Open(LPCTSTR lpstrDeviceType, LPCTSTR lpstrElement)
{
	if (m_mciDeviceID == NULL)
	{
		// Set values for open parms
		m_mciOpenParms.lpstrDeviceType = lpstrDeviceType;
		m_mciOpenParms.lpstrElementName = lpstrElement;

		if ((m_mciLastError =
			mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT,
				(DWORD_PTR)&m_mciOpenParms) == 0))
		{
			m_mciDeviceID = m_mciOpenParms.wDeviceID;
			return TRUE;
		}
		else
		{
			Close();
			return FALSE;
		}
	}
	else
	{
		return FALSE;
	}
}


BOOL MIDIPlayer::Pause() {
	// ensure device is connected
	if (m_mciDeviceID == NULL)
		return FALSE;

	if ((m_mciLastError =
		mciSendCommand(m_mciDeviceID, MCI_PAUSE, 0, NULL)) == 0)
	{
		return TRUE;
	}
	else
	{
		Close();
		return FALSE;
	}
}

BOOL MIDIPlayer::Play(HWND hWindow) {

	if (m_mciDeviceID == NULL)
		return FALSE;

	m_mciPlayParms.dwCallback = (DWORD)hWindow;

	if ((m_mciLastError =
		mciSendCommand(m_mciDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&m_mciPlayParms)) == 0)
	{
		return TRUE;
	}
	else
	{
		Close();
		return FALSE;
	}
}


BOOL MIDIPlayer::Close() {

	if (m_mciDeviceID == NULL)
		return FALSE;

	if ((m_mciLastError =
		mciSendCommand(m_mciDeviceID, MCI_CLOSE, 0, NULL)) == 0)
	{
		// clear device ID
		m_mciDeviceID = NULL;
		return TRUE;
	}
	else return FALSE;
}

BOOL MIDIPlayer::Restart(HWND hWindow)
{
	if (m_mciDeviceID == NULL)
		return FALSE;

	if ((m_mciLastError =
		mciSendCommand(m_mciDeviceID, MCI_SEEK, MCI_SEEK_TO_START,
			(DWORD_PTR)&m_mciSeekParms)) == 0)
	{
		Play(hWindow);
		return TRUE;
	}
	else
	{
		Close();
		return FALSE;
	}
}
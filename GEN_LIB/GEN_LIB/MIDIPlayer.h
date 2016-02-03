//--------------------------------------------------------
// C++ Header - MIDIPlayer.h
//--------------------------------------------------------

#ifndef _MIDI_PLAYER_H
#define _MIDI_PLAYER_H

//--------------------------------------------------------
// Include Files
//--------------------------------------------------------

#include "Windows.h"

//--------------------------------------------------------
// MIDIPlayer Class Declaration
//--------------------------------------------------------

class MIDIPlayer
{
private:
	UINT			m_mciDeviceID;
	MCI_OPEN_PARMS	m_mciOpenParms;
	MCI_PLAY_PARMS	m_mciPlayParms;
	MCI_SEEK_PARMS	m_mciSeekParms;
	MCIERROR		m_mciLastError = 0;
public:
	// Constructor(s) / Destructor
	MIDIPlayer(); // default constructor
	MIDIPlayer(LPCTSTR lpstrDeviceType, LPCTSTR lpstrElement);
	~MIDIPlayer(); // default destructor

				   // General Methods

	BOOL Open(LPCTSTR lpstrDeviceType, LPCTSTR lpstrElement);
	BOOL Pause();
	BOOL Play(HWND hWindow);
	BOOL Close();
	BOOL Restart(HWND hWindow);

	// accessor methods
	UINT		GetDeviceID() { return m_mciDeviceID; };
	MCIERROR	GetLastError() { return m_mciLastError; };
	LPCTSTR		GetDeviceType() { return m_mciOpenParms.lpstrDeviceType; };
	LPCTSTR		GetFileName() { return m_mciOpenParms.lpstrElementName; };
};


#endif
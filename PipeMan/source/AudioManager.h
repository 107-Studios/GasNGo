#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#pragma region Includes

#include <string>
#include <vector>

//--------------------------
// !MUST HAVE FOR SDL SOUND/MIXER!
#include <stdio.h>
#include <assert.h>
#include <signal.h>
#include "Include\SDL_thread.h"
#include "Include\SDL.h"
#include "Include\SDL_sound.h"
#include "Include\SDL_mixer.h"
#pragma comment(lib, "libs/sdl.lib")
#pragma comment(lib, "libs/sdl_mixer.lib")
//--------------------------

using std::string;
using std::vector;

#pragma endregion

struct BGMSample
{
	string szFilename;
	Mix_Music* pData;
};

struct SoundSample
{
	string szFilename;
	Mix_Chunk* pData;
	int nRefCount;

	SoundSample() 
	{
		nRefCount = 0;
		pData = NULL;
	}
};

class CAudioManager
{
#pragma region Data Members

private:

	vector<SoundSample*> m_vSounds;
	vector<BGMSample*> m_vBGMs;

public:

#pragma endregion

#pragma region Functions

private:
public:

	/*General Functions*/
	CAudioManager();
	~CAudioManager();

	//////////////////////////////////////////////////////////////////////////
	//	Func. Name: Initialize
	//	Parameter 1: nFlags - Inits the desired codecs (MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG)
	//  Parameter 2: nChannelsToAllocate - Number of Channels wished to allocate for use
	//  Return: void
	//////////////////////////////////////////////////////////////////////////
	void Initialize(int nFlags = 0, int nChannelsToAllocate = 8 );
	
	//////////////////////////////////////////////////////////////////////////
	// Func. Name: Shutdown
	// Parameter 1: void
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void Shutdown(void);
	
	/*Sound Effect Functions*/
	//////////////////////////////////////////////////////////////////////////
	// Func. Name: LoadSound
	// Parameter 1: szFilename - the filename for the sound file.(include file extension)
	// Return: int - the Sound ID for the corresponding sound file
	//////////////////////////////////////////////////////////////////////////
	int LoadSound(string szFilename);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: PlaySound
	// Parameter 1: nSoundID - desired sound wishing to play
	// Parameter 2: nChannel - desired channel to play sound on. (sending -1 will play sound on first available channel)
	// Parameter 3: nNumLoops - Amount of times to loop the sound
	// Parameter 4: bFadeIn - want the sound to Fade In?
	// Parameter 5: nMsFadeIn - length (in Milliseconds) of Fade In starting now.
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void PlaySound(int nSoundID, int nChannel = -1, int nNumLoops = 1, bool bFadeIn = false, int nMsFadeIn = 0);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: SetSoundVolume
	// Parameter 1: nSoundID - desired sound wishing to change volume
	// Parameter 2: nVolume - desired volume (max 128)
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void SetSoundVolume(int nSoundID, int nVolume);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: FreeSound
	// Parameter 1: nSoundID - desired sound wishing to remove
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void FreeSound(int* nSoundID);

	/*Background Music Functions*/

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: LoadBGM
	// Parameter 1: szFileName - filename of Music you wish to load
	// Return: int - the ID for the Background Music loaded
	//////////////////////////////////////////////////////////////////////////
	int LoadBGM(string szFilename);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: FreeBGM
	// Parameter 1: nMusicID - the ID for the Music file you wish to remove
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void FreeBGM(int nMusicID);
	
	//////////////////////////////////////////////////////////////////////////
	// Func. Name: PlayBGM
	// Parameter 1: nMusicID - the desired Music file to play (specifed by ID)
	// Parameter 2: nNumLoops - amount of times to play the music file
	// Parameter 3: bFadeIn - want the music to fade in?
	// Parameter 4: nMsFadeIn - length (in Milliseconds) of fade in starting now
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void PlayBGM(int nMusicID, int nNumLoops = 1, bool bFadeIn = false, int nMsFadeIn = 0);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: SetBGMVolume
	// Parameter 1: nVolume - volume desired
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void SetBGMVolume(int nVolume);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: PauseBGM
	// Parameter 1: void
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void PauseBGM(void);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: ResumeBGM
	// Parameter 1: void
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void ResumeBGM(void);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: RewindBGM
	// Parameter 1: void
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void RewindBGM(void);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: StopBGMPlayback
	// Parameter 1: bFadeout - would you like the Music to Fade out?
	// Parameter 2: nMsFadeOut - Length (in Milliseconds) of fade out starting now.
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void StopBGMPlayback(bool bFadeOut = false, int nMsFadeOut = 0);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isBGMPlaying
	// Parameter 1: void
	// Return: bool - whether or not the Background Music is playing.
	//////////////////////////////////////////////////////////////////////////
	bool isBGMPlaying(void);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isBGMPaused
	// Parameter 1: void
	// Return: bool - whether or not the Background Music is paused.
	//////////////////////////////////////////////////////////////////////////
	bool isBGMPaused(void);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isBGMFading
	// Parameter 1: void
	// Return: bool - whether or not the Background Music is doing any sort of Fading.
	//////////////////////////////////////////////////////////////////////////
	bool isBGMFading(void);

	/*Channel Manipulation Functions*/
	//////////////////////////////////////////////////////////////////////////
	// Func. Name: SetChannelVolume
	// Parameter 1: nVolume - desited volume for the channel (max 128)
	// Parameter 2: nChannel - desired channel you want to set the volume. (passing -1 will set all channels)
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void SetChannelVolume(int nVolume, int nChannel = -1);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: PauseChannel
	// Parameter 1: nChannel - desired channel you want to Pause. (passing -1 will pause all channels)
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void PauseChannel(int nChannel = -1);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: ResumeChannel
	// Parameter 1: nChannel - desired channel you want to Resume. (passing -1 will resume all channels)
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void ResumeChannel(int nChannel = -1);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: StopChannelPlayback
	// Parameter 1: nChannel - desired channel you want to stop Playback. (passing -1 will stop all channels)
	// Parameter 2: bFadeout - would you like the channel to fade out?
	// Parameter 3: nMsFadeOut - length (in Milliseconds) of FadeOut starting now.
	// Return: void
	//////////////////////////////////////////////////////////////////////////
	void StopChannelPlayback(int nChannel = -1, bool bFadeout = false, int nMsFadeOut = 0);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isChannelPlaying
	// Parameter 1: nChannel - desired channel you wish to check is playing.
	// Return: bool - whether or not the channel is playing?
	//////////////////////////////////////////////////////////////////////////
	bool isChannelPlaying(int nChannel);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isChannelPaused
	// Parameter 1: nChannel - desired channel you wish to check is paused.
	// Return: bool - whether or not the channel is Paused?
	//////////////////////////////////////////////////////////////////////////
	bool isChannelPaused(int nChannel);

	//////////////////////////////////////////////////////////////////////////
	// Func. Name: isChannelFading
	// Parameter 1: nChannel - desired channel you wish to check is fading.
	// Return: bool - whether or not the channel is doing some sort of Fading?
	//////////////////////////////////////////////////////////////////////////
	bool isChannelFading(int nChannel);

#pragma endregion
};

#endif
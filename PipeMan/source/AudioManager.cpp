#include "AudioManager.h"

CAudioManager::CAudioManager()
{

}

CAudioManager::~CAudioManager()
{

}

//////////////////////////////////////////////////////////////////////////
//	Func. Name: Initialize
//	Parameter 1: nFlags - Inits the desired codecs (MIX_INIT_FLAC, MIX_INIT_MOD, MIX_INIT_MP3, MIX_INIT_OGG)
//  Parameter 2: nChannelsToAllocate - Number of Channels wished to allocate for use
//  Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::Initialize(int nFlags /*= 0*/, int nChannelsToAllocate /*= 8*/)
{
	/*Init SDL API (Audio Only)*/
	assert(SDL_Init(SDL_INIT_AUDIO) != -1);

	/*init Mixer with additional Codecs*/
	int initted = Mix_Init(nFlags);	
	assert( (initted&nFlags) == nFlags );  // desired codecs were not initialized

	/*open audio device*/
	assert( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,MIX_DEFAULT_FORMAT,2,4096)>0 );

	/*Allocate channels*/
	Mix_AllocateChannels(nChannelsToAllocate);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: Shutdown
// Parameter 1: void
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::Shutdown()
{
	/* free all BGM data */
	for (unsigned int i = 0; i < m_vBGMs.size(); i++)
		Mix_FreeMusic(m_vBGMs[i]->pData);

	/* free all Sound data*/
	for (unsigned int i = 0; i < m_vSounds.size(); i++)
		Mix_FreeChunk(m_vSounds[i]->pData);

	/*clear all pointers in the vectors*/
	m_vSounds.clear();
	m_vBGMs.clear();

	/*deallocate channels*/
	Mix_AllocateChannels(0);

	/*Shutdown SDL APIs*/
	Mix_CloseAudio();
	SDL_Quit();
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: LoadSound
// Parameter 1: szFilename - the filename for the sound file.(include file extension)
// Return: int - the Sound ID for the corresponding sound file
//////////////////////////////////////////////////////////////////////////
int CAudioManager::LoadSound(string szFilename)
{
	/*Is sound already loaded?*/
	for (unsigned int i = 0; i < m_vSounds.size(); i++)
		if ( m_vSounds[i]->szFilename == szFilename )
		{
			m_vSounds[i]->nRefCount++;
			return i;
		}

	/*No? Add it to the list.*/
	SoundSample* pTemp = new SoundSample();
	pTemp->szFilename = szFilename;
	pTemp->pData = Mix_LoadWAV(pTemp->szFilename.c_str());
	assert( pTemp->pData != NULL );
	pTemp->nRefCount = 1;
	m_vSounds.push_back(pTemp);

	/*return assigned ID*/
	return m_vSounds.size() - 1;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: PlaySound
// Parameter 1: nSoundID - desired sound wishing to play
// Parameter 2: nChannel - desired channel to play sound on. (sending -1 will play sound on first available channel)
// Parameter 3: nNumLoops - Amount of times to loop the sound
// Parameter 4: bFadeIn - want the sound to Fade In?
// Parameter 5: nMsFadeIn - length (in Milliseconds) of Fade In starting now.
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::PlaySound( int nSoundID, int nChannel /*= -1*/, int nNumLoops /*= 1*/, bool bFadeIn /*= false*/, int nMsFadeIn /*= 0*/)
{
	if ( bFadeIn )
		Mix_FadeInChannel(nChannel, m_vSounds[nSoundID]->pData, nNumLoops, nMsFadeIn);
	else
		Mix_PlayChannel(nChannel, m_vSounds[nSoundID]->pData, nNumLoops);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: SetSoundVolume
// Parameter 1: nSoundID - desired sound wishing to change volume
// Parameter 2: nVolume - desired volume (max 128)
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::SetSoundVolume( int nSoundID, int nVolume )
{
	Mix_VolumeChunk(m_vSounds[nSoundID]->pData, nVolume);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: FreeSound
// Parameter 1: nSoundID - desired sound wishing to remove
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::FreeSound( int* nSoundID )
{
	/*Make sure ID is within range*/
	if ( *nSoundID > (int)m_vSounds.size() - 1 || *nSoundID < 0 )
		return;

	m_vSounds[*nSoundID]->nRefCount--;
	if (m_vSounds[*nSoundID]->nRefCount > 0)
	{
		*nSoundID = -1;
		return;
	}

	/*take care of the trash*/
	Mix_FreeChunk(m_vSounds[*nSoundID]->pData);
	vector<SoundSample*>::iterator position = m_vSounds.begin();

	//for ( int i = 0; i < nSoundID; i++)
	position+=*nSoundID;

	/*Remove sound from collection*/
	m_vSounds.erase(position);
	*nSoundID = -1;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: LoadBGM
// Parameter 1: szFileName - filename of Music you wish to load
// Return: int - the ID for the Background Music loaded
//////////////////////////////////////////////////////////////////////////
int CAudioManager::LoadBGM( string szFilename )
{
	/*Is Music already loaded?*/
	for (unsigned int i = 0; i < m_vBGMs.size(); i++)
		if ( m_vBGMs[i]->szFilename == szFilename )
			return i;

	/*No? Add it to the list.*/
	BGMSample* pTemp = new BGMSample();
	pTemp->szFilename = szFilename;
	pTemp->pData = Mix_LoadMUS(pTemp->szFilename.c_str());
	assert( pTemp->pData != NULL );
	m_vBGMs.push_back(pTemp);

	/*return assigned ID*/
	return m_vBGMs.size() - 1;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: FreeBGM
// Parameter 1: nMusicID - the ID for the Music file you wish to remove
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::FreeBGM( int nMusicID )
{
	/*Make sure ID is within range*/
	if ( nMusicID > (int)m_vBGMs.size() - 1 || nMusicID < 0 )
		return;

	/*take care of the trash*/
	Mix_FreeMusic(m_vBGMs[nMusicID]->pData);
	vector<BGMSample*>::iterator position = m_vBGMs.begin();

	//for ( int i = 0; i < nSoundID; i++)
	position+=nMusicID;

	/*Remove music from collection*/
	m_vBGMs.erase(position);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: PlayBGM
// Parameter 1: nMusicID - the desired Music file to play (specifed by ID)
// Parameter 2: nNumLoops - amount of times to play the music file
// Parameter 3: bFadeIn - want the music to fade in?
// Parameter 4: nMsFadeIn - length (in Milliseconds) of fade in starting now
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::PlayBGM( int nMusicID, int nNumLoops /*= 1*/, bool bFadeIn /*= false*/, int nMsFadeIn  /*= 0*/)
{
	/* ?Does Music Exist?*/
	assert( nMusicID >= 0 || (unsigned int)nMusicID <= m_vBGMs.size() - 1);

	/*Play the Music*/
	if ( bFadeIn )
		Mix_FadeInMusic(m_vBGMs[nMusicID]->pData, nNumLoops, nMsFadeIn);
	else
		Mix_PlayMusic(m_vBGMs[nMusicID]->pData, nNumLoops);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: SetBGMVolume
// Parameter 1: nVolume - volume desired
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::SetBGMVolume( int nVolume )
{
	Mix_VolumeMusic(nVolume);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: PauseBGM
// Parameter 1: void
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::PauseBGM( void )
{
	Mix_PauseMusic();
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: ResumeBGM
// Parameter 1: void
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::ResumeBGM( void )
{
	Mix_ResumeMusic();
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: RewindBGM
// Parameter 1: void
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::RewindBGM( void )
{
	Mix_RewindMusic();
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: StopBGMPlayback
// Parameter 1: bFadeout - would you like the Music to Fade out?
// Parameter 2: nMsFadeOut - Length (in Milliseconds) of fade out starting now.
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::StopBGMPlayback( bool bFadeOut, int nMsFadeOut )
{
	if ( bFadeOut )
		Mix_FadeOutMusic(nMsFadeOut);
	else
		Mix_HaltMusic();
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isBGMPlaying
// Parameter 1: void
// Return: bool - whether or not the Background Music is playing.
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isBGMPlaying( void )
{
	if ( Mix_PlayingMusic() )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isBGMPaused
// Parameter 1: void
// Return: bool - whether or not the Background Music is paused.
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isBGMPaused( void )
{
	if ( Mix_PausedMusic() )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isBGMFading
// Parameter 1: void
// Return: bool - whether or not the Background Music is doing any sort of Fading.
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isBGMFading( void )
{
	if ( Mix_FadingMusic() )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: SetChannelVolume
// Parameter 1: nVolume - desited volume for the channel (max 128)
// Parameter 2: nChannel - desired channel you want to set the volume. (passing -1 will set all channels)
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::SetChannelVolume( int nVolume, int nChannel /*= -1*/ )
{
	Mix_Volume(nChannel, nVolume);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: PauseChannel
// Parameter 1: nChannel - desired channel you want to Pause. (passing -1 will pause all channels)
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::PauseChannel( int nChannel /*= -1*/ )
{
	Mix_Pause(nChannel);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: ResumeChannel
// Parameter 1: nChannel - desired channel you want to Resume. (passing -1 will resume all channels)
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::ResumeChannel( int nChannel /*= -1*/ )
{
	Mix_Resume(nChannel);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: StopChannelPlayback
// Parameter 1: nChannel - desired channel you want to stop Playback. (passing -1 will stop all channels)
// Parameter 2: bFadeout - would you like the channel to fade out?
// Parameter 3: nMsFadeOut - length (in Milliseconds) of FadeOut starting now.
// Return: void
//////////////////////////////////////////////////////////////////////////
void CAudioManager::StopChannelPlayback( int nChannel /*= -1*/, bool bFadeout /*= false*/, int nMsFadeOut /*= 0*/ )
{
	if (bFadeout)
		Mix_FadeOutChannel(nChannel, nMsFadeOut);
	else
		Mix_HaltChannel(nChannel);
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isChannelPlaying
// Parameter 1: nChannel - desired channel you wish to check is playing.
// Return: bool - whether or not the channel is playing?
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isChannelPlaying( int nChannel )
{
	if ( Mix_Playing(nChannel) )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isChannelPaused
// Parameter 1: nChannel - desired channel you wish to check is paused.
// Return: bool - whether or not the channel is Paused?
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isChannelPaused( int nChannel )
{
	if ( Mix_Paused(nChannel) )
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// Func. Name: isChannelFading
// Parameter 1: nChannel - desired channel you wish to check is fading.
// Return: bool - whether or not the channel is doing some sort of Fading?
//////////////////////////////////////////////////////////////////////////
bool CAudioManager::isChannelFading( int nChannel )
{
	if ( Mix_FadingChannel(nChannel) )
		return true;
	else
		return false;
}

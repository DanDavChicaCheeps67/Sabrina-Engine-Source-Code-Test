#ifndef _SOUND_H
#define _SOUND_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "openFiles.h"

//Music file class
struct MusicFile
{
	double loopPosition;
	int currentVolume,maxVolume, minVolume, channel;
	std::string location;
	Mix_Music* music;
	bool paused, loop, close, open, playing;
	Mix_Chunk* soundEffect;
};

// initiate Sound for the entire engine
bool initSound(int&,int&,int&,int&);

// Open Music Files
bool openMusicFile(MusicFile*);
bool openSoundEffect(MusicFile*);
void closeMusicFile(MusicFile*);

// Pause and Unpause
void playMusic(MusicFile*);
void pauseMusic(MusicFile*);
void unPauseMusic(MusicFile*);
void changeVolume(MusicFile*,bool&,int&);
void fadeInMusic(MusicFile*,int&);
void fadeOutMusic(MusicFile*,int&);
void playSoundEffect(MusicFile*);
// Free Memory
void closeMusicFile(MusicFile*);
void closeSoundEffect(MusicFile*);
void destroyMixAudioSystem();
#endif

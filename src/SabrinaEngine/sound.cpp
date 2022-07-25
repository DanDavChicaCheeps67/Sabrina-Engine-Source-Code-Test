#include "sound.h"

bool initSound()
{
	if (SDL_InitSubSystem(SDL_INIT_AUDIO) != 0)
	{
		printf("SDL Error: %s\n", SDL_GetError());
		return false;
	}
	else 
	{
		int flags = MIX_INIT_OGG | MIX_INIT_MOD;
		if (Mix_Init(flags)&flags != flags )
		{
			printf("Mix_Init: %s\n", Mix_GetError());
			return false;
		}
		else
			return true;
	}
}

bool initMusic(MusicFile *source, bool loop, std::string location, short channel, short maxVolume, short minVolume)
{
	source->loop = loop;
	source->location = location;
	source->channel = channel;
	source->maxVolume = maxVolume;
	source->minVolume = minVolume;

	if (openMusicFile(source) != false)
		return true;
	else
	{
		printf("Failed Music Load\n");
		return false;
	}
}

bool initSoundEffect(MusicFile *source, std::string location)
{
	source->location = location;
	return openSoundEffect(source);
}

bool initMixer(int soundRate, Uint16 format, int channels, int buffer)
{
	if (Mix_OpenAudio(soundRate,format,channels,buffer) < 0)
	{
		printf("SDL ERROR: %s\n",SDL_GetError());
		return false;
	}
	else
		return true;
}

void freeMixer()
{
	Mix_CloseAudio();
}

bool openMusicFile(MusicFile* source)
{
	bool worked = false;
	source->music = Mix_LoadMUS(source->location.c_str());
	if (source->music != NULL)
	{
		source->playing = false;
		source->open = true;
		source->close = false;
		worked = true;
		printf("MUSIC OPEN\n");
	}
	else
		printf("SDL ERROR: %s\n",SDL_GetError());

	return worked;
}

bool openSoundEffect(MusicFile* source)
{
	source->soundEffect = Mix_LoadWAV(source->location.c_str());
	if (source->soundEffect != NULL)
		return true;
	else
	{
		printf("SDL Error: %s\n",Mix_GetError());
		return false;
	}
}

void closeMusicFile(MusicFile* source)
{
	Mix_FreeMusic(source->music);
	source->music = NULL;
}

void playMusic(MusicFile* source)
{
	if (Mix_PlayMusic(source->music, source->loop ? -1:0 ) < 0)
		printf("Mix Error: %s\n",Mix_GetError());
	else
	{
		source->currentVolume = Mix_VolumeMusic(-1);
		source->playing = true;
		source->paused = false;
	}
}

void fadeInMusic(MusicFile* source, int &amount)
{
	if (Mix_FadeInMusic(source->music, source->loop ? 0:-1, amount) < 0)
		printf("Mixer Error: %s\n", Mix_GetError());
}

void fadeOutMusic(MusicFile* source, int &amount)
{
	while (!(Mix_FadeOutMusic(3000)) && (source->paused != true))
	{
		SDL_Delay(100);
		printf("DELAYING FOR SOUND\n");
	}
}

void pauseMusic(MusicFile* source)
{
	Mix_PauseMusic();
	source->paused = true;
}

void unPauseMusic(MusicFile* source)
{
	Mix_ResumeMusic();
	source->paused = false;
}

void changeVolume(MusicFile* source,bool &increase,int &value)
{
	if (increase != false)
		Mix_VolumeMusic(source->currentVolume + value);
	else
		Mix_VolumeMusic(source->currentVolume - value);
	
	source->currentVolume = Mix_VolumeMusic(-1);
}

void closeSoundEffect(MusicFile* source)
{
	Mix_FreeChunk(source->soundEffect);
	source->soundEffect = NULL;
}

void destroyAudioSystem()
{
	SDL_InitSubSystem(SDL_INIT_AUDIO);
}

void playSoundEffect(MusicFile *source)
{
	if (Mix_PlayChannel(source->channel,source->soundEffect,source->loop ? -1:0) < 0)
		printf("MIX ERROR: %s",Mix_GetError());
}

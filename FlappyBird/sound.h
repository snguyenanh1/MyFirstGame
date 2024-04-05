#ifndef _SOUND__H
#define _SOUND__H

#include <SDL.h>
#include <SDL_mixer.h>

class Sound {
private:
	Mix_Music* music;
	Mix_Chunk* sound;
	bool isPlayed;
public:
	Sound();
	~Sound();
	bool loadMusic(const char* path);
	bool loadSound(const char* path);
	void playMusic(int loops = -1);
	void playSound(int channel = -1);
	void stopMusic();
	void pauseMusic();
	void resumeMusic();
	bool isPlaying();
    void reset();
    bool isPlayedMusic();
};

#endif // _SOUND__H
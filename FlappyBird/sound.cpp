#include "sound.h"

Sound::Sound() {
	music = nullptr;
	sound = nullptr;
    isPlayed = false;
}

Sound::~Sound() {
    if (music != nullptr) {
        Mix_FreeMusic(music);
        music = nullptr;
    }
    if (sound != nullptr) {
        Mix_FreeChunk(sound);
        sound = nullptr;
    }
}

bool Sound::loadMusic(const char* path) {
    music = Mix_LoadMUS(path);
    if (music == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to load music: %s", Mix_GetError());
        return false;
    }
    return true;
}

bool Sound::loadSound(const char* path) {
    sound = Mix_LoadWAV(path);
    if (sound == nullptr) {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Failed to load sound: %s", Mix_GetError());
        return false;
    }
    return true;
}

void Sound::playMusic(int loops) {
    if (music) Mix_PlayMusic(music, loops);
    isPlayed = true;
}

void Sound::playSound(int channel) {
	if (sound) Mix_PlayChannel(channel, sound, 0);
    isPlayed = true;
}

void Sound::stopMusic() {
    if (music) Mix_HaltMusic();
}

void Sound::pauseMusic() {
       if (music) Mix_PauseMusic();
}

void Sound::resumeMusic() {
          if (music) Mix_ResumeMusic();
}

bool Sound::isPlaying() {
    if(music) return Mix_PlayingMusic();
    if(sound) return Mix_Playing(-1);
}

void Sound::reset() {
    isPlayed = false;
}

bool Sound::isPlayedMusic() {
    return isPlayed;
}
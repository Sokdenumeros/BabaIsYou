#ifndef _AUDIO_ENGINE_H_
#define _AUDIO_ENGINE_H_

#include "fmod_studio.hpp"
#include "fmod_studio.h"
#include "fmod.hpp"


#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

#endif

using namespace std;

class AudioEngine {
public:
	void Init();
	void Update();
	int ErrorCheck(FMOD_RESULT result);
	/*
	static void LoadBank(const string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	static void LoadEvent(const string& strEventName);
	static void LoadSound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	static void UnLoadSound(const string& strSoundName);
	//static void Set3dListenerAndOrientation(const FMOD_VECTOR& vPos = FMOD_VECTOR{ 0, 0, 0 }, float fVolumedB = 0.0f);
	static int  PlaySound(const string& strSoundName, const FMOD_VECTOR& position = FMOD_VECTOR{ 0, 0, 0 }, float fVolumedB = 0.0f);
	//static void PlayEvent(const string& strEventName);
	static void StopChannel(int nChannelId);
	//static void StopEvent(const string& strEventName, bool bImmediate = false);
	//static void GeteventParameter(const string& strEventName, const string& strEventParameter, float* parameter);
	//static void SetEventParameter(const string& strEventName, const string& strParameterName, float fValue);
	//static void StopAllChannels();
	static void SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& vPosition);
	static void SetChannelvolume(int nChannelId, float fVolumedB);
	static bool IsPlaying(int nChannelId);
	//static bool IsEventPlaying(const string& strEventName);
	static float dbToVolume(float db);
	static float VolumeTodb(float volume);*/

private:

	static FMOD::Studio::System* mpStudioSystem;
	static FMOD::System* mpSystem;

	static int mnNextChannelId;

	static map<string, FMOD::Sound*> SoundMap;
	static map<int, FMOD::Channel*> ChannelMap;
	static map<string, FMOD::Studio::EventInstance*> EventMap;
	static map<string, FMOD::Studio::Bank*> BankMap;
};
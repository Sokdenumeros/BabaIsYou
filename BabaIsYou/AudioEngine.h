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
#include "common.h"

#endif

using namespace std;

class AudioEngine {
public:
	void Init();
	void Update();
	int ErrorCheck(FMOD_RESULT result);
	
	void LoadBank(const string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags);
	void LoadEvent(const string& strEventName);
	void LoadSound(const string& strSoundName, bool b3d = true, bool bLooping = false, bool bStream = false);
	void UnLoadSound(const string& strSoundName);
	//static void Set3dListenerAndOrientation(const FMOD_VECTOR& vPos = FMOD_VECTOR{ 0, 0, 0 }, float fVolumedB = 0.0f);
	int PlayS(const string& strSoundName, const FMOD_VECTOR& position = FMOD_VECTOR{ 0, 0, 0 }, float fVolumedB = 0.0f);
	//static void PlayEvent(const string& strEventName);
	void StopChannel(int nChannelId);
	//static void StopEvent(const string& strEventName, bool bImmediate = false);
	//static void GeteventParameter(const string& strEventName, const string& strEventParameter, float* parameter);
	//static void SetEventParameter(const string& strEventName, const string& strParameterName, float fValue);
	//static void StopAllChannels();
	void SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& vPosition);
	void SetChannelvolume(int nChannelId, float fVolumedB);
	bool IsPlaying(int nChannelId);
	//static bool IsEventPlaying(const string& strEventName);
	float dbToVolume(float db);
	float VolumeTodb(float volume);

private:
	FMOD::Studio::System * mpStudioSystem;
	FMOD::System * mpSystem;

	int mnNextChannelId;

	map<string, FMOD::Sound*> SoundMap;
	map<int, FMOD::Channel*> ChannelMap;
	map<string, FMOD::Studio::EventInstance*> EventMap;
	map<string, FMOD::Studio::Bank*> BankMap;
};
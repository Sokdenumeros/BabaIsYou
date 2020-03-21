#include "AudioEngine.h"


FMOD::Studio::System * AudioEngine::mpStudioSystem = NULL;
FMOD::System * AudioEngine::mpSystem = NULL;

int AudioEngine::mnNextChannelId;

map<string, FMOD::Sound*> AudioEngine::SoundMap;
map<int, FMOD::Channel*> AudioEngine::ChannelMap;
map<string, FMOD::Studio::EventInstance*> AudioEngine::EventMap;
map<string, FMOD::Studio::Bank*> AudioEngine::BankMap;


void AudioEngine::Init() {
	mpStudioSystem = NULL;
	ErrorCheck(FMOD::Studio::System::create(&mpStudioSystem));
	ErrorCheck(mpStudioSystem->initialize(32, FMOD_STUDIO_INIT_LIVEUPDATE, FMOD_INIT_PROFILE_ENABLE, NULL));
	//Possible cagada
	mpSystem = NULL;
	ErrorCheck(mpStudioSystem->getCoreSystem(&mpSystem));
}

void AudioEngine::Update() {
	bool bIsPlaying;
	for (auto it = ChannelMap.begin(), itEnd = ChannelMap.end(); it != itEnd; ++it)
	{
		bIsPlaying = false;
		it->second->isPlaying(&bIsPlaying);
		auto temp = it;
		++it;
		if (!bIsPlaying) ChannelMap.erase(temp);
	}
}

int AudioEngine::ErrorCheck(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		cerr << "FMOD ERROR " << result << endl;
		return 1;
	}
	return 0;
}

void AudioEngine::LoadSound(const std::string& strSoundName, bool b3d, bool bLooping, bool bStream)
{
	auto tFoundIt = SoundMap.find(strSoundName);
	if (tFoundIt != SoundMap.end()) return;

	FMOD_MODE eMode = FMOD_DEFAULT;
	eMode |= b3d ? FMOD_3D : FMOD_2D;
	eMode |= bLooping ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF;
	eMode |= bStream ? FMOD_CREATESTREAM : FMOD_CREATECOMPRESSEDSAMPLE;

	FMOD::Sound* pSound = nullptr;
	ErrorCheck(mpSystem->createSound(strSoundName.c_str(), eMode, nullptr, &pSound));
	if (pSound) {
		SoundMap[strSoundName] = pSound;
	}

}

void AudioEngine::UnLoadSound(const std::string& strSoundName)
{
	auto tFoundIt = SoundMap.find(strSoundName);
	if (tFoundIt == SoundMap.end())
		return;

	ErrorCheck(tFoundIt->second->release());
	SoundMap.erase(tFoundIt);
}

int AudioEngine::PlayS(const string& strSoundName, const FMOD_VECTOR& position, float fVolumedB)
{
	int nChannelId = mnNextChannelId++;
	auto tFoundIt = SoundMap.find(strSoundName);
	if (tFoundIt == SoundMap.end())
	{
		LoadSound(strSoundName);
		tFoundIt = SoundMap.find(strSoundName);
		if (tFoundIt == SoundMap.end()) return nChannelId;
	}
	FMOD::Channel* pChannel = nullptr;
	ErrorCheck(mpSystem->playSound(tFoundIt->second, nullptr, true, &pChannel));
	if (pChannel)
	{
		FMOD_MODE currMode;
		tFoundIt->second->getMode(&currMode);
		if (currMode & FMOD_3D) ErrorCheck(pChannel->set3DAttributes(&position, nullptr));

		ErrorCheck(pChannel->setVolume(dbToVolume(fVolumedB)));
		ErrorCheck(pChannel->setPaused(false));
		ChannelMap[nChannelId] = pChannel;
	}
	return nChannelId;
}

void AudioEngine::SetChannel3dPosition(int nChannelId, const FMOD_VECTOR& position)
{
	auto tFoundIt = ChannelMap.find(nChannelId);
	if (tFoundIt == ChannelMap.end()) return;

	ErrorCheck(tFoundIt->second->set3DAttributes(&position, NULL));
}

void AudioEngine::SetChannelvolume(int nChannelId, float fVolumedB)
{
	auto tFoundIt = ChannelMap.find(nChannelId);
	if (tFoundIt == ChannelMap.end()) return;

	ErrorCheck(tFoundIt->second->setVolume(dbToVolume(fVolumedB)));
}

bool AudioEngine::IsPlaying(int nChannelId)
{
	bool b = false;
	ChannelMap[nChannelId]->isPlaying(&b);
	return b;
}

void AudioEngine::StopAllChannels() {
	for (auto it = ChannelMap.begin(), end = ChannelMap.end(); it != end; ++it) it->second->stop();
}

void AudioEngine::StopChannel(int nChannelId) {
	ChannelMap[nChannelId]->stop();
}

void AudioEngine::LoadBank(const std::string& strBankName, FMOD_STUDIO_LOAD_BANK_FLAGS flags) {
	auto tFoundIt = BankMap.find(strBankName);
	if (tFoundIt != BankMap.end()) return;

	FMOD::Studio::Bank* pBank;
	ErrorCheck(mpStudioSystem->loadBankFile(strBankName.c_str(), flags, &pBank));

	if (pBank) BankMap[strBankName] = pBank;
}

void AudioEngine::LoadEvent(const std::string& strEventName) {
	auto tFoundit = EventMap.find(strEventName);
	if (tFoundit != EventMap.end()) return;
	FMOD::Studio::EventDescription* pEventDescription = NULL;
	ErrorCheck(mpStudioSystem->getEvent(strEventName.c_str(), &pEventDescription));
	if (pEventDescription) {
		FMOD::Studio::EventInstance* pEventInstance = NULL;
		ErrorCheck(pEventDescription->createInstance(&pEventInstance));
		if (pEventInstance) EventMap[strEventName] = pEventInstance;
	}
}

float AudioEngine::dbToVolume(float dB)
{
	return powf(10.0f, 0.05f * dB);
}

float AudioEngine::VolumeTodb(float volume)
{
	return 20.0f * log10f(volume);
}

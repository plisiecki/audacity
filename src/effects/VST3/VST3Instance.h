#pragma once

#include <public.sdk/source/vst/utility/uid.h>

#include "effects/PerTrackEffect.h"

namespace Steinberg
{
   class IPlugView;
   class IPlugFrame;
}

class NumericTextCtrl;
class VST3ParametersWindow;

namespace VST3
{
   namespace Hosting
   {
      class Module;
   }
}

class VST3Wrapper;
class VST3Effect;

class VST3Instance
   : public PerTrackEffect::Instance
{
   VST3::UID mEffectUID;

   std::unique_ptr<VST3Wrapper> mWrapper;

   size_t mUserBlockSize { 8192 };
   size_t mProcessingBlockSize { 8192 };
   bool mUseLatency { true };
   sampleCount mInitialDelay { 0 };

public:
   VST3Instance(const PerTrackEffect& effect, VST3::Hosting::Module& module, VST3::UID effectUID);
   ~VST3Instance() override;

   VST3Instance(const VST3Instance&) = delete;
   VST3Instance& operator=(const VST3Instance&) = delete;

   size_t GetTailSize() const override;
   bool Init() override;
   bool RealtimeAddProcessor(EffectSettings& settings, unsigned numChannels, float sampleRate) override;
   bool RealtimeFinalize(EffectSettings& settings) noexcept override;
   bool RealtimeInitialize(EffectSettings& settings, double sampleRate) override;
   size_t RealtimeProcess(size_t group, EffectSettings& settings, const float* const* inBuf, float* const* outBuf,
      size_t numSamples) override;
   bool RealtimeProcessEnd(EffectSettings& settings) noexcept override;
   bool RealtimeProcessStart(EffectSettings& settings) override;
   bool RealtimeResume() override;
   bool RealtimeSuspend() override;
   SampleCount GetLatency(const EffectSettings& settings, double sampleRate)
      const override;
   bool ProcessFinalize() noexcept override;
   bool ProcessInitialize(EffectSettings &settings,
         double sampleRate, ChannelNames chanMap) override;
   size_t GetBlockSize() const override;
   size_t SetBlockSize(size_t maxBlockSize) override;
   size_t ProcessBlock(EffectSettings& settings, const float* const* inBlock, float* const* outBlock,
      size_t blockLen) override;

   VST3Wrapper& GetWrapper();

   unsigned GetAudioOutCount() const override;
   unsigned GetAudioInCount() const override;

   void ReloadUserOptions();

   void AssignSettings(EffectSettings& dst, EffectSettings&& src) const override;
};

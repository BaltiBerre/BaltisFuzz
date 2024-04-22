//mypluginprocessor.h
// Copyright(c) 2024 Baltisreverb.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

namespace MyCompanyName {

//------------------------------------------------------------------------
// BaltiReverbProcessor
//------------------------------------------------------------------------

class BaltiReverbProcessor : public Steinberg::Vst::AudioEffect
{
public:
    BaltiReverbProcessor(); // Constructor
    ~BaltiReverbProcessor() SMTG_OVERRIDE; // Destructor

    // Create function
    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (Steinberg::Vst::IAudioProcessor*)new BaltiReverbProcessor;
    }

    //--- ---------------------------------------------------------------------
    // AudioEffect overrides:
    //--- ---------------------------------------------------------------------

    /** Called at first after constructor */
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE;

    /** Called at the end before destructor */
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE;

    /** Switch the Plug-in on/off */
    Steinberg::tresult PLUGIN_API setActive(Steinberg::TBool state) SMTG_OVERRIDE;

    /** Will be called before any process call */
    Steinberg::tresult PLUGIN_API setupProcessing(Steinberg::Vst::ProcessSetup& newSetup) SMTG_OVERRIDE;

    /** Asks if a given sample size is supported see SymbolicSampleSizes. */
    Steinberg::tresult PLUGIN_API canProcessSampleSize(Steinberg::int32 symbolicSampleSize) SMTG_OVERRIDE;

    /** Here we go...the process call */
    Steinberg::tresult PLUGIN_API process(Steinberg::Vst::ProcessData& data) SMTG_OVERRIDE;

    float BaltiReverbProcessor::calculateLimiterThreshold(float bitDepth); // Function to calculate limiter threshold

    /** For persistence */
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

//------------------------------------------------------------------------
protected:
    float fFuzz = 0.5f; // Fuzz parameter
    float fDrive = 0.5f; // Drive parameter
    float fOutput = 0.5f; // Output parameter
    float fMix = 1.0f; // Mix parameter
    float fBitDepth = 1.0f; // Bit depth parameter
    double sampleRate = 0.0; // Sample rate
    float fGain = 0.0f; // Gain parameter
    float fClipThreshold = 0.7f; // Clipping threshold
    float fLimiterThreshold = 1.0f; // Limiter threshold
    float fOversamplingFactor = 4.0f; // Oversampling factor
};

//------------------------------------------------------------------------
} // namespace MyCompanyName

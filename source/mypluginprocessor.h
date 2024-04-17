//mypluginprocessor.h
// Copyright(c) 2024 Baltisreverb.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vstaudioeffect.h"

namespace MyCompanyName {

	//------------------------------------------------------------------------
	//  BaltiReverbProcessor
	//------------------------------------------------------------------------
	class BaltiReverbProcessor : public Steinberg::Vst::AudioEffect
	{
	public:
		BaltiReverbProcessor();
		~BaltiReverbProcessor() SMTG_OVERRIDE;

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
		float BaltiReverbProcessor::calculateLimiterThreshold(float bitDepth);
		/** For persistence */
		Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE;
		Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE;

		//------------------------------------------------------------------------
	protected:
		float fFuzz = 0.5f;
		float fDrive = 0.5f;
		float fOutput = 0.5f;
		float fMix = 1.0f;
		float fTone = 1.0f;
		float fBitDepth = 1.0f;

		double sampleRate = 0.0;
		float fGain = 0.0f;
		float fClipThreshold = 0.7f;
		float fLimiterThreshold = 1.0f;
		float fOversamplingFactor = 4.0f;
	};

	//------------------------------------------------------------------------
} // namespace MyCompanyName
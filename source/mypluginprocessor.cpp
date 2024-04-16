//mypluginprocessor.cpp
// Copyright(c) 2024 BaltisFuzz.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincids.h"
#include "params.h"
#include "base/source/fstreamer.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"



using namespace Steinberg;
using namespace std;
const float kBitDepthGainTable[] = {
    0.0f, 0.1f, 0.2f, 0.3f, 0.4f, 0.5f, 0.6f, 0.7f, 0.8f, 0.9f, 1.0f
};
const int kBitDepthGainTableSize = sizeof(kBitDepthGainTable) / sizeof(float);

namespace MyCompanyName {

    float BaltiReverbProcessor::calculateLimiterThreshold(float bitDepth) {
        return 0.1f + bitDepth * 0.9f;
    }

//------------------------------------------------------------------------
// BaltiFuzzProcessor
//------------------------------------------------------------------------
BaltiReverbProcessor::BaltiReverbProcessor()
{
	//--- set the wanted controller for our processor
	setControllerClass (kBaltiReverbControllerUID);
}

//------------------------------------------------------------------------
BaltiReverbProcessor::~BaltiReverbProcessor ()
{}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated
	
	//---always initialize the parent-------
	tresult result = AudioEffect::initialize (context);
	// if everything Ok, continue
	if (result != kResultOk)
	{
		return result;
	}

	//--- create Audio IO ------
	addAudioInput (STR16 ("Stereo In"), Steinberg::Vst::SpeakerArr::kStereo);
	addAudioOutput (STR16 ("Stereo Out"), Steinberg::Vst::SpeakerArr::kStereo);

	/* If you don't need an event bus, you can remove the next line */
	addEventInput (STR16 ("Event In"), 1);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!
	
	//---do not forget to call parent ------
	return AudioEffect::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::setActive (TBool state)
{
	//--- called when the Plug-in is enable/disable (On/Off) -----
	return AudioEffect::setActive (state);
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::process(Vst::ProcessData& data)
{
    //--- First : Read inputs parameter changes-----------
    if (data.inputParameterChanges)
    {
        int32 numParamsChanged = data.inputParameterChanges->getParameterCount();
        for (int32 index = 0; index < numParamsChanged; index++)
        {
            if (auto* paramQueue = data.inputParameterChanges->getParameterData(index))
            {
                Vst::ParamValue value;
                int32 sampleOffset;
                int32 numPoints = paramQueue->getPointCount();
                if (paramQueue->getPoint(numPoints - 1, sampleOffset, value) == kResultTrue) {
                    switch (paramQueue->getParameterId())
                    {
                    case kFuzzId:
                        fFuzz = (float)value;
                        break;
                    case kDriveId:
                        fDrive = (float)value;
                        break;
                    case kOutputId:
                        fOutput = (float)value;
                        break;
                    case kMixId:
                        fMix = (float)value;
                        break;
                    case kToneId:
                        fTone = (float)value;
                        break;
                    case kBitDepthId:
                        fBitDepth = (float)value;
                        break;
                    case kSampleRateId:
                        fSampleRate = (float)value;
                        break;
                    }
                }
            }
        }
    }

    //--- Here you have to implement your processing
    if (data.numInputs == 0 || data.numOutputs == 0) {
        return kResultOk;
    }

    int32 numChannels = data.inputs[0].numChannels;
    Vst::Sample32** in = data.inputs[0].channelBuffers32;
    Vst::Sample32** out = data.outputs[0].channelBuffers32;

   
    for (int32 ch = 0; ch < numChannels; ch++)
    {
        Vst::Sample32* pIn = in[ch];
        Vst::Sample32* pOut = out[ch];
        Vst::Sample32 tmp;

        for (int32 i = 0; i < data.numSamples; i++) {
            tmp = *pIn * (1.0f + fDrive * 10.0f);
            tmp = tanh(tmp * (1.0f + fFuzz * 5.0f));

            // Apply soft clipping with adjusted threshold and clipping curve
            float threshold = 0.7;
            if (tmp > threshold) {
                tmp = threshold + (1.0 - threshold) * tanh((tmp - threshold) / (1.0 - threshold));
            }
            else if (tmp < -threshold) {
                tmp = -threshold + (1.0 - threshold) * tanh((tmp + threshold) / (1.0 - threshold));
            }

            // Apply bitcrusher effect
            float bitDepth = pow(2.0f, fBitDepth * 16.0f);
            float limiterThreshold = calculateLimiterThreshold(fBitDepth);
            float crushedSample = floor(tmp * bitDepth) / bitDepth;

            // Apply limiter
            if (crushedSample > limiterThreshold) {
                crushedSample = limiterThreshold + (crushedSample - limiterThreshold) / (bitDepth - limiterThreshold + 1.0f);
            }
            else if (crushedSample < -limiterThreshold) {
                crushedSample = -limiterThreshold + (crushedSample + limiterThreshold) / (bitDepth - limiterThreshold + 1.0f);
            }

            *pOut = ((*pIn * (1.0f - fMix)) + (crushedSample * fMix) * fOutput);

            float outputGain = 1.5f; // Adjust this value to control the overall output gain
            *pOut = *pOut * outputGain;

            pIn++;
            pOut++;            
        }
    }


    return kResultOk;
} 




//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::setupProcessing (Vst::ProcessSetup& newSetup)
{
	//--- called before any processing ----

	sampleRate = newSetup.sampleRate;
	return AudioEffect::setupProcessing (newSetup);
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::canProcessSampleSize (int32 symbolicSampleSize)
{
	// by default kSample32 is supported
	if (symbolicSampleSize == Vst::kSample32)
		return kResultTrue;

	// disable the following comment if your processing support kSample64
	/* if (symbolicSampleSize == Vst::kSample64)
		return kResultTrue; */

	return kResultFalse;
}




//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::setState (IBStream* state)
{
	// called when we load a preset, the model has to be reloaded
	IBStreamer streamer (state, kLittleEndian);
    if (!state)
        return kResultFalse;

    float savedFuzz = 0.0f;
    if (streamer.readFloat(savedFuzz) == false)
        return kResultFalse;
    fFuzz = savedFuzz;

    float savedDrive = 0.0f;
    if (streamer.readFloat(savedDrive) == false)
        return kResultFalse;
    fDrive = savedDrive;

    float savedOutput = 0.0f;
    if (streamer.readFloat(savedOutput) == false)
        return kResultFalse;
    fOutput = savedOutput;

    float savedMix = 0.0f;
    if (streamer.readFloat(savedMix) == false)
        return kResultFalse;
    fMix = savedMix;

    float savedTone = 0.0f;
    if (streamer.readFloat(savedTone) == false)
        return kResultFalse;
    fTone = savedTone;

    float savedBitDepth = 0.0f;
    if (streamer.readFloat(savedBitDepth) == false)
        return kResultFalse;
    fBitDepth = savedBitDepth;

    float savedSampleRate = 0.0f;
    if (streamer.readFloat(savedSampleRate) == false)
        return kResultFalse;

    fSampleRate = savedSampleRate;

	
	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbProcessor::getState (IBStream* state)
{

    // Save the model of your plug-in
    IBStreamer streamer(state, kLittleEndian);
    streamer.writeFloat(fFuzz);
    streamer.writeFloat(fDrive);
    streamer.writeFloat(fOutput);
    streamer.writeFloat(fMix);
    streamer.writeFloat(fTone);
    streamer.writeFloat(fBitDepth);
    streamer.writeFloat(fSampleRate);


	return kResultOk;
}

//------------------------------------------------------------------------
} // namespace BaltiFuzz

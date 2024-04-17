// myplugincontroller.cpp
// Copyright(c) 2024 BaltisFuzz.
//------------------------------------------------------------------------

#include "myplugincontroller.h"
#include "myplugincids.h"
#include "params.h"
#include "vstgui/plugin-bindings/vst3editor.h"
#include "pluginterfaces/base/ibstream.h"
#include "pluginterfaces/base/ustring.h"

using Steinberg::IBStreamer;

using namespace Steinberg;

namespace MyCompanyName {

//------------------------------------------------------------------------
// Balti
// 
// 
// 
// 
// 
// 
// 
// 
// Controller Implementation
//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbController::initialize (FUnknown* context)
{
	// Here the Plug-in will be instantiated

	//---do not forget to call parent ------
	tresult result = EditControllerEx1::initialize (context);
	if (result != kResultOk)
	{
		return result;
	}

	// Here you could register some parameters
	parameters.addParameter(STR16("Fuzz"), nullptr, 0, 0.5, Vst::ParameterInfo::kCanAutomate, kFuzzId);
	parameters.addParameter(STR16("Drive"), nullptr, 0, 0.5, Vst::ParameterInfo::kCanAutomate, kDriveId);
	parameters.addParameter(STR16("Output"), nullptr, 0, 0.5, Vst::ParameterInfo::kCanAutomate, kOutputId);
	parameters.addParameter(STR16("Mix"), nullptr, 0, 1, Vst::ParameterInfo::kCanAutomate, kMixId);
	parameters.addParameter(STR16("Tone"), nullptr, 0, 1, Vst::ParameterInfo::kCanAutomate, kToneId);
	parameters.addParameter(STR16("BitDepth"), nullptr, 0, 1, Vst::ParameterInfo::kCanAutomate, kBitDepthId);
	parameters.addParameter(STR16("Gain"), nullptr, 0, 0.5, Vst::ParameterInfo::kCanAutomate, kOutputGainId);
	

	return result;
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbController::terminate ()
{
	// Here the Plug-in will be de-instantiated, last possibility to remove some memory!

	//---do not forget to call parent ------
	return EditControllerEx1::terminate ();
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbController::setComponentState(IBStream* state)
{
	if (!state)
		return kResultFalse;

	float savedFuzz = 0.0f;
	if (state->read(&savedFuzz, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kFuzzId, savedFuzz);

	float savedDrive = 0.0f;
	if (state->read(&savedDrive, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kDriveId, savedDrive);

	float savedOutput = 0.0f;
	if (state->read(&savedOutput, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kOutputId, savedOutput);

	float savedMix = 0.0f;
	if (state->read(&savedMix, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kMixId, savedMix);

	float savedTone = 0.0f;
	if (state->read(&savedTone, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kToneId, savedTone);

	float savedBitDepth = 0.0f;
	if (state->read(&savedBitDepth, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kBitDepthId, savedBitDepth);

	float savedSampleRate = 0.0f;
	if (state->read(&savedSampleRate, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kSampleRateId, savedSampleRate);

	float savedGain = 0.0f;
	if (state->read(&savedGain, sizeof(float)) != kResultOk)
		return kResultFalse;
	setParamNormalized(kOutputGainId, savedGain);

	return kResultOk;
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbController::setState (IBStream* state)
{
	// Here you get the state of the controller

	return kResultTrue;
}

//------------------------------------------------------------------------
tresult PLUGIN_API BaltiReverbController::getState (IBStream* state)
{
	// Here you are asked to deliver the state of the controller (if needed)
	// Note: the real state of your plug-in is saved in the processor

	return kResultTrue;
}

//------------------------------------------------------------------------
IPlugView* PLUGIN_API BaltiReverbController::createView (FIDString name)
{
	// Here the Host wants to open your editor (if you have one)
	if (FIDStringsEqual (name, Vst::ViewType::kEditor))
	{
		// create your editor here and return a IPlugView ptr of it
		auto* view = new VSTGUI::VST3Editor (this, "view", "myplugineditor.uidesc");
		return view;
	}
	return nullptr;
}

//------------------------------------------------------------------------
} // namespace MyCompanyName

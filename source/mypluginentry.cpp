//------------------------------------------------------------------------
// Copyright(c) 2024 Baltisreverb.
//------------------------------------------------------------------------

#include "mypluginprocessor.h"
#include "myplugincontroller.h"
#include "myplugincids.h"
#include "version.h"
#include "public.sdk/source/main/pluginfactory.h"

#define stringPluginName "BaltiReverb"

using namespace Steinberg::Vst;
using namespace MyCompanyName;

//------------------------------------------------------------------------
// VST Plug-in Entry
//------------------------------------------------------------------------

// Define the factory for the plugin
BEGIN_FACTORY_DEF("Baltisreverb", "baltisreverb", "mailto:baltisreverb")

//---First Plug-in included in this factory-------

// Define the audio effect processor component
DEF_CLASS2(INLINE_UID_FROM_FUID(kBaltiReverbProcessorUID),
           PClassInfo::kManyInstances, // Cardinality (allows multiple instances)
           kVstAudioEffectClass, // Component category (audio effect)
           stringPluginName, // Plugin name
           Vst::kDistributable, // Distributable (component and controller can be on different computers)
           BaltiReverbVST3Category, // Plugin subcategory
           FULL_VERSION_STR, // Plugin version
           kVstVersionString, // VST 3 SDK version
           BaltiReverbProcessor::createInstance) // Function to create an instance of the processor

// Define the controller component
DEF_CLASS2(INLINE_UID_FROM_FUID(kBaltiReverbControllerUID),
           PClassInfo::kManyInstances, // Cardinality (allows multiple instances)
           kVstComponentControllerClass, // Component category (controller)
           stringPluginName "Controller", // Controller name
           0, // Not used
           "", // Not used
           FULL_VERSION_STR, // Plugin version
           kVstVersionString, // VST 3 SDK version
           BaltiReverbController::createInstance) // Function to create an instance of the controller

//----for others Plug-ins contained in this factory, put like for the first Plug-in different DEF_CLASS2---

END_FACTORY

//------------------------------------------------------------------------
// Copyright(c) 2024 Baltisreverb.
//------------------------------------------------------------------------

#pragma once

#include "public.sdk/source/vst/vsteditcontroller.h"

namespace Steinberg {
    class IBStream;
    class IBStreamer;
}

namespace MyCompanyName {

//------------------------------------------------------------------------
// BaltiReverbController
//------------------------------------------------------------------------

class BaltiReverbController : public Steinberg::Vst::EditControllerEx1
{
public:
    //------------------------------------------------------------------------
    BaltiReverbController() = default; // Default constructor
    ~BaltiReverbController() SMTG_OVERRIDE = default; // Default destructor

    // Create function
    static Steinberg::FUnknown* createInstance(void* /*context*/)
    {
        return (Steinberg::Vst::IEditController*)new BaltiReverbController;
    }

    //--- from IPluginBase -----------------------------------------------
    Steinberg::tresult PLUGIN_API initialize(Steinberg::FUnknown* context) SMTG_OVERRIDE; // Initialize the controller
    Steinberg::tresult PLUGIN_API terminate() SMTG_OVERRIDE; // Terminate the controller

    //--- from EditController --------------------------------------------
    Steinberg::tresult PLUGIN_API setComponentState(Steinberg::IBStream* state) SMTG_OVERRIDE; // Set the controller's state from a stream
    Steinberg::IPlugView* PLUGIN_API createView(Steinberg::FIDString name) SMTG_OVERRIDE; // Create the plugin's view (editor)
    Steinberg::tresult PLUGIN_API setState(Steinberg::IBStream* state) SMTG_OVERRIDE; // Set the controller's state from a stream
    Steinberg::tresult PLUGIN_API getState(Steinberg::IBStream* state) SMTG_OVERRIDE; // Get the controller's state to a stream

    //---Interface---------
    DEFINE_INTERFACES
        // Here you can add more supported VST3 interfaces
        // DEF_INTERFACE (Vst::IXXX)
    END_DEFINE_INTERFACES(EditController)
    DELEGATE_REFCOUNT(EditController)

//------------------------------------------------------------------------
protected:
};

//------------------------------------------------------------------------
} // namespace MyCompanyName

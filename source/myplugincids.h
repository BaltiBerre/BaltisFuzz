//------------------------------------------------------------------------
// Copyright(c) 2024 Baltisreverb.
//------------------------------------------------------------------------

#pragma once

#include "pluginterfaces/base/funknown.h"
#include "pluginterfaces/vst/vsttypes.h"

namespace MyCompanyName {
//------------------------------------------------------------------------
static const Steinberg::FUID kBaltiReverbProcessorUID (0xF31F083C, 0x088B5952, 0xA2FDF85B, 0xD525B3B5);
static const Steinberg::FUID kBaltiReverbControllerUID (0x8F0BFA20, 0xFE885824, 0xAC416769, 0xFDB73953);

#define BaltiReverbVST3Category "Fx"

//------------------------------------------------------------------------
} // namespace MyCompanyName

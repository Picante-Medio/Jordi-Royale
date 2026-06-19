# pragma once

#include "HugoComponentMacros.h"
#include "HugoTypes.h"

HCOMPONENT(DynamicAudioComponent)
    DEFAULT_SERIALIZED_MEMBER(float, maxVolume, 1.0f);
    DEFAULT_SERIALIZED_MEMBER(float, minVolume, .0f);
    DEFAULT_SERIALIZED_MEMBER(std::string, audioName, "");
    DEFAULT_SERIALIZED_MEMBER(float, interpolationMiliseconds, 1500.0f);
END_HCOMPONENT()

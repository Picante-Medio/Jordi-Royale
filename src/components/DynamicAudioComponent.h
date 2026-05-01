#include "HugoComponentMacros.h"
#include "HugoTypes.h"

HCOMPONENT(DynamicAudioComponent)
    DEFAULT_SERIALIZED_MEMBER(HUGO::Float, maxVolume, 1.0f);
    DEFAULT_SERIALIZED_MEMBER(HUGO::Float, minVolume, .0f);
    DEFAULT_SERIALIZED_MEMBER(HUGO::String, audioName, "");
    DEFAULT_SERIALIZED_MEMBER(HUGO::Float, interpolationMiliseconds, 1500.0f);
END_HCOMPONENT()

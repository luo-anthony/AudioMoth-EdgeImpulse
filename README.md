# AudioMoth-EdgeImpulse

### *Currently under development* ###

A modified version of the [AudioMoth standard firmware](https://github.com/OpenAcousticDevices/AudioMoth-Project). This software performs live classification of samples using a neural network from Edge Impulse and saves audio clips containing a specific sound.

To build this firmware, see the steps under the regular firmware. 

This firmware is based off of [SmartMoth](https://github.com/leocorne/AudioMoth-Project) by [Leo](https://github.com/leocorne).

## Steps to Change Edge Impulse Models ##

1. Train a different neural network (using MFCC for audio) on the Edge Impulse platform. Go to the "Deployment" tab, build the C++ library, and download the ZIP file (and unzip it)
2. Replace the `model-parameters` folder in `firmware/ei_library/` with the `model-parameters` folder from the Edge Impulse ZIP folder generated. 
3. Replace the `tflite-model` folder in `firmware/ei_library/` with the `tflite-model` folder from the Edge Impulse ZIP folder generated.
4. In `firmware/ei_library/tflite-model/trained_model_compiled.cpp`, replace the line `#include "edge-impulse-sdk/porting/ei_classifier_porting.h"` with`#include "edge-impulse-sdk/porting_audiomoth/ei_classifier_porting.h"`

*TODO: Clean up this changing of Edge Impulse Models*

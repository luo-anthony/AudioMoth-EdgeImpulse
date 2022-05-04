# AudioMoth-EdgeImpulse

### *Currently under development* ###

A modified version of the [AudioMoth standard firmware](https://github.com/OpenAcousticDevices/AudioMoth-Project). This software performs live classification of samples using a neural network from Edge Impulse and saves audio clips containing a specific sound.

To build this firmware, see the steps under the regular firmware. 

This firmware is based off of [SmartMoth](https://github.com/leocorne/AudioMoth-Project) by [Leo](https://github.com/leocorne).

## Steps to Change Edge Impulse Models ##

1. Train a different neural network (using MFCC for audio) on the Edge Impulse platform. Go to the "Deployment" tab, build the C++ library, and download the ZIP file (and unzip it). 
2. In the `firmware/Makefile` set the `EI_MODELPATH =` variable to the path of the Edge Impulse ZIP Model folder
3. Run `make clean` and `make` to build the firmware with the new model 
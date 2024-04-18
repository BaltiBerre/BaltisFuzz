# SolUru VST3 Plugin

SolUru is a VST3 audio effect plugin that provides a versatile fuzz and bitcrushing effect. It allows you to apply fuzz, drive, bit depth reduction, and gain to your audio signal, creating unique and gritty tones.

## Features
- **Fuzz:** Adjust the amount of fuzz applied to the signal.
- **Drive:** Control the amount of drive or distortion.
- **Output:** Set the output level of the processed signal.
- **Mix:** Blend between the dry (unprocessed) and wet (processed) signals.
- **Bit Depth:** Reduce the bit depth of the signal for a lo-fi, bitcrushed effect.
- **Gain:** Adjust the overall output gain of the plugin.

## Installation
1. Clone the repository or download the source code.
2. Make sure you have the VST3 SDK installed and the path to the SDK is correctly set in the CMakeLists.txt file.
3. Open the project in your preferred C++ IDE.
4. Build the project to generate the VST3 plugin binary.
5. Copy the generated VST3 plugin file to your system's VST3 plugin directory.

## Usage
1. Open your VST3-compatible digital audio workstation (DAW).
2. Create a new track or select an existing track where you want to use the SolUru plugin.
3. Load the SolUru VST3 plugin on the track.
4. Adjust the plugin parameters to achieve the desired fuzz and bitcrushing effect:
   - **Fuzz:** Increase the fuzz amount to add more distortion and grit to the signal.
   - **Drive:** Increase the drive to add more saturation and distortion.
   - **Output:** Adjust the output level to control the overall volume of the processed signal.
   - **Mix:** Blend between the dry and wet signals to balance the amount of the effect.
   - **Bit Depth:** Lower the bit depth to introduce quantization noise and create a lo-fi sound.
   - **Gain:** Adjust the overall output gain to compensate for any volume changes introduced by the effect.
5. Experiment with different parameter settings to create unique and interesting tones.

## Code Structure
The SolUru plugin consists of the following main files:
- **mypluginprocessor.h** and **mypluginprocessor.cpp:** Contain the audio processing logic for the plugin.
- **myplugincontroller.h** and **myplugincontroller.cpp:** Implement the plugin's parameter handling and user interface.
- **myplugincids.h:** Defines the unique identifiers for the plugin.
- **mypluginentry.cpp:** Entry point for the VST3 plugin.
- **version.h:** Contains version information for the plugin.
- **CMakeLists.txt:** CMake build configuration file.
The code follows the VST3 SDK architecture and utilizes VSTGUI for the plugin's user interface.

## Dependencies
- **VST3 SDK:** The plugin is built using the VST3 SDK, which provides the necessary frameworks and libraries for developing VST3 plugins.
- **VSTGUI:** The plugin uses VSTGUI for creating the user interface elements.
- **BaltiReverb:** While not reverb when the bitdepth parameter is close to zero it has a high propensity to it.

## License
This project is licensed under the [license].
![image](https://github.com/BaltiBerre/BaltisFuzz/assets/119361606/7a98f532-7f0f-4ced-8071-a2a0fb383f0b)

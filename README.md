# VocoderSynthBWidgets ![GPL license logo!](https://www.gnu.org/graphics/gplv3-or-later.png)

![Screenshot of VocoderSynth.!](https://github.com/TimKrause2/VocoderSynthBWidgets/blob/main/screenshot.png "VocoderSynth with BWidgets.")

## Description

VocoderSynth LV2 plugin is a Linear Predictive Coding based
vocoder with 3 selectable modules: raw audio, a voice
controlled impulse and noise generator and a MIDI
controlled synth of impulse generators with an ADSR.

## Controls

- **Raw Enable** controls the raw audio input.
- **Voice Enable** controls the voice controlled impulse and noise generator.
- **Impulse** sets the gain of the impulses in dB.
- **Noise** sets the gain of the noise in dB.
- **Pitch Shift** sets the pitch offset of the impulse generator in semitones.
- **Synth Enable** controls the MIDI impulse generator synth.
- **Gain** sets the gain of the MIDI synth in dB.
- **Bend** sets the pitch bend range of the MIDI synth in semitones.
- **Attack** sets attack time in seconds.
- **Decay** sets decay time in seconds.
- **Sustain** sets sustain level in percent.
- **Release** sets release time in seconds.

## Inputs

- **Control Audio In** This input is analysed and used to determine the filter of the Vocoder and the pitch of the voice module.
- **Raw Audio In** This input is filtered by the Vocoder.
- **MIDI In** This input is a MIDI input that controls the synthesizer.

## Use in Ardour

Use the following steps to setup VocoderSynth in Ardour.

1. Create or select a mono track.
2. Insert a VocoderSynth plugin.
3. Open the pin connections dialog.
4. Enable sidechains.
5. Add a MIDI sidechain.
6. Connect the inputs to the sidechains.
7. Select the sidechain sources.

To edit the dial values with the keyboard click on the keyboard icon in the top right hand corner of the plugin window.
When you are done editing click the keyboard icon again to use the keyboard in Ardour.

## Building Prerequisites

In order to build VocoderSynth you need these prerequisites.

- g++ and gcc
- libcairo2-dev
- libx11-dev
- lv2-dev
- make
- pkg-config
- git

On Ubuntu this can be done by the following.

```
sudo apt install g++ gcc make libcairo2-dev libx11-dev lv2-dev pkg-config git
```

## Clone and make

In a terminal enter the following.

```
git clone https://github.com/TimKrause2/VocoderSynthBWidgets.git
cd VocoderSynthBWidgets
make
make install
```

The install directory is `.lv2` in your home directory.



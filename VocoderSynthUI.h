/*
VocoderSynth is a DSP plugin.

Copyright 2024 Tim Krause

This file is part of VocoderSynth

VocoderSynth is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published
by the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

VocoderSynth is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with VocoderSynth. If not, see
<https://www.gnu.org/licenses/>.

Contact: tim.krause@twkrause.ca

*/
#pragma once

#include <string>
#include <lv2/lv2plug.in/ns/lv2core/lv2.h>
#include <lv2/lv2plug.in/ns/extensions/ui/ui.h>
#include "BWidgets/BEvents/Event.hpp"
#include "BWidgets/BEvents/ExposeEvent.hpp"
#include "BWidgets/BEvents/ValueChangeTypedEvent.hpp"
#include "BWidgets/BEvents/ExposeEvent.hpp"
#include "BWidgets/BWidgets/Window.hpp"
#include "BWidgets/BWidgets/Label.hpp"
#include "BWidgets/BWidgets/CheckBox.hpp"
#include "BWidgets/BWidgets/ValueDial.hpp"

#include "VocoderSynth.h"

#define WINDOW_RESIZABLE true
#define LABEL_WIDTH 80
#define LABEL_HEIGHT 20
#define CK_BX_WIDTH 20
#define CK_BX_HEIGHT 20
#define VL_DL_WIDTH 60
#define VL_DL_HEIGHT 75
#define BORDER 10
#define CK_BX_Y             BORDER
#define CK_BX_LABEL_Y      (CK_BX_Y+CK_BX_HEIGHT)
#define VL_DL_ROW1_Y       (CK_BX_LABEL_Y+LABEL_HEIGHT)
#define VL_DL_LABEL_ROW1_Y (VL_DL_ROW1_Y+VL_DL_HEIGHT)
#define VL_DL_ROW2_Y       (VL_DL_LABEL_ROW1_Y+LABEL_HEIGHT)
#define VL_DL_LABEL_ROW2_Y (VL_DL_ROW2_Y+VL_DL_HEIGHT)
#define WINDOW_HEIGHT      (VL_DL_LABEL_ROW2_Y+LABEL_HEIGHT+BORDER)

#define COL1_X BORDER
#define COL2_X (COL1_X + LABEL_WIDTH)
#define COL3_X (COL2_X + LABEL_WIDTH*2)
#define WINDOW_WIDTH (COL3_X + LABEL_WIDTH + BORDER)
#define COL1_CNTR (COL1_X + LABEL_WIDTH/2)
#define COL1_CK_BX_X (COL1_CNTR - CK_BX_WIDTH/2)
#define COL1_LABEL_X (COL1_CNTR - LABEL_WIDTH/2)
#define COL2_CNTR (COL2_X + LABEL_WIDTH)
#define COL2_CK_BX_X (COL2_CNTR - CK_BX_WIDTH/2)
#define COL2_LABEL_X (COL2_CNTR - LABEL_WIDTH/2)
#define COL2_VL_DL_X (COL2_CNTR - VL_DL_WIDTH/2)
#define COL2A_X (COL2_X)
#define COL2B_X (COL2_X + LABEL_WIDTH)
#define COL2A_CNTR (COL2A_X + LABEL_WIDTH/2)
#define COL2B_CNTR (COL2B_X + LABEL_WIDTH/2)
#define COL2A_VL_DL_X (COL2A_CNTR - VL_DL_WIDTH/2)
#define COL2A_LABEL_X (COL2A_CNTR - LABEL_WIDTH/2)
#define COL2B_VL_DL_X (COL2B_CNTR - VL_DL_WIDTH/2)
#define COL2B_LABEL_X (COL2B_CNTR - LABEL_WIDTH/2)
#define COL3_CNTR (COL3_X + LABEL_WIDTH/2)
#define COL3_CK_BX_X (COL3_CNTR - CK_BX_WIDTH/2)
#define COL3_VL_DL_X (COL3_CNTR - VL_DL_WIDTH/2)
#define COL3_LABEL_X (COL3_CNTR - LABEL_WIDTH/2)

#define RAW_STATE   true
#define VOICE_STATE false
#define SYNTH_STATE false

#define VC_IMP_VALUE 25.0
#define VC_IMP_MIN 0.0
#define VC_IMP_MAX 30.0
#define VC_IMP_STEP 0.1

#define VC_NSE_VALUE 3.0
#define VC_NSE_MIN 0.0
#define VC_NSE_MAX 30.0
#define VC_NSE_STEP 0.1

#define VC_PTC_VALUE 0.0
#define VC_PTC_MIN -12.0
#define VC_PTC_MAX 12.0
#define VC_PTC_STEP 0.25

#define SN_GAN_VALUE 10.0
#define SN_GAN_MIN 0.0
#define SN_GAN_MAX 30.0
#define SN_GAN_STEP 0.1

#define SN_BND_VALUE 0.0
#define SN_BND_MIN 0.0
#define SN_BND_MAX 12.0
#define SN_BND_STEP 0.25

class VocoderSynthUI : public BWidgets::Window
{
private:
    LV2UI_Write_Function write_function;
    LV2UI_Controller controller;
    BWidgets::Label raw_enable_label;
    BWidgets::Label voice_enable_label;
    BWidgets::Label synth_enable_label;
    BWidgets::Label voice_impulse_label;
    BWidgets::Label voice_noise_label;
    BWidgets::Label voice_pitch_label;
    BWidgets::Label synth_gain_label;
    BWidgets::Label synth_bend_label;
    BWidgets::CheckBox raw_enable;
    BWidgets::CheckBox voice_enable;
    BWidgets::CheckBox synth_enable;
    BWidgets::ValueDial voice_impulse;
    BWidgets::ValueDial voice_noise;
    BWidgets::ValueDial voice_pitch;
    BWidgets::ValueDial synth_gain;
    BWidgets::ValueDial synth_bend;

public:
    VocoderSynthUI (LV2UI_Write_Function write_function, LV2UI_Controller controller, void* parentXWindow, std::string bundlePath);
    ~VocoderSynthUI();
    LV2UI_Widget getTopLevelWidget();
    void portEvent(uint32_t port_index, uint32_t buffer_size, uint32_t format, const void *buffer);
    static void configureCallback(BEvents::Event* event);
    static void raw_enable_callback(BEvents::Event* event);
    static void voice_enable_callback(BEvents::Event* event);
    static void voice_impulse_callback(BEvents::Event* event);
    static void voice_noise_callback(BEvents::Event* event);
    static void voice_pitch_callback(BEvents::Event* event);
    static void synth_enable_callback(BEvents::Event* event);
    static void synth_gain_callback(BEvents::Event* event);
    static void synth_bend_callback(BEvents::Event* event);
};

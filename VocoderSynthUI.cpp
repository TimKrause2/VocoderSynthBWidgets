/*
VocoderSynth is a DSP plugin.

Copyright 2024-2025 Tim Krause

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
#include <iostream>
#include "VocoderSynthUI.h"
#include <stdexcept>

VocoderSynthUI::VocoderSynthUI (
    LV2UI_Write_Function write_function,
    LV2UI_Controller controller,
    void* parentXWindow,
    std::string bundlePath)
:
    Window (WINDOW_WIDTH, WINDOW_HEIGHT, 
        reinterpret_cast<PuglNativeView>(parentXWindow),
        BUTILITIES_URID_UNKNOWN_URID, 
        "VocoderSynth",
        WINDOW_RESIZABLE, PUGL_MODULE, 0),
    write_function(write_function),
    controller(controller),
    raw_enable_label(COL1_LABEL_X, CK_BX_LABEL_Y, LABEL_WIDTH, LABEL_HEIGHT, "Raw"),
    voice_enable_label(COL2_LABEL_X, CK_BX_LABEL_Y, LABEL_WIDTH, LABEL_HEIGHT, "Voice"),
    synth_enable_label(COL3_LABEL_X, CK_BX_LABEL_Y, LABEL_WIDTH, LABEL_HEIGHT, "Synth"),
    voice_impulse_label(COL2A_LABEL_X, VL_DL_LABEL_ROW1_Y, LABEL_WIDTH, LABEL_HEIGHT, "Impulse"),
    voice_noise_label(COL2B_LABEL_X, VL_DL_LABEL_ROW1_Y, LABEL_WIDTH, LABEL_HEIGHT, "Noise"),
    voice_pitch_label(COL2_LABEL_X, VL_DL_LABEL_ROW2_Y, LABEL_WIDTH, LABEL_HEIGHT, "Pitch"),
    synth_gain_label(COL3A_LABEL_X, VL_DL_LABEL_ROW1_Y, LABEL_WIDTH, LABEL_HEIGHT, "Gain"),
    synth_bend_label(COL3A_LABEL_X, VL_DL_LABEL_ROW2_Y, LABEL_WIDTH, LABEL_HEIGHT, "Bend"),
    synth_attack_label(COL3B_LABEL_X, VL_DL_LABEL_ROW1_Y, LABEL_WIDTH, LABEL_HEIGHT, "Attack"),
    synth_decay_label(COL3C_LABEL_X, VL_DL_LABEL_ROW1_Y, LABEL_WIDTH, LABEL_HEIGHT, "Decay"),
    synth_sustain_label(COL3B_LABEL_X, VL_DL_LABEL_ROW2_Y, LABEL_WIDTH, LABEL_HEIGHT, "Sustain"),
    synth_release_label(COL3C_LABEL_X, VL_DL_LABEL_ROW2_Y, LABEL_WIDTH, LABEL_HEIGHT, "Release"),
    raw_enable(COL1_CK_BX_X, CK_BX_Y, CK_BX_WIDTH, CK_BX_HEIGHT, true, RAW_STATE),
    voice_enable(COL2_CK_BX_X, CK_BX_Y, CK_BX_WIDTH, CK_BX_HEIGHT, true, VOICE_STATE),
    synth_enable(COL3_CK_BX_X, CK_BX_Y, CK_BX_WIDTH, CK_BX_HEIGHT, true, SYNTH_STATE),
    voice_impulse(COL2A_VL_DL_X, VL_DL_ROW1_Y, VL_DL_WIDTH, VL_DL_HEIGHT, VC_IMP_VALUE, VC_IMP_MIN, VC_IMP_MAX, VC_IMP_STEP),
    voice_noise(COL2B_VL_DL_X, VL_DL_ROW1_Y, VL_DL_WIDTH, VL_DL_HEIGHT, VC_NSE_VALUE, VC_NSE_MIN, VC_NSE_MAX, VC_NSE_STEP),
    voice_pitch(COL2_VL_DL_X, VL_DL_ROW2_Y, VL_DL_WIDTH, VL_DL_HEIGHT, VC_PTC_VALUE, VC_PTC_MIN, VC_PTC_MAX, VC_PTC_STEP),
    synth_gain(COL3A_VL_DL_X, VL_DL_ROW1_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_GAN_VALUE, SN_GAN_MIN, SN_GAN_MAX, SN_GAN_STEP),
    synth_bend(COL3A_VL_DL_X, VL_DL_ROW2_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_BND_VALUE, SN_BND_MIN, SN_BND_MAX, SN_BND_STEP),
    synth_attack(COL3B_VL_DL_X, VL_DL_ROW1_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_ATK_VALUE, SN_ATK_MIN, SN_ATK_MAX, SN_ATK_STEP),
    synth_decay(COL3C_VL_DL_X, VL_DL_ROW1_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_DCY_VALUE, SN_DCY_MIN, SN_DCY_MAX, SN_DCY_STEP),
    synth_sustain(COL3B_VL_DL_X, VL_DL_ROW2_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_STN_VALUE, SN_STN_MIN, SN_STN_MAX, SN_STN_STEP),
    synth_release(COL3C_VL_DL_X, VL_DL_ROW2_Y, VL_DL_WIDTH, VL_DL_HEIGHT, SN_RLS_VALUE, SN_RLS_MIN, SN_RLS_MAX, SN_RLS_STEP)
{
    raw_enable.setTitle("Raw enable");
    voice_enable.setTitle("Voice controlled enable");
    synth_enable.setTitle("Synth enable");
    voice_impulse.setTitle("Impulse gain(dB)");
    voice_noise.setTitle("Noise gain(dB)");
    voice_pitch.setTitle("Pitch offset(semitones)");
    synth_gain.setTitle("Synth impulse gain(dB)");
    synth_bend.setTitle("Synth bender range(semitones)");
    synth_attack.setTitle("Synth attack(seconds)");
    synth_decay.setTitle("Synth decay(seconds)");
    synth_sustain.setTitle("Synth sustain(percentage)");
    synth_release.setTitle("Synth release(seconds)");

    setCallbackFunction(
        BEvents::Event::EventType::configureRequestEvent,
        configureCallback);

    raw_enable.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        raw_enable_callback);

    voice_enable.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        voice_enable_callback);

    synth_enable.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_enable_callback);

    voice_impulse.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        voice_impulse_callback);

    voice_noise.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        voice_noise_callback);

    voice_pitch.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        voice_pitch_callback);

    synth_gain.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_gain_callback);

    synth_bend.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_bend_callback);

    synth_attack.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_attack_callback);

    synth_decay.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_decay_callback);

    synth_sustain.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_sustain_callback);

    synth_release.setCallbackFunction(
        BEvents::Event::EventType::valueChangedEvent,
        synth_release_callback);

    voice_impulse.setClickable(false);
    voice_noise.setClickable(false);
    voice_pitch.setClickable(false);
    synth_gain.setClickable(false);
    synth_bend.setClickable(false);
    synth_attack.setClickable(false);
    synth_decay.setClickable(false);
    synth_sustain.setClickable(false);
    synth_release.setClickable(false);

    BStyles::Font labelFont("sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL, 12.0, BStyles::Font::TextAlign::center, BStyles::Font::TextVAlign::middle);
    raw_enable_label.setFont(labelFont);
    voice_enable_label.setFont(labelFont);
    synth_enable_label.setFont(labelFont);
    voice_impulse_label.setFont(labelFont);
    voice_noise_label.setFont(labelFont);
    voice_pitch_label.setFont(labelFont);
    synth_gain_label.setFont(labelFont);
    synth_bend_label.setFont(labelFont);
    synth_attack_label.setFont(labelFont);
    synth_decay_label.setFont(labelFont);
    synth_release_label.setFont(labelFont);
    synth_sustain_label.setFont(labelFont);

    add(&raw_enable_label);
    add(&voice_enable_label);
    add(&synth_enable_label);
    add(&voice_impulse_label);
    add(&voice_noise_label);
    add(&voice_pitch_label);
    add(&synth_gain_label);
    add(&synth_bend_label);
    add(&synth_attack_label);
    add(&synth_decay_label);
    add(&synth_sustain_label);
    add(&synth_release_label);
    add(&raw_enable);
    add(&voice_enable);
    add(&synth_enable);
    add(&voice_impulse);
    add(&voice_noise);
    add(&voice_pitch);
    add(&synth_gain);
    add(&synth_bend);
    add(&synth_attack);
    add(&synth_decay);
    add(&synth_sustain);
    add(&synth_release);
}

VocoderSynthUI::~VocoderSynthUI()
{
}

LV2UI_Widget VocoderSynthUI::getTopLevelWidget()
{
    return reinterpret_cast<LV2UI_Widget>(puglGetNativeView(getView()));
}

void VocoderSynthUI::portEvent(uint32_t port_index, uint32_t buffer_size, uint32_t format, const void *buffer)
{
    if (format == 0)
    {
        const float value = *static_cast<const float*>(buffer);
        switch(port_index){
        case PORT_CONTROL + CONTROL_RAW_ENABLE:
            raw_enable.setValue(value!=0.0f);
            break;
        case PORT_CONTROL + CONTROL_VOICE_ENABLE:
            voice_enable.setValue(value!=0.0f);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_ENABLE:
            synth_enable.setValue(value!=0.0f);
            break;
        case PORT_CONTROL + CONTROL_VOICE_IMPULSE_GAIN:
            voice_impulse.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_VOICE_NOISE_GAIN:
            voice_noise.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_VOICE_PITCH_OFFSET:
            voice_pitch.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_GAIN:
            synth_gain.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_BEND_RANGE:
            synth_bend.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_ATTACK:
            synth_attack.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_DECAY:
            synth_decay.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_SUSTAIN:
            synth_sustain.setValue(value);
            break;
        case PORT_CONTROL + CONTROL_SYNTH_RELEASE:
            synth_release.setValue(value);
            break;
        default:
            break;
        }
    }
}

void VocoderSynthUI::configureCallback(BEvents::Event* event)
{
    BEvents::ExposeEvent* ev = dynamic_cast<BEvents::ExposeEvent*>(event);
    if (!ev) return;
    Window* w = dynamic_cast<Window*>(ev->getWidget());
    if (!w) return;

    double sx = ev->getArea().getWidth() / WINDOW_WIDTH;
    double sy = ev->getArea().getHeight() / WINDOW_HEIGHT;
	const double sz = (sx<sy) ? sx : sy;
	w->setZoom (sz);
}

void VocoderSynthUI::raw_enable_callback(BEvents::Event* event)
{
    BWidgets::CheckBox* d = dynamic_cast<BWidgets::CheckBox*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue()?1.0f:0.0f;
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_RAW_ENABLE,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::voice_enable_callback(BEvents::Event* event)
{
    BWidgets::CheckBox* d = dynamic_cast<BWidgets::CheckBox*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue()?1.0f:0.0f;
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_VOICE_ENABLE,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_enable_callback(BEvents::Event* event)
{
    BWidgets::CheckBox* d = dynamic_cast<BWidgets::CheckBox*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue()?1.0f:0.0f;
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_ENABLE,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::voice_impulse_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_VOICE_IMPULSE_GAIN,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::voice_noise_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_VOICE_NOISE_GAIN,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::voice_pitch_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_VOICE_PITCH_OFFSET,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_gain_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_GAIN,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_bend_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_BEND_RANGE,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_attack_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_ATTACK,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_decay_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_DECAY,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_sustain_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_SUSTAIN,
            sizeof(gain), 0, &gain);
    }
}

void VocoderSynthUI::synth_release_callback(BEvents::Event* event)
{
    BWidgets::ValueDial* d = dynamic_cast<BWidgets::ValueDial*>(event->getWidget());
    VocoderSynthUI* ui = dynamic_cast<VocoderSynthUI*>(d->getMainWindow());
    if (ui)
    {
        float gain = d->getValue();
        ui->write_function (
            ui->controller,
            PORT_CONTROL + CONTROL_SYNTH_RELEASE,
            sizeof(gain), 0, &gain);
    }
}

static LV2UI_Handle instantiate(const struct LV2UI_Descriptor *descriptor, const char *plugin_uri, const char *bundle_path, LV2UI_Write_Function write_function, LV2UI_Controller controller, LV2UI_Widget *widget, const LV2_Feature *const *features)
{
    if (strcmp (plugin_uri, "https://twkrause.ca/plugins/VocoderSynth") != 0) return nullptr;
    
    void* parentXWindow = nullptr;
    for (int i = 0; features[i]; ++i)
    {
        if (strcmp (features[i]->URI, LV2_UI__parent) == 0) parentXWindow = features[i]->data;
    }

    if (!parentXWindow)
    {
        std::cerr << "Required feature LV2_UI__parent not provided" << std::endl;
        return nullptr;
    }

    VocoderSynthUI* ui;
    try {ui = new VocoderSynthUI(write_function, controller, parentXWindow, std::string (bundle_path));}
    catch (std::exception& exc)
    {
        std::cerr << "UI instantiation failed." << std::endl;
        return nullptr;
    }

    *widget = ui->getTopLevelWidget();
    return (LV2UI_Handle) ui;
}

static void cleanup (LV2UI_Handle ui)
{
    VocoderSynthUI* myUi = static_cast<VocoderSynthUI*>(ui);
    if (myUi) delete myUi;
}

static void port_event(LV2UI_Handle ui, uint32_t port_index, uint32_t buffer_size, uint32_t format, const void *buffer)
{
    VocoderSynthUI* myUi = static_cast<VocoderSynthUI*>(ui);
    if (myUi) myUi->portEvent(port_index, buffer_size, format, buffer);
}

static int ui_idle (LV2UI_Handle ui)
{
    VocoderSynthUI* myUi = static_cast<VocoderSynthUI*>(ui);
    myUi->handleEvents();
    return 0;
}

static const void * extension_data (const char *uri)
{
    static const LV2UI_Idle_Interface idle = { ui_idle };
    if (strcmp (uri, LV2_UI__idleInterface) == 0) return &idle;
    return nullptr;
}

static const LV2UI_Descriptor ui_descriptor =
{
    "https://twkrause.ca/plugins/VocoderSynth#ui",
    instantiate,
    cleanup,
    port_event,
    extension_data
};

LV2_SYMBOL_EXPORT const LV2UI_Descriptor * 	lv2ui_descriptor (uint32_t index)
{
    switch (index)
    {
        case 0:     return &ui_descriptor;
        default:    return 0;
    }
}


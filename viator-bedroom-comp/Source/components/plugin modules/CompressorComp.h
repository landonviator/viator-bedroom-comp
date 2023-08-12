#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"

class ViatorbedroomcompAudioProcessorEditor;
class CompressorComp  : public juce::Component
, private juce::Timer
{
public:
    CompressorComp(ViatorbedroomcompAudioProcessor&, viator_dsp::Compressor<float>&, std::vector<ViatorParameters::SliderParameterData>&);
    ~CompressorComp() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    
private:
    ViatorbedroomcompAudioProcessor& audioProcessor;
    viator_dsp::Compressor<float>& compressor;
    std::vector<ViatorParameters::SliderParameterData>& sliderParams;
    
    // dials
    juce::OwnedArray<viator_gui::ImageFader> compDials;
    juce::OwnedArray<juce::AudioProcessorValueTreeState::SliderAttachment> attachments;
    void setCompDialProps();
    int getDialIndexByName(const juce::String& name);
    juce::StringArray compDialTooltips =
    {
        "Sets the amount of amplification or attenuation of signal going into the compressor",
        "Sets the amount of amplification or attenuation of signal going out of the compressor",
        "Sets how fast or slow the compressor reacts to acting on a signal.",
        "Sets how fast or slow the compressor lets go of the signal after compression.",
        "Sets the linearity of the compressor's threshold-ratio relationship.",
        "Highpass filter cutoff that only affects the signal checked by the threshold, does not filter the signal coming out of the compressor.",
        "The dB level at which the compressor will act on the signal.",
        "The amount of gain reduction multiplied by the compressor.",
        "The blend between the compressed signal and the input signal."
    };
    
    void mouseEnter(const juce::MouseEvent &event) override;
    void mouseExit(const juce::MouseEvent &event) override;
    
    viator_gui::VUMeter vuMeter;
    
    juce::GroupComponent border;
    void setBorderProps();
    viator_gui::CustomBorder borderLAF;
    
    void timerCallback() override
    {
        auto reduction = compressor.getGainReduction();
        vuMeter.getVUMeter().setValue(reduction <= 0.0 ? reduction : 0.0);
    }
    
    viator_gui::ImageButton compTypeButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> typeAttach;
    viator_gui::ImageButton compPowerButton;
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> powerAttach;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CompressorComp)
};

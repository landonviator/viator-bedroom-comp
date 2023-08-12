#pragma once
#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "components/Header.h"
#include "components/plugin modules/CompressorComp.h"

class ViatorbedroomcompAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ViatorbedroomcompAudioProcessorEditor (ViatorbedroomcompAudioProcessor&);
    ~ViatorbedroomcompAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void setTooltipText(const juce::String& tooltip);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ViatorbedroomcompAudioProcessor& audioProcessor;
    
    // comps
    Header _headerComp;
    
    CompressorComp _compressorComp;
    
    // tooltip
    viator_gui::Label _tooltipLabel;
    void initTooltipLabel();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorbedroomcompAudioProcessorEditor)
};

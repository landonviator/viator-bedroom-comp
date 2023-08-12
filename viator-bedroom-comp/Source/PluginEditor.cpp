#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorbedroomcompAudioProcessorEditor::ViatorbedroomcompAudioProcessorEditor (ViatorbedroomcompAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), _compressorComp(audioProcessor, audioProcessor.getComp(), audioProcessor._parameterMap.getComp1SliderParams())
{
    // header
    addAndMakeVisible(_headerComp);
    
    // compressor comps
    addAndMakeVisible(_compressorComp);
    _compressorComp.setName("Comp Stage One");
    
    // tooltip
    initTooltipLabel();
    
    viator_utils::PluginWindow::setPluginWindowSize(0, 0, *this, 1.75, 0.75);
}

ViatorbedroomcompAudioProcessorEditor::~ViatorbedroomcompAudioProcessorEditor()
{
}

//==============================================================================
void ViatorbedroomcompAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
    
    auto bgImage = juce::ImageCache::getFromMemory(BinaryData::back_a_png, BinaryData::back_a_pngSize);
    auto multWidth = 0.9;
    auto multHeight = 0.8;
    auto compY = getHeight() * 0.14;
    g.drawImage(bgImage, getLocalBounds().toFloat().withSizeKeepingCentre(getWidth() * multWidth, getHeight() * multHeight).withY(compY));
}

void ViatorbedroomcompAudioProcessorEditor::resized()
{
    // header
    const auto headerHeightMult = 0.08;
    const auto headerHeight = getHeight() * headerHeightMult;
    _headerComp.setBounds(0, 0, getWidth(), headerHeight);
    
    // compressors
    const auto compressorWidth = getWidth() * 0.8;
    const auto compressorHeight = getHeight() * 0.67;
    const auto compressorX = getWidth() * 0.1;
    const auto compressorY = getHeight() * 0.2;
    _compressorComp.setBounds(compressorX, compressorY, compressorWidth, compressorHeight);
    
    // tooltips
    auto labelHeight = getHeight() * 0.05;
    auto labelFontSize = labelHeight * 0.4;
    _tooltipLabel.setBounds(0, getHeight() * 0.95, getWidth(), labelHeight);
    _tooltipLabel.setFont(juce::Font("Helvetica", labelFontSize, juce::Font::FontStyleFlags::bold));
}

void ViatorbedroomcompAudioProcessorEditor::setTooltipText(const juce::String &tooltip)
{
    _tooltipLabel.setText(tooltip, juce::dontSendNotification);
}

#pragma mark Tooltips
void ViatorbedroomcompAudioProcessorEditor::initTooltipLabel()
{
    _tooltipLabel.setText("", juce::dontSendNotification);
    addAndMakeVisible(_tooltipLabel);
}

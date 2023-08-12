#include <JuceHeader.h>
#include "CompressorComp.h"
#include "../../PluginEditor.h"

CompressorComp::CompressorComp(ViatorbedroomcompAudioProcessor& p, viator_dsp::Compressor<float>& c, std::vector<ViatorParameters::SliderParameterData>& s) : audioProcessor(p)
, compressor(c)
, sliderParams(s)
, compTypeButton(juce::ImageCache::getFromMemory(BinaryData::but_small_rec_off_png, BinaryData::but_small_rec_off_pngSize), juce::ImageCache::getFromMemory(BinaryData::but_small_rec_on_png, BinaryData::but_small_rec_on_pngSize), "VCA", "Opto")
, compPowerButton(juce::ImageCache::getFromMemory(BinaryData::but_small_rec_off_png, BinaryData::but_small_rec_off_pngSize), juce::ImageCache::getFromMemory(BinaryData::but_small_rec_on_png, BinaryData::but_small_rec_on_pngSize), "Power Off", "Power On")
{
    startTimerHz(20);
    
    // dials
    setCompDialProps();
    
    // vu meter
    addAndMakeVisible(vuMeter);
    
    // border
    setBorderProps();
    
    // buttons
    addAndMakeVisible(compTypeButton);
    auto id = ViatorParameters::comp1TypeID;
    compTypeButton.addMouseListener(this, false);
    compTypeButton.getButton().addMouseListener(this, false);
    typeAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState,
                                                                                        id,
                                                                                        compTypeButton.getButton());
    
    addAndMakeVisible(compPowerButton);
    compPowerButton.addMouseListener(this, false);
    compPowerButton.getButton().addMouseListener(this, false);
    auto powerID = ViatorParameters::comp1PowerID;
    powerAttach = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor._treeState,
                                                                                         powerID,
                                                                                         compPowerButton.getButton());
    
    // vu
    auto main = juce::ImageCache::getFromMemory(BinaryData::vu_meter_png, BinaryData::vu_meter_pngSize);
    auto grid = juce::ImageCache::getFromMemory(BinaryData::scale_vumeter_png, BinaryData::scale_vumeter_pngSize);
    auto bg = juce::ImageCache::getFromMemory(BinaryData::back_vumeter_decore5_png, BinaryData::back_vumeter_decore5_pngSize);
    vuMeter.setVUImages(main, grid, bg);
}

CompressorComp::~CompressorComp()
{
    stopTimer();
    border.setLookAndFeel(nullptr);
    compTypeButton.removeMouseListener(this);
    compTypeButton.getButton().removeMouseListener(this);
    compPowerButton.removeMouseListener(this);
    compPowerButton.getButton().removeMouseListener(this);
    for (auto& dial : compDials)
    {
        dial->removeMouseListener(this);
    }
}

void CompressorComp::paint (juce::Graphics& g)
{
    border.setText(getName());
}

void CompressorComp::resized()
{
    // dials
    const auto dialSize = getWidth() * 0.16;
    auto dialX = 0;
    auto dialY = getHeight() * 0.1;
    const auto padding = 1.3;
    
    compDials[2]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[3]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[4]->setBounds(dialX, dialY, dialSize, dialSize);

    dialX = 0;
    dialY += dialSize * padding;

    compDials[0]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[1]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[5]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;

    compDials[6]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[7]->setBounds(dialX, dialY, dialSize, dialSize);
    dialX += dialSize;
    compDials[8]->setBounds(dialX, dialY, dialSize, dialSize);
    
    // vu meter
    auto mult = 1.5;
    vuMeter.setBounds(compDials[4]->getRight(), 10, dialSize * mult * 1.428, dialSize * mult);

    // border
    border.setBounds(getLocalBounds());

    // comp type button
    const auto btnWidth = getWidth() * 0.1;
    const auto btnHeight = btnWidth * 0.6;
    const auto btnX = getWidth() * 0.84;
    auto btnY = getHeight() * 0.15;
    compTypeButton.setBounds(btnX, btnY, btnWidth, btnHeight);
    btnY += btnHeight;
    compPowerButton.setBounds(btnX, btnY, btnWidth, btnHeight);
}

void CompressorComp::setCompDialProps()
{
    auto param = sliderParams;
    auto size = param.size();
    auto filmStrip1 = juce::ImageCache::getFromMemory(BinaryData::Knob_04_png, BinaryData::Knob_04_pngSize);
    auto filmStrip2 = juce::ImageCache::getFromMemory(BinaryData::Knob_01_png, BinaryData::Knob_01_pngSize);
    auto filmStrip3 = juce::ImageCache::getFromMemory(BinaryData::Knob_05_png, BinaryData::Knob_05_pngSize);
    
    
    for (int i = 0; i < size; i++)
    {
        compDials.add(std::make_unique<viator_gui::ImageFader>());
        attachments.add(std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor._treeState, param[i].paramID, *compDials[i]));
        
        if (i >= 0 && i < size - 3)
        {
            compDials[i]->setFaderImageAndNumFrames(filmStrip1, 128);
        }
        
        else if (i >= size - 3 && i < size - 1)
        {
            compDials[i]->setFaderImageAndNumFrames(filmStrip2, 128);
        }
        
        else
        {
            compDials[i]->setFaderImageAndNumFrames(filmStrip3, 128);
        }
        
        if (param[i].isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            compDials[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kInt);
        }
        
        else
        {
            compDials[i]->setDialValueType(viator_gui::CustomDialLabel::ValueType::kFloat);
        }
        
        compDials[i]->setName(param[i].paramName);
        compDials[i]->addMouseListener(this, false);
        compDials[i]->setSliderStyle(juce::Slider::RotaryVerticalDrag);
        addAndMakeVisible(*compDials[i]);
    }
}

int CompressorComp::getDialIndexByName(const juce::String &name)
{
    auto params = sliderParams;
    auto size = params.size();
    int index = -1;
    
    for (int i = 0; i < size; i++)
    {
        if (compDials[i]->getName() == name)
        {
            index = i;
        }
    }
    
    jassert(index > -1);
    return index;
}

void CompressorComp::setBorderProps()
{
    addAndMakeVisible(border);
    border.setColour(juce::GroupComponent::ColourIds::outlineColourId, viator_utils::gui_utils::Colors::_textColor);
    border.setColour(juce::GroupComponent::ColourIds::textColourId, viator_utils::gui_utils::Colors::_textColor);
    border.setLookAndFeel(&borderLAF);
}

#pragma mark Tooltips
void CompressorComp::mouseEnter(const juce::MouseEvent &event)
{
    auto* parent = dynamic_cast<ViatorbedroomcompAudioProcessorEditor*>(getParentComponent());
    jassert(parent != nullptr);
    
    // dials
    for (int i = 0; i < compDials.size(); ++i)
    {
        if (event.eventComponent == compDials[i])
        {
            parent->setTooltipText(compDialTooltips[i]);
        }
    }
    
    // button
    if (event.eventComponent == &compTypeButton.getButton())
    {
        parent->setTooltipText("Switches the compressor model between VCA or Opto.");
    }
    
    if (event.eventComponent == &compPowerButton.getButton())
    {
        parent->setTooltipText("Powers the compressor on or off.");
    }
}

void CompressorComp::mouseExit(const juce::MouseEvent &event)
{
    auto* parent = dynamic_cast<ViatorbedroomcompAudioProcessorEditor*>(getParentComponent());
    jassert(parent != nullptr);
    
    // dials
    for (int i = 0; i < compDials.size(); ++i)
    {
        if (event.eventComponent == compDials[i])
        {
            parent->setTooltipText("");
        }
    }
    
    // button
    if (event.eventComponent == &compTypeButton.getButton())
    {
        parent->setTooltipText("");
    }
    
    if (event.eventComponent == &compPowerButton.getButton())
    {
        parent->setTooltipText("");
    }
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ViatorbedroomcompAudioProcessor::ViatorbedroomcompAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )
, _treeState(*this, nullptr, "PARAMETERS", createParameterLayout())
#endif
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.addParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
}

ViatorbedroomcompAudioProcessor::~ViatorbedroomcompAudioProcessor()
{
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getSliderParams()[i].paramID, this);
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getButtonParams()[i].paramID, this);
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        _treeState.removeParameterListener(_parameterMap.getMenuParams()[i].paramID, this);
    }
}

//==============================================================================
const juce::String ViatorbedroomcompAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ViatorbedroomcompAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ViatorbedroomcompAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ViatorbedroomcompAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ViatorbedroomcompAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ViatorbedroomcompAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ViatorbedroomcompAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ViatorbedroomcompAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ViatorbedroomcompAudioProcessor::getProgramName (int index)
{
    return {};
}

void ViatorbedroomcompAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

juce::AudioProcessorValueTreeState::ParameterLayout ViatorbedroomcompAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // sliders
    for (int i = 0; i < _parameterMap.getSliderParams().size(); i++)
    {
        auto param = _parameterMap.getSliderParams()[i];
        auto range = juce::NormalisableRange<float>(param.min, param.max);
        
        if (param.isSkew == ViatorParameters::SliderParameterData::SkewType::kSkew)
        {
            range.setSkewForCentre(param.center);
        }

        if (param.isInt == ViatorParameters::SliderParameterData::NumericType::kInt)
        {
            params.push_back (std::make_unique<juce::AudioProcessorValueTreeState::Parameter>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, param.paramName, range, param.initial, valueToTextFunction, textToValueFunction));
        }
        
        else
        {
            params.push_back (std::make_unique<juce::AudioParameterFloat>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, range, param.initial));
        }
    }
    
    // buttons
    for (int i = 0; i < _parameterMap.getButtonParams().size(); i++)
    {
        auto param = _parameterMap.getButtonParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterBool>(juce::ParameterID { param.paramID, _versionNumber }, param.paramName, _parameterMap.getButtonParams()[i].initial));
    }
    
    // menus
    for (int i = 0; i < _parameterMap.getMenuParams().size(); i++)
    {
        auto param = _parameterMap.getMenuParams()[i];
        params.push_back (std::make_unique<juce::AudioParameterInt>(juce::ParameterID { param.paramID, 1 }, param.paramName, param.min, param.max, param.defaultIndex));
    }
    
    return { params.begin(), params.end() };
}

void ViatorbedroomcompAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)

{
    if (_spec.sampleRate < 44100.0f)
        return;
    
    updateParameters();
    
}

void ViatorbedroomcompAudioProcessor::updateParameters()
{
    // comp 1 params
    auto comp1Gain = _treeState.getRawParameterValue(ViatorParameters::comp1InputID)->load();
    auto comp1Volume = _treeState.getRawParameterValue(ViatorParameters::comp1OutputID)->load();
    auto comp1Mix = _treeState.getRawParameterValue(ViatorParameters::comp1MixID)->load();
    auto thresh1 = _treeState.getRawParameterValue(ViatorParameters::comp1ThreshID)->load();
    auto ratio1 = _treeState.getRawParameterValue(ViatorParameters::comp1RatioID)->load();
    auto attack1 = _treeState.getRawParameterValue(ViatorParameters::comp1AttackID)->load();
    auto release1 = _treeState.getRawParameterValue(ViatorParameters::comp1ReleaseID)->load();
    auto knee1 = _treeState.getRawParameterValue(ViatorParameters::comp1KneeID)->load();
    auto hpf1 = _treeState.getRawParameterValue(ViatorParameters::comp1HPFID)->load();
    auto type1 = _treeState.getRawParameterValue(ViatorParameters::comp1TypeID)->load();
    
    compressorModule.setCompressorType(static_cast<viator_dsp::Compressor<float>::CompressorType>(type1));
    compressorModule.setInputGain(comp1Gain);
    compressorModule.setOutputGain(comp1Volume);
    compressorModule.setMix(comp1Mix);
    compressorModule.setParameters(thresh1, ratio1, attack1, release1, knee1, hpf1);
}

//==============================================================================
void ViatorbedroomcompAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    _spec.sampleRate = sampleRate;
    _spec.numChannels = getTotalNumOutputChannels();
    _spec.maximumBlockSize = samplesPerBlock;
    
    compressorModule.prepareModule(_spec);
    compressorModule.reset();
    updateParameters();
}

void ViatorbedroomcompAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ViatorbedroomcompAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void ViatorbedroomcompAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::dsp::AudioBlock<float> block {buffer};
    auto compPower = _treeState.getRawParameterValue(ViatorParameters::comp1PowerID)->load();
    
    if (compPower)
    {
        compressorModule.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
}

void ViatorbedroomcompAudioProcessor::calculatePeakSignal(juce::AudioBuffer<float> &buffer)
{
    levelGain.skip(buffer.getNumSamples());
    peakDB = buffer.getMagnitude(0, 0, buffer.getNumSamples());
    rmsDB = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    
    if (peakDB < levelGain.getCurrentValue())
    {
        levelGain.setTargetValue(peakDB);
    }

    else
    {
        levelGain.setCurrentAndTargetValue(peakDB);
    }
}

float ViatorbedroomcompAudioProcessor::getCurrentPeakSignal()
{
    return levelGain.getNextValue();
}

//==============================================================================
bool ViatorbedroomcompAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ViatorbedroomcompAudioProcessor::createEditor()
{
    return new ViatorbedroomcompAudioProcessorEditor (*this);
}

//==============================================================================
void ViatorbedroomcompAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    _treeState.state.appendChild(variableTree, nullptr);
    juce::MemoryOutputStream stream(destData, false);
    _treeState.state.writeToStream (stream);
}

void ViatorbedroomcompAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    auto tree = juce::ValueTree::readFromData (data, size_t(sizeInBytes));
    variableTree = tree.getChildWithName("Variables");
    
    if (tree.isValid())
    {
        _treeState.state = tree;
        _width = variableTree.getProperty("width");
        _height = variableTree.getProperty("height");
    }
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ViatorbedroomcompAudioProcessor();
}

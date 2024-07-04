#pragma once
#include <JuceHeader.h>
#include "Globals/Parameters.h"
#include "XMTFilter.h"

class ViatorbedroomcompAudioProcessor  : public juce::AudioProcessor
, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ViatorbedroomcompAudioProcessor();
    ~ViatorbedroomcompAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    // parameters
    ViatorParameters::Params _parameterMap;
    juce::AudioProcessorValueTreeState _treeState;
    
    juce::ValueTree variableTree
    { "Variables", {},
        {
        { "Group", {{ "name", "Vars" }},
            {
                { "Parameter", {{ "id", "width" }, { "value", 0.0 }}},
                { "Parameter", {{ "id", "height" }, { "value", 0.0 }}}
            }
        }
        }
    };
    
    float _width = 0.0f;
    float _height = 0.0f;
    
    viator_dsp::Compressor<float>& getComp(){return compressorModule;};
    
    void calculatePeakSignal(juce::AudioBuffer<float>& buffer);
    float getCurrentPeakSignal();
    
private:
    juce::dsp::ProcessSpec _spec;
    viator_dsp::Compressor<float> compressorModule;
    BiquadFilter<float> biquadFilter;
    
    // parameters
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    void parameterChanged (const juce::String& parameterID, float newValue) override;
    using Parameter = juce::AudioProcessorValueTreeState::Parameter;
    static juce::String valueToTextFunction(float x) { return juce::String(static_cast<int>(x)); }
    static float textToValueFunction(const juce::String& str) { return static_cast<int>(str.getFloatValue()); }
    void updateParameters();
    
    juce::SmoothedValue<double> levelGain = -60.0;
    float peakDB = -60.0;
    float rmsDB = -60.0;
    
    const int _versionNumber = 1;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ViatorbedroomcompAudioProcessor)
};

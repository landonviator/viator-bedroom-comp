#pragma once
#ifndef BiquadFilter_h
#define BiquadFilter_h
#include <JuceHeader.h>

template <typename SampleType>
class BiquadFilter
{
public:
    BiquadFilter(){};
    ~BiquadFilter(){};

    void reset();
    
    void prepareModule (const juce::dsp::ProcessSpec& spec);
    
    template <typename ProcessContext>
    void process (const ProcessContext& context) noexcept
    {
        const auto& inputBlock = context.getInputBlock();
        auto& outputBlock      = context.getOutputBlock();
        const auto numChannels = outputBlock.getNumChannels();
        const auto numSamples  = outputBlock.getNumSamples();

        jassert (inputBlock.getNumChannels() == numChannels);
        jassert (inputBlock.getNumSamples()  == numSamples);

        for (size_t channel = 0; channel < numChannels; ++channel)
        {
            for (size_t sample = 0; sample < numSamples; ++sample)
            {
                auto* input = inputBlock.getChannelPointer (channel);
                auto* output = outputBlock.getChannelPointer (channel);
                
                output[sample] = processSample(input[sample], channel);
            }
        }
    }
    
    SampleType processSample(SampleType input, SampleType channel) noexcept
    {
        auto xn = input;
        auto yn =  (currentFilterCoef.b0 * xn)
                 + (currentFilterCoef.b1 * States[channel]->x1)
                 + (currentFilterCoef.b2 * States[channel]->x2)
                 - (currentFilterCoef.a1 * States[channel]->y1)
                 - (currentFilterCoef.a2 * States[channel]->y2);
                        
        States[channel]->x2 = States[channel]->x1;    /*remember states*/
        States[channel]->x1 = xn;
        States[channel]->y2 = States[channel]->y1;
        States[channel]->y1 = yn;
        
        return yn;
    }
    
    void setParameters(double cutoff, double bandwidth);
    
private:
    
    static constexpr SampleType TwoPI = juce::MathConstants<SampleType>::twoPi;
    SampleType sampleRate = 44100.0f;
    SampleType FreqHZ = 1000.0f;
    SampleType filterQ = 0.3f;
    
    typedef struct BQCOEF
    {
        double a1;
        double a2;
        double b0;
        double b1;
        double b2;
    } BQCOEF;
    
    // State-variables
    typedef struct    BQSTATES
    {
        double        x1;
        double        x2;
        double        y1;
        double        y2;
    } BQSTATES;
    
    BQCOEF getParametricEQBand(double FreqHZ, double GaindB, double Q, double samplerate)
    {
        BQCOEF Coef;
        
        // intermediate variables
        SampleType A        = pow(10.0f , (GaindB / 40.0f) );
        SampleType w        = TwoPI * FreqHZ / sampleRate;
        SampleType sine     = sin(w);
        SampleType cosine   = cos(w);
        SampleType alpha    = sine /( 2 * Q);
        
        // compute coefficients
        SampleType a0    =   1 / (1 + alpha/A);
        Coef.a1    =   (-2*cosine) * a0;
        Coef.a2    =   (1 - alpha/A) * a0;
        Coef.b0    =   (1 + alpha*A) * a0;
        Coef.b1    =   (-2*cosine) * a0;
        Coef.b2    =   (1 - alpha*A) * a0;
        
        return Coef;
    }
    
    BQCOEF currentFilterCoef;
    juce::OwnedArray<BQSTATES> States;
};

#endif

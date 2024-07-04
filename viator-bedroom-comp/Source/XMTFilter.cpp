#include "XMTFilter.h"

template <typename SampleType>
void BiquadFilter<SampleType>::prepareModule (const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    
    States.clear();
    
    for (int i = 0; i < spec.numChannels; ++i)
    {
        States.add(std::make_unique<BQSTATES>());
        States[i]->x1 = 0.0;
        States[i]->x2 = 0.0;
        States[i]->y1 = 0.0;
        States[i]->y1 = 0.0;
    }
}

template <typename SampleType>
void BiquadFilter<SampleType>::reset()
{

}

template <typename SampleType>
void BiquadFilter<SampleType>::setParameters(double cutoff, double bandwidth)
{
    jassert(cutoff >= 20.0 && cutoff <= 20000.0);
    jassert(bandwidth >= 0.0 && bandwidth <= 1.0);
    FreqHZ = cutoff;
    filterQ = bandwidth;
    currentFilterCoef = getParametricEQBand(FreqHZ, 10.0, filterQ, sampleRate);
}

template class BiquadFilter<float>;
template class BiquadFilter<double>;

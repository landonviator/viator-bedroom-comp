#pragma once
#include <JuceHeader.h>
#include "Globals.h"

namespace ViatorParameters
{
// Param data
struct SliderParameterData
{
    enum SkewType
    {
        kSkew,
        kNoSkew
    };
    
    enum NumericType
    {
        kInt,
        kFloat
    };
    
    public:
        juce::String paramID;
        juce::String paramName;
        float min;
        float max;
        float initial;
        SkewType isSkew;
        float center;
        NumericType isInt;
};

struct ButtonParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        bool initial;
};

struct MenuParameterData
{
    public:
        juce::String paramID;
        juce::String paramName;
        int min;
        int max;
        int defaultIndex;
};


    class Params
    {
    public:
        Params();
        
        // Get a ref to the param data
        std::vector<ViatorParameters::SliderParameterData>& getSliderParams(){return _sliderParams;};
        std::vector<ViatorParameters::ButtonParameterData>& getButtonParams(){return _buttonParams;};
        std::vector<ViatorParameters::MenuParameterData>& getMenuParams(){return _menuParams;};
        
        // for attachments
        std::vector<ViatorParameters::SliderParameterData>& getComp1SliderParams(){return _comp1Params;};
        std::vector<ViatorParameters::SliderParameterData>& getIOSliderParams(){return _ioSliderParams;};
        
        int getTotalNumberOfParams(){return static_cast<int>(_sliderParams.size()) + static_cast<int>(_buttonParams.size()) + static_cast<int>(_menuParams.size());}
        
    private:
        // Adds params to the vector
        void initSliderParams();
        void initButtonParams();
        void initMenuParams();
        
        
    private:
        // Vector holding param data
        std::vector<ViatorParameters::SliderParameterData> _sliderParams;
        std::vector<ViatorParameters::ButtonParameterData> _buttonParams;
        std::vector<ViatorParameters::MenuParameterData> _menuParams;
        
        // for attachments
        std::vector<ViatorParameters::SliderParameterData> _comp1Params;
        std::vector<ViatorParameters::SliderParameterData> _ioSliderParams;
    };
}

#include "Parameters.h"


ViatorParameters::Params::Params()
{
    initSliderParams();
    initButtonParams();
    initMenuParams();
}

void ViatorParameters::Params::initSliderParams()
{
    using skew = SliderParameterData::SkewType;
    using type = SliderParameterData::NumericType;
    
    // globals
    _sliderParams.push_back({ViatorParameters::inputID,
        ViatorParameters::inputName,
        -20.0f, 20.0f, 0.0f,
        skew::kNoSkew,
        0.0,
        type::kFloat});
    _sliderParams.push_back({ViatorParameters::outputID,
        ViatorParameters::outputName,
        -20.0f, 20.0f, 0.0f,
        skew::kNoSkew,
        0.0,
        type::kFloat});
    
    // comp 1
    _sliderParams.push_back({ViatorParameters::comp1InputID, ViatorParameters::comp1InputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::comp1OutputID, ViatorParameters::comp1OutputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::comp1AttackID, ViatorParameters::comp1AttackName, 5.0f, 1000.0f, 20.0f, skew::kSkew, 100.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::comp1ReleaseID, ViatorParameters::comp1ReleaseName, 5.0f, 1000.0f, 50.0f, skew::kSkew, 100.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::comp1KneeID, ViatorParameters::comp1KneeName, 0.2f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::comp1HPFID, ViatorParameters::comp1HPFName, 20.0f, 500.0f, 20.0f, skew::kSkew, 100.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::comp1ThreshID, ViatorParameters::comp1ThreshName, -60.0f, 0.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _sliderParams.push_back({ViatorParameters::comp1RatioID, ViatorParameters::comp1RatioName, 1.0f, 20.0f, 2.0f, skew::kNoSkew, 0.0, type::kInt});
    _sliderParams.push_back({ViatorParameters::comp1MixID, ViatorParameters::comp1MixName, 0.0f, 100.0f, 100.0f, skew::kNoSkew, 0.0, type::kInt});
    
    
    // for attachments
    // io
    _ioSliderParams.push_back({ViatorParameters::inputID, ViatorParameters::inputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _ioSliderParams.push_back({ViatorParameters::outputID, ViatorParameters::outputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    
    // comp 1
    _comp1Params.push_back({ViatorParameters::comp1InputID, ViatorParameters::comp1InputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _comp1Params.push_back({ViatorParameters::comp1OutputID, ViatorParameters::comp1OutputName, -20.0f, 20.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _comp1Params.push_back({ViatorParameters::comp1AttackID, ViatorParameters::comp1AttackName, 5.0f, 1000.0f, 20.0f, skew::kSkew, 100.0, type::kInt});
    _comp1Params.push_back({ViatorParameters::comp1ReleaseID, ViatorParameters::comp1ReleaseName, 5.0f, 1000.0f, 50.0f, skew::kSkew, 100.0, type::kInt});
    _comp1Params.push_back({ViatorParameters::comp1KneeID, ViatorParameters::comp1KneeName, 0.2f, 1.0f, 1.0f, skew::kNoSkew, 0.0, type::kFloat});
    _comp1Params.push_back({ViatorParameters::comp1HPFID, ViatorParameters::comp1HPFName, 20.0f, 500.0f, 20.0f, skew::kSkew, 100.0, type::kInt});
    _comp1Params.push_back({ViatorParameters::comp1ThreshID, ViatorParameters::comp1ThreshName, -60.0f, 0.0f, 0.0f, skew::kNoSkew, 0.0, type::kFloat});
    _comp1Params.push_back({ViatorParameters::comp1RatioID, ViatorParameters::comp1RatioName, 1.0f, 20.0f, 2.0f, skew::kNoSkew, 0.0, type::kInt});
    _comp1Params.push_back({ViatorParameters::comp1MixID, ViatorParameters::comp1MixName, 0.0f, 100.0f, 100.0f, skew::kNoSkew, 0.0, type::kInt});
}

void ViatorParameters::Params::initButtonParams()
{
}

void ViatorParameters::Params::initMenuParams()
{
    _menuParams.push_back({ViatorParameters::comp1TypeID, ViatorParameters::comp1TypeName, 0, 1, 0});
    _menuParams.push_back({ViatorParameters::comp1PowerID, ViatorParameters::comp1PowerName, 0, 1, 1});
}

#pragma once
#include <JuceHeader.h>

namespace ViatorThemes
{
    class ViatorThemeData
    {
    public:
        ViatorThemeData();
        
        juce::Colour getMainBackgroundColor();
        juce::Colour getMainTextColor();
        juce::Colour getWidgetFillColor();
        juce::Colour getAuxBackgroundColor();
        juce::Colour getAuxTextColor();
        juce::Colour getBlackBackgroundColor();
        
        enum class Theme
        {
            kPrimeDark,
            kRetro,
            kLofi,
            kVaporWave,
            kHighContrast
        };
        
        void setCurrentTheme(Theme newTheme);
        
    private:
        
        
        // Theme
        Theme _currentTheme = Theme::kPrimeDark;
        
        // Colors
        juce::Colour _mainBackgroundColor = juce::Colour::fromRGB(33, 37, 43);
        juce::Colour _mainTextColor = juce::Colour::fromRGB(87, 154, 208).withAlpha(0.75f);
        juce::Colour _widgetFillColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
        juce::Colour _auxBackgroundColor = _mainBackgroundColor.darker(1.0);
        juce::Colour _auxTextColor = juce::Colour::fromRGB(74, 81, 98).darker(0.5);
        juce::Colour _blackBackgroundColor = juce::Colour::fromRGB(33, 35, 37);
    };
}

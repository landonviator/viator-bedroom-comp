#include "Colors.h"
namespace ViatorThemes
{
    ViatorThemes::ViatorThemeData::ViatorThemeData()
    {
    }

    void ViatorThemes::ViatorThemeData::setCurrentTheme(Theme newTheme)
    {
        switch (newTheme)
        {
            case Theme::kPrimeDark:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(60, 60, 73);
                _mainTextColor = juce::Colour::fromRGB(87, 154, 208).withAlpha(0.75f);
                _widgetFillColor = juce::Colour::fromRGB(161, 168, 181).darker(0.3f);
                _auxBackgroundColor = _mainBackgroundColor.darker(1.0);
                _auxTextColor = juce::Colour::fromRGB(74, 81, 98).darker(1.5);
                _blackBackgroundColor = juce::Colour::fromRGB(33, 35, 37);
                break;
            }
                
            case Theme::kRetro:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(40, 44, 52);
                _mainTextColor = juce::Colour::fromRGB(173, 213, 220).withAlpha(0.75f);
                _widgetFillColor = juce::Colour::fromRGB(109, 150, 195);
                _auxBackgroundColor = _mainBackgroundColor.darker(0.25f);
                _auxTextColor = juce::Colour::fromRGB(216, 103, 53);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
                break;
            }
                
            case Theme::kLofi:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(44, 48, 69);
                _mainTextColor = juce::Colour::fromRGB(233, 138, 235).withAlpha(0.75f);
                _widgetFillColor = juce::Colour::fromRGB(190, 147, 251).withAlpha(0.8f);
                _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
                _auxTextColor = juce::Colour::fromRGB(84, 96, 146);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
                break;
            }
                
            case Theme::kVaporWave:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(146, 157, 195).darker(2.0);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255).withAlpha(0.75f);
                _widgetFillColor = juce::Colour::fromRGB(34, 197, 236).withAlpha(0.6f);
                _auxBackgroundColor = juce::Colour::fromRGB(24, 25, 26);
                _auxTextColor = juce::Colour::fromRGB(31, 101, 181);
                _blackBackgroundColor = juce::Colour::fromRGB(18, 19, 20);
                break;
            }
                
            case Theme::kHighContrast:
            {
                _mainBackgroundColor = juce::Colour::fromRGB(0, 0, 0);
                _mainTextColor = juce::Colour::fromRGB(255, 255, 255);
                _widgetFillColor = juce::Colour::fromRGB(255, 255, 255);
                _auxBackgroundColor = juce::Colour::fromRGB(0, 0, 0);
                _auxTextColor = juce::Colour::fromRGB(255, 255, 255);
                _blackBackgroundColor = juce::Colour::fromRGB(0, 0, 0);
            }
        }
    }

    juce::Colour ViatorThemes::ViatorThemeData::getMainBackgroundColor()
    {
        return _mainBackgroundColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getMainTextColor()
    {
        return _mainTextColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getWidgetFillColor()
    {
        return _widgetFillColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getAuxBackgroundColor()
    {
        return _auxBackgroundColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getAuxTextColor()
    {
        return _auxTextColor;
    }

    juce::Colour ViatorThemes::ViatorThemeData::getBlackBackgroundColor()
    {
        return _blackBackgroundColor;
    }
}

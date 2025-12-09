

#pragma once


#include <JuceHeader.h>

namespace aiomfx {


const juce::Colour AIOMFX_RED{255, 109, 124};


class AiomFXLookAndFeel : public juce::LookAndFeel_V4  {

public:
    AiomFXLookAndFeel();
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPos, const float rotaryStartAngle,
                           const float rotaryEndAngle, juce::Slider& slider);
  
    juce::Label* createSliderTextBox (juce::Slider& slider);
    
   void drawTickBox (juce::Graphics& g, juce::Component& component,
                                      float x, float y, float w, float h,
                                      const bool ticked,
                                      [[maybe_unused]] const bool isEnabled,
                                      [[maybe_unused]] const bool shouldDrawButtonAsHighlighted,
                     [[maybe_unused]] const bool shouldDrawButtonAsDown);
    
    // In LookAndFeel.h inside class AiomFXLookAndFeel : public ...
void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                       bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown,
                       int buttonX, int buttonY, int buttonW, int buttonH,
                       juce::ComboBox& box) override;

    void positionComboBoxText (juce::ComboBox& box, juce::Label& label) override;

    void drawPopupMenuBackground (juce::Graphics& g, int width, int height) override;
    

   
};

}

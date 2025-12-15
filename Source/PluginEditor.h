/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <unordered_set>
#include "PluginProcessor.h"
#include "processors/scales_n_chords/Scale.h"
#include "LookAndFeel.h"


//==============================================================================
/**
*/
class AiomFXAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer,
private juce::ComboBox::Listener, private juce::ToggleButton::Listener, private juce::Slider::Listener
{
public:
    AiomFXAudioProcessorEditor (AiomFXAudioProcessor&);
    ~AiomFXAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void comboBoxChanged(juce::ComboBox *box) override;
    void buttonClicked(juce::Button *button) override;
    void timerCallback() override;
    void sliderValueChanged(juce::Slider *slider) override;
    
    /**
     * @param x starting offset by X for drawing piano
     * @param y starting offset by Y for drawing piano
     */
    void drawScaleSectionPiano(int x, int y);

private:
    AiomFXAudioProcessor& audioProcessor;
    aiomfx::AiomFXLookAndFeel aiomFXLAF;
    
    // Min width and heigt of the plugin
    int minWidth = 600;
    int minHeight = 340;
    int maxWidth = 800;
    int maxHeight = 700;
    
    juce::ComboBox keyDropdown;
    juce::ComboBox scaleDropdown;
    juce::ToggleButton scaleSectionOctDownBtn;
    juce::ToggleButton scaleSectionOctUpBtn;
    juce::ToggleButton scaleSectionBypassBtn;
    juce::Label scaleSectionLabel;
    juce::Label scaleSectionKeyLabel;
    juce::Label scaleSectionScaleLabel;
    juce::ToggleButton scaleSectionChordsAreOnBtn;
    juce::Slider scaleSectionNumOfNotesSlider = juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                                             juce::Slider::TextEntryBoxPosition::TextBoxBelow);
    juce::Label scaleSectionNumOfNotesSliderLabel;
    
    juce::Slider scaleSectionInversionSlider = juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                                            juce::Slider::TextEntryBoxPosition::TextBoxBelow);
    juce::Label scaleSectionInversionSliderLabel;
    
    // Velocity section UI controls
    juce::Label velocitySectionLabel;
    juce::ToggleButton velocitySectionBypassBtn;
    juce::Slider velocitySectionMinSlider = juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                                         juce::Slider::TextEntryBoxPosition::TextBoxBelow);
    juce::Slider velocitySectionMaxSlider = juce::Slider(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
                                                         juce::Slider::TextEntryBoxPosition::TextBoxBelow);
    juce::Label velocitySectionMinSliderLabel;
    juce::Label velocitySectionMaxSliderLabel;
    juce::Rectangle<int> velocitySectionHeaderBorder;
    
    juce::Rectangle<int> scaleSectionHeaderBorder;
    juce::Rectangle<int> scaleSectionPianoTopBorder;
    juce::Rectangle<int> scaleSectionPianoLeftBorder;
    juce::Rectangle<int> scaleSectionPianoRightBorder;
    juce::Rectangle<int> scaleSectionPianoBottomBorder;
    juce::Rectangle<int> scaleSectionVerticalSeparator;
    juce::Rectangle<int> keyC;
    juce::Rectangle<int> keyDb;
    juce::Rectangle<int> keyD;
    juce::Rectangle<int> keyEb;
    juce::Rectangle<int> keyE;
    juce::Rectangle<int> keyF;
    juce::Rectangle<int> keyGb;
    juce::Rectangle<int> keyG;
    juce::Rectangle<int> keyAb;
    juce::Rectangle<int> keyA;
    juce::Rectangle<int> keyBb;
    juce::Rectangle<int> keyB;

    std::map<int, juce::Rectangle<int>> itor;
    void setUpDropdown(juce::ComboBox &dropdown, const std::vector<std::string> &options, int selectedOption, bool addListener);
    
    std::vector<int> currentNoteNumbers;
    std::unordered_set<int> currentNoteNumbersSet;
    
    // Colors
    std::map<std::string, juce::Colour> notesColours{
        {"naturalNotActive", juce::Colour(229, 214, 212)},
        {"naturalActive", juce::Colour(198, 176, 171)},
        {"sharpNotActive", juce::Colour (158, 143, 137)},
        {"sharpActive", juce::Colour(107, 91, 85)},
    };
    
    juce::Colour scaleSectionPianoBorderColour = juce::Colour(229, 214, 212);
    
    juce::Colour backgroundColour = juce::Colour(255, 249, 245);
//    juce::Colour backgroundColour = juce::Colour(86, 100, 139);
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AiomFXAudioProcessorEditor)
};

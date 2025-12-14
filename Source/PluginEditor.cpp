/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

//==============================================================================
AiomFXAudioProcessorEditor::AiomFXAudioProcessorEditor (AiomFXAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setLookAndFeel(&aiomFXLAF);
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    audioProcessor.scale.setKeyAndName("C", "Major");
    setSize (minWidth, minHeight);
//    setResizable(true, true);
//    setResizeLimits (minWidth, minHeight, maxWidth, maxHeight);
    
    const juce::Colour PLUGIN_BACKGROUND_COLOR{59, 96, 94};
    const juce::Colour TEXT_COLOR{239, 146, 35};

    addAndMakeVisible(keyDropdown);
    addAndMakeVisible(scaleDropdown);
    addAndMakeVisible(scaleSectionLabel);
    addAndMakeVisible(scaleSectionKeyLabel);
    addAndMakeVisible(scaleSectionScaleLabel);
    addAndMakeVisible(scaleSectionBypassBtn);
    addAndMakeVisible(scaleSectionOctDownBtn);
    addAndMakeVisible(scaleSectionChordsAreOnBtn);
    addAndMakeVisible(scaleSectionNumOfNotesSlider);
    addAndMakeVisible(scaleSectionOctUpBtn);
    addAndMakeVisible(scaleSectionNumOfNotesSliderVal2);
    addAndMakeVisible(scaleSectionNumOfNotesSliderVal3);
    addAndMakeVisible(scaleSectionNumOfNotesSliderVal4);
    addAndMakeVisible(scaleSectionNumOfNotesSliderVal5);
    addAndMakeVisible(scaleSectionNumOfNotesSliderLabel);
    addAndMakeVisible(scaleSectionInversionSlider);
    addAndMakeVisible(scaleSectionInversionSliderLabel);
    addAndMakeVisible(scaleSectionInversionSliderVal0);
    addAndMakeVisible(scaleSectionInversionSliderVal1);
    addAndMakeVisible(scaleSectionInversionSliderVal2);
    addAndMakeVisible(scaleSectionInversionSliderVal3);
    
    // Velocity section UI components
    addAndMakeVisible(velocitySectionLabel);
    addAndMakeVisible(velocitySectionBypassBtn);
    addAndMakeVisible(velocitySectionMinSlider);
    addAndMakeVisible(velocitySectionMaxSlider);
    addAndMakeVisible(velocitySectionMinSliderLabel);
    addAndMakeVisible(velocitySectionMaxSliderLabel);

    scaleSectionLabel.setFont (juce::Font (18.0f, juce::Font::bold));
    scaleSectionLabel.setText("Scales & Chords", juce::dontSendNotification);
    scaleSectionLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    
    scaleSectionNumOfNotesSliderVal2.setText("2", juce::dontSendNotification);
    scaleSectionNumOfNotesSliderVal2.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionNumOfNotesSliderVal3.setText("3", juce::dontSendNotification);
    scaleSectionNumOfNotesSliderVal3.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionNumOfNotesSliderVal4.setText("4", juce::dontSendNotification);
    scaleSectionNumOfNotesSliderVal4.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionNumOfNotesSliderVal5.setText("5", juce::dontSendNotification);
    scaleSectionNumOfNotesSliderVal5.setColour(juce::Label::textColourId, juce::Colours::black);
    
    scaleSectionNumOfNotesSliderLabel.setText("Notes", juce::dontSendNotification);
    scaleSectionNumOfNotesSliderLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    
    scaleSectionInversionSliderLabel.setText("Inversion", juce::dontSendNotification);
    scaleSectionInversionSliderLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    
    scaleSectionInversionSliderVal0.setText("0", juce::dontSendNotification);
    scaleSectionInversionSliderVal0.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionInversionSliderVal1.setText("1", juce::dontSendNotification);
    scaleSectionInversionSliderVal1.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionInversionSliderVal2.setText("2", juce::dontSendNotification);
    scaleSectionInversionSliderVal2.setColour(juce::Label::textColourId, juce::Colours::black);
    scaleSectionInversionSliderVal3.setText("3", juce::dontSendNotification);
    scaleSectionInversionSliderVal3.setColour(juce::Label::textColourId, juce::Colours::black);

    scaleSectionKeyLabel.setText("Key", juce::dontSendNotification);
    scaleSectionKeyLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    scaleSectionScaleLabel.setText("Scale", juce::dontSendNotification);
    scaleSectionScaleLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    setUpDropdown(keyDropdown, aiomfx::Note::notes, 1, true);
    setUpDropdown(scaleDropdown, aiomfx::Scale::scalesNames, 1, true);

    scaleSectionBypassBtn.setTitle("Bypass");
    scaleSectionBypassBtn.setButtonText("Bypass");
    scaleSectionBypassBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionBypassBtn.addListener(this);
    scaleSectionBypassBtn.setToggleable(true);
    scaleSectionBypassBtn.setToggleState(true, juce::dontSendNotification);

//    if (audioProcessor.scale.getIsActive()) {
//        scaleSectionBypassBtn.setState(juce::Button::ButtonState::buttonDown);
//    }

    scaleSectionOctDownBtn.setTitle("Oct Down");
    scaleSectionOctDownBtn.setButtonText("Oct Down");
    scaleSectionOctDownBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionOctDownBtn.addListener(this);
    scaleSectionOctDownBtn.setToggleable(true);
    
    scaleSectionOctUpBtn.setTitle("Oct Up");
    scaleSectionOctUpBtn.setButtonText("Oct Up");
    scaleSectionOctUpBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionOctUpBtn.addListener(this);
    scaleSectionOctUpBtn.setToggleable(true);

    scaleSectionChordsAreOnBtn.setTitle("Chords");
    scaleSectionChordsAreOnBtn.setButtonText("Chords");
    scaleSectionChordsAreOnBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    scaleSectionChordsAreOnBtn.addListener(this);
    scaleSectionChordsAreOnBtn.setToggleable(true);
    scaleSectionChordsAreOnBtn.setToggleState(true, juce::dontSendNotification);

    juce::NormalisableRange<double> range (2.0, 5.0, 1.0, true); // Snap to integers
    scaleSectionNumOfNotesSlider.setNormalisableRange (range);
    scaleSectionNumOfNotesSlider.setValue(3.0);
    scaleSectionNumOfNotesSlider.setDoubleClickReturnValue(true, 0.0);
    scaleSectionNumOfNotesSlider.setTextBoxIsEditable(false);
    scaleSectionNumOfNotesSlider.setTextBoxStyle(
                                                 juce::Slider::TextEntryBoxPosition::NoTextBox,
                                                 true,
                                                 20,
                                                 20
    );
    scaleSectionNumOfNotesSlider.addListener(this);
    
    scaleSectionNumOfNotesSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(239, 146, 35));
    scaleSectionNumOfNotesSlider.setColour(juce::Slider::thumbColourId, juce::Colour(239, 146, 35));
    scaleSectionNumOfNotesSlider.setColour(juce::Slider::textBoxTextColourId , TEXT_COLOR);
    scaleSectionNumOfNotesSlider.setColour(juce::Slider::textBoxOutlineColourId, PLUGIN_BACKGROUND_COLOR);
    
    // INVERSION SLIDER
    juce::NormalisableRange<double> range2 (0.0, 3.0, 1.0, true); // Snap to integers
    scaleSectionInversionSlider.setNormalisableRange (range2);
    scaleSectionInversionSlider.setValue(0.0);
    scaleSectionInversionSlider.setDoubleClickReturnValue(true, 0.0);
    scaleSectionInversionSlider.setTextBoxIsEditable(false);
    scaleSectionInversionSlider.setTextBoxStyle(
                                                 juce::Slider::TextEntryBoxPosition::NoTextBox,
                                                 true,
                                                 20,
                                                 20
    );
    scaleSectionInversionSlider.addListener(this);
    
    scaleSectionInversionSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(239, 146, 35));
    scaleSectionInversionSlider.setColour(juce::Slider::thumbColourId, juce::Colour(239, 146, 35));
    scaleSectionInversionSlider.setColour(juce::Slider::textBoxTextColourId , TEXT_COLOR);
    scaleSectionInversionSlider.setColour(juce::Slider::textBoxOutlineColourId, PLUGIN_BACKGROUND_COLOR);
    
    // VELOCITY SECTION SETUP
    velocitySectionLabel.setFont (juce::Font (18.0f, juce::Font::bold));
    velocitySectionLabel.setText("Humanize", juce::dontSendNotification);
    velocitySectionLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    
    velocitySectionBypassBtn.setTitle("Bypass");
    velocitySectionBypassBtn.setButtonText("Bypass");
    velocitySectionBypassBtn.setColour(juce::ToggleButton::textColourId, juce::Colours::black);
    velocitySectionBypassBtn.addListener(this);
    velocitySectionBypassBtn.setToggleable(true);
    velocitySectionBypassBtn.setToggleState(true, juce::dontSendNotification);
    
    // MIN VELOCITY SLIDER
    juce::NormalisableRange<double> velocityMinRange (1.0, 127.0, 1.0, true); // MIDI velocity range
    velocitySectionMinSlider.setNormalisableRange (velocityMinRange);
    velocitySectionMinSlider.setValue(64.0); // Default min value
    audioProcessor.velocity.setMinVal(64);
    velocitySectionMinSlider.setDoubleClickReturnValue(true, 64.0);
    velocitySectionMinSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    velocitySectionMinSlider.setTextBoxIsEditable(false);
    velocitySectionMinSlider.addListener(this);
    velocitySectionMinSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(239, 146, 35));
    velocitySectionMinSlider.setColour(juce::Slider::thumbColourId, juce::Colour(239, 146, 35));
    velocitySectionMinSlider.setColour(juce::Slider::textBoxTextColourId , juce::Colours::black);
    velocitySectionMinSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    
    velocitySectionMinSliderLabel.setText("Min", juce::dontSendNotification);
    velocitySectionMinSliderLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    velocitySectionMinSliderLabel.setJustificationType(juce::Justification::centred);
    
    // MAX VELOCITY SLIDER  
    juce::NormalisableRange<double> velocityMaxRange (1.0, 127.0, 1.0, true); // MIDI velocity range
    velocitySectionMaxSlider.setNormalisableRange (velocityMaxRange);
    velocitySectionMaxSlider.setValue(100.0); // Default max value
    audioProcessor.velocity.setMaxVal(100);
    velocitySectionMaxSlider.setDoubleClickReturnValue(true, 100.0);
    velocitySectionMaxSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 50, 20);
    velocitySectionMaxSlider.setTextBoxIsEditable(false);
    velocitySectionMaxSlider.addListener(this);
    velocitySectionMaxSlider.setColour(juce::Slider::rotarySliderFillColourId, juce::Colour(239, 146, 35));
    velocitySectionMaxSlider.setColour(juce::Slider::thumbColourId, juce::Colour(239, 146, 35));
    velocitySectionMaxSlider.setColour(juce::Slider::textBoxTextColourId , juce::Colours::black);
    velocitySectionMaxSlider.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
    
    velocitySectionMaxSliderLabel.setText("Max", juce::dontSendNotification);
    velocitySectionMaxSliderLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    velocitySectionMaxSliderLabel.setJustificationType(juce::Justification::centred);
    
    drawScaleSectionPiano(10, 100);

    itor[1] = keyC;
    itor[2] = keyDb;
    itor[3] = keyD;
    itor[4] = keyEb;
    itor[5] = keyE;
    itor[6] = keyF;
    itor[7] = keyGb;
    itor[8] = keyG;
    itor[9] = keyAb;
    itor[10] = keyA;
    itor[11] = keyBb;
    itor[12] = keyB;

    juce::Timer::startTimer(1);
}

AiomFXAudioProcessorEditor::~AiomFXAudioProcessorEditor()
{
    juce::Timer::stopTimer();
    setLookAndFeel(nullptr);
}

//==============================================================================
void AiomFXAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
//    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(backgroundColour);
    
    g.setColour(scaleSectionPianoBorderColour);
    g.fillRect(scaleSectionHeaderBorder);
    g.fillRect(velocitySectionHeaderBorder);
    g.fillRect(scaleSectionPianoTopBorder);
    g.fillRect(scaleSectionPianoBottomBorder);
    g.fillRect(scaleSectionPianoLeftBorder);
    g.fillRect(scaleSectionPianoRightBorder);

    for (auto note : audioProcessor.scale.getNotes()) {
        if (note.getIsNatural()) {
            if (note.getIsInScale()) {
                g.setColour(notesColours["naturalActive"]);
                g.fillRect(itor[note.getId()]);
            } else {
                g.setColour(notesColours["naturalNotActive"]);
                g.fillRect(itor[note.getId()]);
            }

            if (std::find(currentNoteNumbers.begin(), currentNoteNumbers.end(), note.getId()) != currentNoteNumbers.end()) {
                g.setColour(juce::Colours::orange);
                g.fillRect(itor[note.getId()]);
            }
        }
    }

    // sharps and flats have to be painted after the naturals because order of painting
    // matters in juce. this way shaprs/flat are drawn correctly on top of naturals
    for (auto note : audioProcessor.scale.getNotes()) {
        if (!note.getIsNatural()) {
            if (note.getIsInScale()) {
                g.setColour(notesColours["sharpActive"]);
                g.fillRect(itor[note.getId()]);
            } else {
                g.setColour(notesColours["sharpNotActive"]);
                g.fillRect(itor[note.getId()]);
            }

            if (std::find(currentNoteNumbers.begin(), currentNoteNumbers.end(), note.getId()) != currentNoteNumbers.end()) {
                g.setColour(juce::Colours::orange);
                g.fillRect(itor[note.getId()]);
            }
        }
    }
}

void AiomFXAudioProcessorEditor::resized() {
    scaleSectionHeaderBorder = juce::Rectangle<int>(0, 30, getWidth(), 2);
    scaleSectionBypassBtn.setBounds(230, 0, 100, 30);
    scaleSectionLabel.setBounds(10, 10, 200, 13);
    
    scaleSectionKeyLabel.setBounds(10, 40, 40, 15);
    scaleSectionScaleLabel.setBounds(90, 40, 100, 15);
    keyDropdown.setBounds(10, 60, 60, 30);
    scaleDropdown.setBounds(90, 60, 100, 30);
    
    scaleSectionChordsAreOnBtn.setBounds(230, 30, 100, 50);
    
    scaleSectionNumOfNotesSliderVal2.setBounds(220, 145, 20, 20);
    scaleSectionNumOfNotesSliderVal3.setBounds(220, 75, 20, 20);
    scaleSectionNumOfNotesSliderVal4.setBounds(300, 75, 20, 20);
    scaleSectionNumOfNotesSliderVal5.setBounds(300, 145, 20, 20);
    scaleSectionNumOfNotesSlider.setBounds(230, 80, 70, 70);
    scaleSectionNumOfNotesSlider.toFront(false);
    scaleSectionNumOfNotesSliderLabel.setBounds(243, 115, 50, 80);
    
    scaleSectionInversionSliderVal0.setBounds(335, 145, 20, 20);
    scaleSectionInversionSliderVal1.setBounds(335, 75, 20, 20);
    scaleSectionInversionSliderVal2.setBounds(415, 75, 20, 20);
    scaleSectionInversionSliderVal3.setBounds(415, 145, 20, 20);
    scaleSectionInversionSlider.setBounds(345, 80, 70, 70);
    scaleSectionInversionSlider.toFront(false);
    scaleSectionInversionSliderLabel.setBounds(349, 115, 70, 80);
    
    
    scaleSectionOctUpBtn.setBounds(450, 70, 100, 50);
    scaleSectionOctDownBtn.setBounds(450, 120, 100, 20);
    
    velocitySectionHeaderBorder = juce::Rectangle<int>(0, 175, getWidth(), 2);
    
    // VELOCITY SECTION LAYOUT - positioned below piano
    velocitySectionLabel.setBounds(10, 180, 200, 20);
    velocitySectionBypassBtn.setBounds(230, 180, 100, 30);
    
    velocitySectionMinSliderLabel.setBounds(10, 210, 70, 15);
    velocitySectionMinSlider.setBounds(10, 225, 70, 90);
    
    velocitySectionMaxSliderLabel.setBounds(100, 210, 70, 15);
    velocitySectionMaxSlider.setBounds(100, 225, 70, 90);
}

void AiomFXAudioProcessorEditor::comboBoxChanged(juce::ComboBox *box) {
    if (box == &keyDropdown || box == &scaleDropdown) {
        // TODO: get rid of scale object in plugin editor;
//        scale.setKeyAndName(keyDropdown.getText().toStdString(), scaleDropdown.getText().toStdString());
        audioProcessor.scale.setKeyAndName(keyDropdown.getText().toStdString(), scaleDropdown.getText().toStdString());
        repaint();
    }
}

void AiomFXAudioProcessorEditor::buttonClicked(juce::Button *btn) {
    bool isToggled = btn->getToggleState();

    if (btn == &scaleSectionOctDownBtn) {
        audioProcessor.scale.setAddOctDown(isToggled);
    } else if (btn == &scaleSectionOctUpBtn) {
        audioProcessor.scale.setAddOctUp(isToggled);
    } else if (btn == &scaleSectionBypassBtn) {
        audioProcessor.scale.setIsActive(isToggled);
    } else if (btn == &scaleSectionChordsAreOnBtn) {
        audioProcessor.scale.setChordsAreOn(isToggled);
    } else if (btn == &velocitySectionBypassBtn) {
        audioProcessor.velocity.setIsActive(isToggled);
    }
}

void AiomFXAudioProcessorEditor::setUpDropdown(juce::ComboBox &dropdown, const std::vector<std::string> &options, int selectedOption, bool addListener) {

    for (int i = 0; i < options.size(); i++) {
        dropdown.addItem(options[i], i+1);
    }

    dropdown.setEditableText(false);
    dropdown.setSelectedId(selectedOption);

    if (addListener)
        dropdown.addListener(this);
}

void AiomFXAudioProcessorEditor::timerCallback() {
    currentNoteNumbers = audioProcessor.getCurrentNoteNumbers();
    if (!currentNoteNumbers.empty()) {
        for (int& noteNumber : currentNoteNumbers) {
            noteNumber = noteNumber % 12 + 1;
        }
        repaint();
    }
}

void AiomFXAudioProcessorEditor::drawScaleSectionPiano(int x, int y) {
    int numOfNaturalNotes = 7;
    int naturalNotePadding = 1; // space between natural notes
    int allNaturalNotesPadding = (numOfNaturalNotes-1) * naturalNotePadding;
    int borderSize = 3;
    int scalePianoY = y+borderSize;
    int scalePianoX = x+borderSize;
    int scalePianoNaturalsHeight = 55;
    int scalePianoFlatsHeight = 25;
    int scalePianoNaturalsWidth = 25;
    int scalePianoFlatsWidth = 18;

    int bottomBorderY = scalePianoY + scalePianoNaturalsHeight;
    int leftRightBorderHeight = scalePianoNaturalsHeight + 2 * borderSize;
    int rightBorderX = x + borderSize + numOfNaturalNotes * scalePianoNaturalsWidth + allNaturalNotesPadding;
    int topBottomBorderWidth = 2 * borderSize + numOfNaturalNotes * scalePianoNaturalsWidth + allNaturalNotesPadding;

    scaleSectionPianoTopBorder = juce::Rectangle<int>(x, y, topBottomBorderWidth, borderSize);
    scaleSectionPianoBottomBorder = juce::Rectangle<int>(x, bottomBorderY, topBottomBorderWidth, borderSize);
    scaleSectionPianoLeftBorder = juce::Rectangle<int>(x, y, borderSize, leftRightBorderHeight);
    scaleSectionPianoRightBorder = juce::Rectangle<int>(rightBorderX, y, borderSize, leftRightBorderHeight);
    // Scale piano roll

    keyC = juce::Rectangle<int>(scalePianoX, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyDb = juce::Rectangle<int>(keyC.getX()+keyC.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyD = juce::Rectangle<int>(scalePianoX+keyC.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyEb = juce::Rectangle<int>(keyD.getX()+keyD.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyE = juce::Rectangle<int>(keyD.getX()+keyD.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyF = juce::Rectangle<int>(keyE.getX()+keyE.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyGb = juce::Rectangle<int>(keyF.getX()+keyF.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyG = juce::Rectangle<int>(keyF.getX()+keyF.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyAb = juce::Rectangle<int>(keyG.getX()+keyG.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyA = juce::Rectangle<int>(keyG.getX()+keyG.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
    keyBb = juce::Rectangle<int>(keyA.getX()+keyA.getWidth() - scalePianoFlatsWidth / 2, scalePianoY, scalePianoFlatsWidth, scalePianoFlatsHeight);
    keyB = juce::Rectangle<int>(keyA.getX()+keyA.getWidth()+naturalNotePadding, scalePianoY, scalePianoNaturalsWidth, scalePianoNaturalsHeight);
}

void AiomFXAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    if (slider == &scaleSectionNumOfNotesSlider) {
        audioProcessor.scale.setNumOfNotesInChords((int)slider->getValue());
    } else if(slider == &scaleSectionInversionSlider) {
        audioProcessor.scale.setInversion((int)slider->getValue());
    } else if (slider == &velocitySectionMinSlider) {
        audioProcessor.velocity.setMinVal((int)slider->getValue());
    } else if (slider == &velocitySectionMaxSlider) {
        audioProcessor.velocity.setMaxVal((int)slider->getValue());
    }
}

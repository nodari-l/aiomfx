
#include "LookAndFeel.h"


namespace aiomfx {

AiomFXLookAndFeel::AiomFXLookAndFeel()
{
    setColour(juce::PopupMenu::backgroundColourId, juce::Colour::fromString("FFFFF9F7"));
    setColour(juce::PopupMenu::textColourId, juce::Colour::fromString("FF2B2B2B"));
    setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour::fromString("FFC49A91"));
    setColour(juce::PopupMenu::highlightedTextColourId, juce::Colour::fromString("FFFFF9F7"));
}

void AiomFXLookAndFeel::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                                          float sliderPos, const float rotaryStartAngle,
                                          const float rotaryEndAngle, juce::Slider& slider) {
    auto bounds = juce::Rectangle<int>(x, y, width, height).toFloat();
    auto center = bounds.getCentre();
    auto radius = juce::jmin(bounds.getWidth(), bounds.getHeight()) / 2.0f;

    // --- Design Parameters ---
    const float trackThickness = 8.0f;
    const float knobPadding = 5.0f;
    const float pointerThickness = 2.5f;
    const float pointerLengthRatio = 0.55f;

    // --- Colors ---
    const auto colorTrack      = juce::Colour::fromString("FFDBC3BE"); // Muted beige (empty part)
    // **NEW**: This is the "brighter" fill color.
    // I chose a slightly deeper/warmer tone so it stands out against the pale background.
    // You can change this hex code to any color you like (e.g., a bright orange or solid black).
    const auto colorActiveFill = juce::Colour::fromString("FFC49A91");
    
    const auto colorKnob       = juce::Colour::fromString("FFFFF9F7");
    const auto colorPointer    = juce::Colour::fromString("FF2B2B2B");
    const auto colorKnobBorder = juce::Colour::fromString("FFE5D6D4");

    // --- 1. Draw the Background Track (The empty container) ---
    float trackRadius = radius - (trackThickness / 2.0f);
    juce::Path trackPath;
    trackPath.addCentredArc(center.x, center.y,
                            trackRadius, trackRadius,
                            0.0f,
                            rotaryStartAngle,
                            rotaryEndAngle,
                            true);

    g.setColour(colorTrack);
    g.strokePath(trackPath, juce::PathStrokeType(trackThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));

    // --- 2. Draw the Active Fill (The bright part) ---
    // Only draw if the slider is not at the minimum position
    if (sliderPos > 0.0f)
    {
        juce::Path fillPath;
        // Calculate the angle for the current slider position
        float currentAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        fillPath.addCentredArc(center.x, center.y,
                               trackRadius, trackRadius,
                               0.0f,
                               rotaryStartAngle,
                               currentAngle,
                               true);

        g.setColour(colorActiveFill);
        g.strokePath(fillPath, juce::PathStrokeType(trackThickness, juce::PathStrokeType::curved, juce::PathStrokeType::rounded));
    }

    // --- 3. Draw the Inner Knob Face ---
    float knobRadius = trackRadius - (trackThickness / 2.0f) - knobPadding;
    
    g.setColour(colorKnob);
    g.fillEllipse(center.x - knobRadius, center.y - knobRadius, knobRadius * 2.0f, knobRadius * 2.0f);
    g.setColour(colorKnobBorder);
    g.drawEllipse(center.x - knobRadius, center.y - knobRadius, knobRadius * 2.0f, knobRadius * 2.0f, 1.5f);

    // --- 4. Draw the Pointer ---
    juce::Path p;
    p.startNewSubPath(0.0f, 0.0f);
    p.lineTo(0.0f, -knobRadius * pointerLengthRatio);

    float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(center.x, center.y));

    g.setColour(colorPointer);
    g.strokePath(p, juce::PathStrokeType(pointerThickness, juce::PathStrokeType::mitered, juce::PathStrokeType::butt));
}


void AiomFXLookAndFeel::drawTickBox (juce::Graphics& g, juce::Component& component,
                                     float x, float y, float w, float h,
                                     const bool ticked,
                                     [[maybe_unused]] const bool isEnabled,
                                     [[maybe_unused]] const bool shouldDrawButtonAsHighlighted,
                                     [[maybe_unused]] const bool shouldDrawButtonAsDown) {
    juce::Rectangle<float> tickBounds {x, y, w, h};
    
    g.setColour(juce::Colours::black);
    g.drawRect(tickBounds);
    
    if (ticked)
    {
        g.setColour(AIOMFX_RED);
        g.fillRect(tickBounds);
    }
}


juce::Label* AiomFXLookAndFeel::createSliderTextBox (juce::Slider& slider) {
    auto* l = LookAndFeel_V2::createSliderTextBox (slider);
    juce::Font font16{20.0f};
    l->setFont(font16);
    
    
    return l;
}


void AiomFXLookAndFeel::drawToggleButton (juce::Graphics& g, juce::ToggleButton& button,
                                          bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    // --- Colors ---
    const auto colorTrack      = juce::Colour::fromString("FFDBC3BE");
    const auto colorActiveFill = juce::Colour::fromString("FFC49A91");
    const auto colorThumb      = juce::Colour::fromString("FFFFF9F7");
    const auto colorText       = juce::Colour::fromString("FF2B2B2B");

    auto bounds = button.getLocalBounds().toFloat();
    
    // --- FIX: Use Hardcoded Dimensions ---
    // Instead of scaling based on bounds, we lock the height to 20 pixels.
    // This ensures Oct Up and Oct Down are identical.
    const float switchHeight = 20.0f; 
    const float switchWidth  = 34.0f; // Fixed width (approx 1.7x height)
    
    // Center the switch vertically
    const float paddingX = 4.0f;
    juce::Rectangle<float> switchBounds (paddingX, 
                                         bounds.getCentreY() - (switchHeight * 0.5f), 
                                         switchWidth, 
                                         switchHeight);

    // --- 1. Draw the Track ---
    g.setColour (button.getToggleState() ? colorActiveFill : colorTrack);
    g.fillRoundedRectangle (switchBounds, switchHeight * 0.5f);

    // --- 2. Draw the Thumb ---
    g.setColour (colorThumb);
    
    const float thumbPadding = 3.0f; 
    const float thumbSize = switchHeight - (thumbPadding * 2.0f);
    
    float thumbX = switchBounds.getX() + thumbPadding; 
    
    if (button.getToggleState())
    {
        thumbX = switchBounds.getRight() - thumbSize - thumbPadding;
    }
    
    g.fillEllipse (thumbX, 
                   switchBounds.getCentreY() - (thumbSize * 0.5f), 
                   thumbSize, 
                   thumbSize);

    // --- 3. Draw the Text ---
    g.setColour (colorText);
    g.setFont (juce::Font(16.0f)); 
    
    if (button.getButtonText().isNotEmpty())
    {
        auto textBounds = bounds;
        // Start text after the switch + 10px spacing
        textBounds.removeFromLeft (switchBounds.getRight() + 10.0f); 
        
        g.drawFittedText (button.getButtonText(), 
                          textBounds.toNearestInt(), 
                          juce::Justification::centredLeft, 
                          1); 
    }
}

void AiomFXLookAndFeel::drawComboBox (juce::Graphics& g, int width, int height, bool isButtonDown,
                                      int buttonX, int buttonY, int buttonW, int buttonH,
                                      juce::ComboBox& box)
{
    auto bounds = juce::Rectangle<int>(0, 0, width, height).toFloat();
    const float cornerSize = 5.0f;

    const auto colorBackground = juce::Colour::fromString("FFDBC3BE");
    const auto colorBorder     = juce::Colour::fromString("FFC49A91");
    const auto colorArrow      = juce::Colour::fromString("FF2B2B2B");

    g.setColour(colorBackground);
    g.fillRoundedRectangle(bounds, cornerSize);

    g.setColour(colorBorder);
    g.drawRoundedRectangle(bounds, cornerSize, 1.5f);

    g.setColour(colorArrow);
    
    juce::Path arrow;
    const float arrowX = buttonX + buttonW * 0.5f;
    const float arrowY = buttonY + buttonH * 0.5f;
    const float arrowW = 4.0f;
    const float arrowH = 2.5f;

    arrow.startNewSubPath (arrowX - arrowW, arrowY - arrowH * 0.5f);
    arrow.lineTo (arrowX, arrowY + arrowH * 0.5f);
    arrow.lineTo (arrowX + arrowW, arrowY - arrowH * 0.5f);

    g.strokePath(arrow, juce::PathStrokeType(2.0f));
}

void AiomFXLookAndFeel::positionComboBoxText (juce::ComboBox& box, juce::Label& label)
{
    label.setBounds (10, 1, box.getWidth() - 30, box.getHeight() - 2);
    label.setFont (juce::Font(16.0f));
    label.setColour(juce::Label::textColourId, juce::Colour::fromString("FF2B2B2B"));
    label.setJustificationType(juce::Justification::centredLeft);
}

void AiomFXLookAndFeel::drawPopupMenuBackground (juce::Graphics& g, int width, int height)
{
    const auto colorBackground = juce::Colour::fromString("FFFFF9F7");
    g.fillAll(colorBackground);
}

}

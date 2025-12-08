#pragma once

#include <JuceHeader.h>

namespace aiomfx {

class Velocity {
    bool isActive = true;
    int minVal = 20;
    int maxVal = 100;
    
    juce::Random random;
    
public:
    Velocity();
    
    /**
     * Process MIDI buffer and randomize velocity of note-on messages
     *
     * @param buffer - MIDI buffer to process
     */
    void process(juce::MidiBuffer& buffer);
    
    /**
     * Randomize velocity within the user-defined range
     *
     * @param originalVelocity - original velocity value (unused in current implementation)
     * @return randomized velocity value within [minVal, maxVal] range
     */
    int randomizeVelocity(int originalVelocity);
    
    /**
     * Set minimum velocity value
     *
     * @param val - minimum velocity (1-127)
     */
    void setMinVal(int val);
    
    /**
     * Get minimum velocity value
     *
     * @return current minimum velocity value
     */
    int getMinVal();
    
    /**
     * Set maximum velocity value
     *
     * @param val - maximum velocity (1-127, must be >= minVal)
     */
    void setMaxVal(int val);
    
    /**
     * Get maximum velocity value
     *
     * @return current maximum velocity value
     */
    int getMaxVal();
    
    /**
     * Enable or disable velocity randomization
     *
     * @param val - true to enable, false to disable
     */
    void setIsActive(bool val);
    
    /**
     * Check if velocity randomization is active
     *
     * @return true if active, false if disabled
     */
    bool getIsActive();
};

}

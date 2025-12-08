#include "Velocity.h"

namespace aiomfx {

Velocity::Velocity() {
    random.setSeedRandomly();
}

void Velocity::process(juce::MidiBuffer& buffer) {
    if (!isActive) {
        return;
    }
    
    juce::MidiBuffer processedBuffer;
    
    for (const juce::MidiMessageMetadata metadata : buffer) {
        auto message = metadata.getMessage();
        
        if (message.isNoteOn()) {
            // Randomize velocity for note-on messages
            int newVelocity = randomizeVelocity(message.getVelocity());
            auto newMessage = juce::MidiMessage::noteOn(message.getChannel(), 
                                                       message.getNoteNumber(), 
                                                       (juce::uint8)newVelocity);
            newMessage.setTimeStamp(message.getTimeStamp());
            processedBuffer.addEvent(newMessage, metadata.samplePosition);
        } else {
            // Pass through all other MIDI messages unchanged
            processedBuffer.addEvent(message, metadata.samplePosition);
        }
    }
    
    // Replace original buffer with processed buffer
    buffer.swapWith(processedBuffer);
}

int Velocity::randomizeVelocity(int originalVelocity) {
    if (!isActive || minVal > maxVal) {
        return originalVelocity;
    }
    
    // Generate random velocity within user-defined range
    int randomVelocity = random.nextInt(juce::Range<int>(minVal, maxVal + 1));
    
    // Ensure valid MIDI range (1-127)
    return juce::jlimit(1, 127, randomVelocity);
}

void Velocity::setMinVal(int val) {
    minVal = juce::jlimit(1, 127, val);
    // Ensure maxVal is not less than minVal
    if (maxVal < minVal) {
        maxVal = minVal;
    }
}

int Velocity::getMinVal() {
    return minVal;
}

void Velocity::setMaxVal(int val) {
    maxVal = juce::jlimit(1, 127, val);
    // Ensure minVal is not greater than maxVal
    if (minVal > maxVal) {
        minVal = maxVal;
    }
}

int Velocity::getMaxVal() {
    return maxVal;
}

void Velocity::setIsActive(bool val) {
    isActive = val;
}

bool Velocity::getIsActive() {
    return isActive;
}

}
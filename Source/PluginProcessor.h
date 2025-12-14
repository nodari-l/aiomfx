/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <vector>
#include <atomic>

#include "processors/scales_n_chords/Scale.h"
#include "processors/velocity/Velocity.h"

//==============================================================================
/**
*/
class AiomFXAudioProcessor  : public juce::AudioProcessor
{
public:
    
    //==============================================================================
    AiomFXAudioProcessor();
    ~AiomFXAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void addCurrentNoteNumber(int noteNumber);
    void removeCurrentNoteNumber(int noteNumber);
    std::vector<int> getCurrentNoteNumbers();
    bool hasActiveNotes();
    void setScale(aiomfx::Scale &scale);
    aiomfx::Scale scale;
    aiomfx::Velocity velocity;
private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AiomFXAudioProcessor);
    std::atomic<std::uint64_t> activeNotesBitfieldLow{0};  // Notes 0-63
    std::atomic<std::uint64_t> activeNotesBitfieldHigh{0}; // Notes 64-127
    
};

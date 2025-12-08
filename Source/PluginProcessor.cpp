/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AiomFXAudioProcessor::AiomFXAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

AiomFXAudioProcessor::~AiomFXAudioProcessor()
{
}

//==============================================================================
const juce::String AiomFXAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool AiomFXAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool AiomFXAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool AiomFXAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double AiomFXAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AiomFXAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AiomFXAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AiomFXAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AiomFXAudioProcessor::getProgramName (int index)
{
    return {};
}

void AiomFXAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AiomFXAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void AiomFXAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool AiomFXAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void AiomFXAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();

    // --- Stage 1: Scale Processing ---
    if (scale.getIsActive())
    {
        juce::MidiBuffer tempBuffer;
        for (const auto metadata : midiMessages)
        {
            auto msg = metadata.getMessage();
            scale.process(metadata, tempBuffer); // Process from midiMessages into tempBuffer

            if (msg.isNoteOn())
                setCurrentNoteNumber(msg.getNoteNumber());
            else if (msg.isNoteOff() && msg.getNoteNumber() == getCurrentNoteNumber())
                setCurrentNoteNumber(-1);
        }
        midiMessages.swapWith(tempBuffer); // Apply the changes by swapping
    }

    // --- Stage 2: Velocity Processing ---
    if (velocity.getIsActive())
    {
        velocity.process(midiMessages); // Process the resulting buffer in-place
    }
}

//==============================================================================
bool AiomFXAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AiomFXAudioProcessor::createEditor() {
    return new AiomFXAudioProcessorEditor (*this);
}

//==============================================================================
void AiomFXAudioProcessor::getStateInformation (juce::MemoryBlock& destData) {
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AiomFXAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter() {
    return new AiomFXAudioProcessor();
}


void AiomFXAudioProcessor::setCurrentNoteNumber(int val) {
    currentNoteNumber = val;
}

int AiomFXAudioProcessor::getCurrentNoteNumber() {
    return currentNoteNumber;
}

void AiomFXAudioProcessor::setScale(aiomfx::Scale &scale) {
    this->scale = scale;
}

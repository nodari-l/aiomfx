---
description: Repository Information Overview
alwaysApply: true
---

# Aiomfx Audio Plugin Information

## Summary
Aiomfx is a MIDI processing VST3/AU audio plugin built with JUCE framework. It provides "Scales and Chords" functionality that transposes played notes to fit selected scales and generates chords from single notes. Future plans include velocity randomization, note randomization, arpeggiator, and step sequencer.

## Structure
**Main Directories**:
- **Source/**: Main C++ source code including plugin processor, editor, and custom processors
- **Source/processors/scales_n_chords/**: Core MIDI processing logic (Scale, Note, Chord classes)
- **JuceLibraryCode/**: Auto-generated JUCE framework integration code
- **Builds/**: Build output directory (git-ignored)

## Language & Runtime
**Language**: C++  
**Framework**: JUCE 7+ (Audio Application Framework)  
**Build System**: JUCE Projucer + Xcode (macOS)  
**Plugin Formats**: VST3, AU (Audio Units)  
**Platform**: macOS (configured for Xcode builds)

## Dependencies
**JUCE Modules**:
- juce_audio_basics, juce_audio_devices, juce_audio_formats
- juce_audio_plugin_client, juce_audio_processors, juce_audio_processors_headless
- juce_audio_utils, juce_core, juce_data_structures, juce_dsp
- juce_events, juce_graphics, juce_gui_basics, juce_gui_extra

**Module Path**: `/opt/JUCE/modules` (global JUCE installation)

## Build & Installation
**Project Configuration**: `aiomfx.jucer` (JUCE Projucer project file)

**Build Process**:
1. Open `aiomfx.jucer` in JUCE Projucer
2. Generate Xcode project files
3. Build using Xcode for macOS targets

**Build Configurations**:
- Debug: Development build with debugging symbols
- Release: Optimized production build

**Plugin Characteristics**: Synthesizer plugin that produces MIDI output and accepts MIDI input

## Main Files & Resources
**Entry Points**:
- `Source/PluginProcessor.cpp:18` - Main audio processor (AiomFXAudioProcessor class)
- `Source/PluginEditor.cpp:25` - Plugin GUI editor

**Core Components**:
- `Source/processors/scales_n_chords/Scale.h:10` - Scale processing logic
- `Source/processors/scales_n_chords/Note.h` - Note representation and handling
- `Source/processors/scales_n_chords/Chord.h` - Chord generation functionality
- `Source/LookAndFeel.cpp` - Custom UI styling

**Configuration**:
- `JuceLibraryCode/JucePluginDefines.h` - Plugin build definitions
- **Plugin Version**: 0.0.1
- **Manufacturer**: aiomfx
- **AAX Identifier**: org.aiomfx.aiomfx

## Project Structure
**Architecture**: Single JUCE audio plugin project with modular processor design
**Plugin Type**: MIDI effect/synthesizer hybrid
**GUI Framework**: JUCE native components with custom LookAndFeel
**Processing Pipeline**: MIDI input → Scale/Chord processing → MIDI output
**Target DAWs**: Ableton Live, REAPER, Logic Pro, Cubase (any VST3/AU compatible DAW)
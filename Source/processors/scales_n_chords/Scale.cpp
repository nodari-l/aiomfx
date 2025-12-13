#include "Scale.h"


namespace aiomfx {

const std::vector<std::string> Scale::scalesNames = {"Major", "Minor",
    "Lydian", "Mixolydian", "Spanish", "Dorian", "Phrygian",
    "Harmonic Minor", "Melodic Minor", "Major Pentatonic", "Minor Pentatonic"};

Scale::Scale(std::string key, std::string name) : key(key), name(name) {
    if (name == "Major")
        buildMajorScale();
    else if (name == "Minor")
        buildMinorScale();
    else if (name == "Lydian")
        buildLydianScale();
    else if (name == "Mixolydian")
        buildMyxolydianScale();
    else if (name == "Spanish")
        buildSpanishScale();
    else if (name == "Dorian")
        buildDorianScale();
    else if (name == "Phrygian")
        buildPhrygianScale();
    else if (name == "Harmonic Minor")
        buildHarmonicMinorScale();
    else if (name == "Melodic Minor")
        buildMelodicMinorScale();
    else if (name == "Major Pentatonic")
        buildMajorPentatonicScale();
    else if (name == "Minor Pentatonic")
        buildMinorPentatonicScale();
}

void Scale::buildScale(std::vector<int> &intervals, std::vector<int> &chordTypes) {
    for (auto& note : notes) {
        note.setInScale(false);
    }
    
    int noteId = keyToNoteNum[key];
    notes[noteId].setInScale(true);
    notes[noteId].setChordType(chordTypes[0]);
    for (int i = 0; i < intervals.size(); i++) {
        noteId += intervals[i];

        if (noteId > 11) {
            noteId = noteId - 12;
        }
        
        notes[noteId].setInScale(true);
        notes[noteId].setChordType(chordTypes[i+1]);
    }
    
    buildScaleMap();
}

// WWHWWWH
void Scale::buildMajorScale() {
    std::vector<int> intervals {2,2,1,2,2,2};
    std::vector<int> chordTypes {
        Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor,
        Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor5};
    buildScale(intervals, chordTypes);
}

// W‑H‑W‑W‑H‑W‑W
void Scale::buildMinorScale() {
    std::vector<int> intervals {2,1,2,2,1,2};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMinor5, Note::chordTypeMajor,
        Note::chordTypeMinor, Note::chordTypeMinor, Note::chordTypeMajor, Note::chordTypeMajor};
    buildScale(intervals, chordTypes);
}

void Scale::buildLydianScale() {
    std::vector<int> intervals {2,2,2,1,2,2};
    std::vector<int> chordTypes {
        Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMinor,
        Note::chordTypeMinor5, Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor};
    buildScale(intervals, chordTypes);
}

void Scale::buildMyxolydianScale() {
    std::vector<int> intervals {2,2,1,2,2,1};
    std::vector<int> chordTypes {
        Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor5,
        Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor,
        Note::chordTypeMajor
    };
    buildScale(intervals, chordTypes);
}

void Scale::buildSpanishScale() {
    std::vector<int> intervals {1,3,1,2,1,2};
    std::vector<int> chordTypes {
        Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMajor5,
        Note::chordTypeMinor, Note::chordTypeMajorDim, Note::chordTypeMajor5, Note::chordTypeMinor};
    buildScale(intervals, chordTypes);
}

void Scale::buildDorianScale() {
    std::vector<int> intervals {2,1,2,2,2,1};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMinor, Note::chordTypeMajor,
        Note::chordTypeMajor, Note::chordTypeMinor, Note::chordTypeMinor5,
        Note::chordTypeMajor};
    buildScale(intervals, chordTypes);
}

void Scale::buildPhrygianScale() {
    std::vector<int> intervals {1,2,2,2,1,2};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMajor, Note::chordTypeMajor,
        Note::chordTypeMinor, Note::chordTypeMinor5, Note::chordTypeMajor, Note::chordTypeMinor};
    buildScale(intervals, chordTypes);
}

void Scale::buildHarmonicMinorScale() {
    std::vector<int> intervals {2,1,2,2,1,3};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMajorDim, Note::chordTypeMajor5,
        Note::chordTypeMinor, Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMajor5};
    buildScale(intervals, chordTypes);
}

void Scale::buildMelodicMinorScale() {
    std::vector<int> intervals {2,1,2,2,2,2};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMinor, Note::chordTypeMajor5,
        Note::chordTypeMajor, Note::chordTypeMajor, Note::chordTypeMinor5, Note::chordTypeMajor5};
    buildScale(intervals, chordTypes);
}

void Scale::buildMajorPentatonicScale() {
    std::vector<int> intervals {2,2,3,2};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMajorNo3, Note::chordTypeMinor5,
        Note::chordTypeMajorNo3, Note::chordTypeMinor};
    buildScale(intervals, chordTypes);
}

void Scale::buildMinorPentatonicScale() {
    std::vector<int> intervals {3,2,2,3};
    std::vector<int> chordTypes {
        Note::chordTypeMinor, Note::chordTypeMajor, Note::chordTypeMajorNo3,
        Note::chordTypeMinor5, Note::chordTypeMajorNo3};
    buildScale(intervals, chordTypes);
}

std::string Scale::toStr() {
    std::stringstream s;
    
    for (auto note : notes)
        s << note.getId() << " ";
    
    return s.str();
}

std::set<Note> Scale::getNotesInScale() {
    std::set<Note> out;
    
    for (auto note : notes) {
        if (note.getIsInScale())
            out.insert(note);
    }
    return out;
}

std::set<Note> Scale::getNotesNotInScale() {
    std::set<Note> out;
    
    for (auto note : notes) {
        if (!note.getIsInScale())
            out.insert(note);
    }
    return out;
}

int Scale::adjustToScale(int noteNumber) {
    if (scaleMapping.count(noteNumber) > 0)
        return scaleMapping[noteNumber];
    
    return noteNumber;
}

std::vector<int> Scale::getChordIntervals(int noteNumber, int numOfNotes=3) {
    noteNumber = noteNumber % 12;
    return notes[noteNumber].getChordIntervals(numOfNotes);
}

void Scale::buildScaleMap() {
    std::set<int> notesNumsInScale;
    
    for (auto note : getNotesInScale()) {
        notesNumsInScale.insert(note.getId()-1);
    }
    
    for (int noteNum = Note::minNoteNumber; noteNum <= Note::maxNoteNumber; noteNum++) {
        if (notesNumsInScale.count(noteNum % 12) == 0) {
            scaleMapping[noteNum] = noteNum - 1;
        }
    }
}

void Scale::process(const juce::MidiMessageMetadata& metadata, juce::MidiBuffer& buffer) {
    auto msg = metadata.getMessage();
    int sampleNumber = msg.getTimeStamp();
    int adjustedRoot = adjustToScale(msg.getNoteNumber());
    std::vector<int> chordIntervals;
    std::deque<int> addedNotes{adjustedRoot};
    // TODO: rewrite how chords are generated using the Chord class
    if (chordsAreOn) {
        chordIntervals = getChordIntervals(adjustedRoot, numOfNotesInChords);
        
        for (auto interval : chordIntervals) {
            addedNotes.push_back(adjustedRoot+interval);
        }
        
        if (inversion > 0) {
            invertChord(addedNotes, inversion);
        }
    }
    
    if (msg.isNoteOn()) {
        // TODO: add oct up/down into the addedNotes deque?
        if (addOctDown && adjustedRoot-12 >= Note::minNoteNumber) {
            buffer.addEvent(juce::MidiMessage::noteOn(msg.getChannel(), adjustedRoot-12, msg.getVelocity()), sampleNumber);
        }
        
        if (addOctUp && adjustedRoot+12 <= Note::maxNoteNumber) {
            buffer.addEvent(juce::MidiMessage::noteOn(msg.getChannel(), adjustedRoot+12, msg.getVelocity()), sampleNumber);
        }
        
        for (auto note : addedNotes) {
            buffer.addEvent(juce::MidiMessage::noteOn(msg.getChannel(), note, msg.getVelocity()), sampleNumber);
        }
    } else if (msg.isNoteOff()) {
        buffer.addEvent(msg, sampleNumber);
        buffer.addEvent(juce::MidiMessage::noteOff(msg.getChannel(), adjustedRoot, msg.getVelocity()), sampleNumber);
        // add a root minus an octave in case addOctDown was on
        if (addOctDown && adjustedRoot-12 >= Note::minNoteNumber) {
            buffer.addEvent(juce::MidiMessage::noteOff(msg.getChannel(), adjustedRoot-12, msg.getVelocity()), sampleNumber);
        }
        // add a root minus an octave in case addOctUp was on
        if (addOctUp && adjustedRoot+12 <= Note::maxNoteNumber) {
            buffer.addEvent(juce::MidiMessage::noteOff(msg.getChannel(), adjustedRoot+12, msg.getVelocity()), sampleNumber);
        }
        
        for (auto note : addedNotes)
            buffer.addEvent(juce::MidiMessage::noteOff(msg.getChannel(), note, msg.getVelocity()), sampleNumber);
    } else {
        buffer.addEvent(msg, sampleNumber);
    }
}

bool Scale::getIsActive() {
    return isActvie;
}

void Scale::setIsActive(bool val) {
    isActvie = val;
}

std::vector<Note> Scale::getNotes() {
    return notes;
}


void Scale::setAddOctDown(bool val) {
    addOctDown = val;
}

bool Scale::getAddOctDown() {
    return addOctDown;
}

void Scale::setAddOctUp(bool val) {
    addOctUp = val;
}

bool Scale::getAddOctUp() {
    return addOctUp;
}

void Scale::setChordsAreOn(bool val) {
    chordsAreOn = val;
}

bool Scale::getChordsAreOn() {
    return chordsAreOn;
}

void Scale::setNumOfNotesInChords(int val) {
    numOfNotesInChords = val;
}

int Scale::getNumOfNotesInChords() {
    return numOfNotesInChords;
}

void Scale::setInversion(int val) {
    inversion = val;
}

int Scale::getInversion() {
    return inversion;
}

void Scale::invertChord(std::deque<int> &notes, int inversion) {
    if (inversion <= 0)
        return;
    
    notes.push_back(notes.front()+12);
    notes.pop_front();
    
    if (inversion == 1)
        return;
    
    notes.push_back(notes.front()+12);
    notes.pop_front();
    
    if (inversion == 2)
        return;
        
    notes.push_back(notes.front()+12);
    notes.pop_front();
}

void Scale::setKeyAndName(std::string newKey, std::string newName) {
    key = newKey;
    name = newName;
    
    if (name == "Major")
        buildMajorScale();
    else if (name == "Minor")
        buildMinorScale();
    else if (name == "Lydian")
        buildLydianScale();
    else if (name == "Mixolydian")
        buildMyxolydianScale();
    else if (name == "Spanish")
        buildSpanishScale();
    else if (name == "Dorian")
        buildDorianScale();
    else if (name == "Phrygian")
        buildPhrygianScale();
    else if (name == "Harmonic Minor")
        buildHarmonicMinorScale();
    else if (name == "Melodic Minor")
        buildMelodicMinorScale();
    else if (name == "Major Pentatonic")
        buildMajorPentatonicScale();
    else if (name == "Minor Pentatonic")
        buildMinorPentatonicScale();
}


}; // namespace aiomfx

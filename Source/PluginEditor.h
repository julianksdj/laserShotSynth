/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LaserShotSynthAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                            public juce::Slider::Listener
                                            //,private juce::MidiKeyboardStateListener
{
public:
    LaserShotSynthAudioProcessorEditor (LaserShotSynthAudioProcessor&);
    ~LaserShotSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    //==============================================================================
    void sliderValueChanged (juce::Slider *slider) override;
    //void handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;
    //void handleNoteOff (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity) override;

    void play(){
        audioProcessor.triggerShot();
    };
    
private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LaserShotSynthAudioProcessor& audioProcessor;
    
    //==============================================================================
    juce::Slider tuneKnob;
    juce::Label  tuneLabel;
    juce::Slider pitchEnvKnob;
    juce::Label  pitchEnvLabel;
    juce::Slider decayKnob;
    juce::Label decayLabel;
    juce::TextButton trigButton;
    
    juce::MidiKeyboardState keyboardState;
    //juce::MidiKeyboardComponent keyboardComponent;
    //juce::AudioDeviceManager deviceManager;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LaserShotSynthAudioProcessorEditor)
};

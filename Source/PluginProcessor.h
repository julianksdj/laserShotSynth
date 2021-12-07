/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Voice.h"

//==============================================================================
/**
*/
class LaserShotSynthAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    LaserShotSynthAudioProcessor();
    ~LaserShotSynthAudioProcessor() override;

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

    //==============================================================================
    void addVoice(float frequency)
    {
        for (auto voiceIndex = 0; voiceIndex < voices.size(); ++voiceIndex)
        {
            if (voices.getUnchecked(voiceIndex)->getFrequency()==frequency)
            {
                voices.remove(voiceIndex);
            }
        }
        Voice *voice = new Voice();
        voice->setNoteOn(true);
        voice->setSampleRate(currentSampleRate);
        voice->setFreq(frequency+frequency*tune/12);
        voice->setPitchDecay(pitchDecay);
        voice->setTune(tune);
        voice->setPitchEnv(pitchEnv);
        voice->setAttack(0.01);
        voice->setDecay(0.01);
        voice->setSustain(0.125);
        voice->setRelease(pitchDecay);
        voice->getEnvelope(); //sobra?
        voices.add(voice);
    };
    void deactivateVoice(float freq)
    {
         for (auto voiceIndex = 0; voiceIndex < voices.size(); ++voiceIndex)
        {
            if (voices[voiceIndex]->getFrequency() == freq)
            {
                voices[voiceIndex]->setNoteOn(false);
                voices[voiceIndex]->resetEnvCount();
            }
        }
    };
    void triggerShot()
    {
        trigger=true;
        DBG("Triggered shot!");
    };
    void setTune(float t)
    {
        tune = t;
    };
    void setPitchEnv(float p)
    {
        pitchEnv = p;
        for (auto voiceIndex = 0; voiceIndex < voices.size(); ++voiceIndex)
        {
            auto* voice = voices.getUnchecked(voiceIndex);
            voice->setPitchEnv(pitchEnv);
        }
    };
    void setPitchDecay(float d)
    {
        pitchDecay = d;
        for (auto voiceIndex = 0; voiceIndex < voices.size(); ++voiceIndex)
        {
            auto* voice = voices.getUnchecked(voiceIndex);
            voice->setPitchDecay(pitchDecay);
        }
    };
    
private:
    float currentSampleRate = 0.0;
    juce::OwnedArray<Voice> voices; //voices array
    float pitchDecay, tune, pitchEnv;
    bool trigger;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LaserShotSynthAudioProcessor)
};

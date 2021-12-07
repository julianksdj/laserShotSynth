/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LaserShotSynthAudioProcessorEditor::LaserShotSynthAudioProcessorEditor (LaserShotSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (180, 360);
    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::purple);
    
    // tune knob
    addAndMakeVisible (tuneKnob);
    tuneKnob.setRange (-11.9, 12.0);
    tuneKnob.addListener (this);
    tuneKnob.setValue(0.0);
    tuneLabel.setText ("Tune", juce::dontSendNotification);
    tuneLabel.setJustificationType(juce::Justification::centred);
    tuneLabel.attachToComponent (&tuneKnob, true);
    tuneLabel.setColour(juce::Label::textColourId, juce::Colours::purple);
    addAndMakeVisible (tuneLabel);
    tuneKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    tuneKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 15);
    
    // pitch env knob
    addAndMakeVisible (pitchEnvKnob);
    pitchEnvKnob.setRange (1.0, 8.0);
    pitchEnvKnob.addListener (this);
    pitchEnvKnob.setValue(4.5);
    pitchEnvLabel.setText ("Pitch env", juce::dontSendNotification);
    pitchEnvLabel.setJustificationType(juce::Justification::centred);
    pitchEnvLabel.attachToComponent (&pitchEnvKnob, true);
    pitchEnvLabel.setColour(juce::Label::textColourId, juce::Colours::purple);
    addAndMakeVisible (pitchEnvLabel);
    pitchEnvKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    pitchEnvKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 15);
    
    // decayKnob
    addAndMakeVisible (decayKnob);
    decayKnob.setRange (0.01, 3.0);
    decayKnob.setTextValueSuffix ("Seconds");
    decayKnob.addListener (this);
    decayKnob.setValue(1.495);
    decayLabel.setText ("Decay", juce::dontSendNotification);
    decayLabel.setJustificationType(juce::Justification::centred);
    decayLabel.attachToComponent (&decayKnob, true);
    decayLabel.setColour(juce::Label::textColourId, juce::Colours::purple);
    addAndMakeVisible (decayLabel);
    decayKnob.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    decayKnob.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 80, 15);
    
    
    // trigger button
    addAndMakeVisible(trigButton);
    trigButton.setButtonText("Trigger");
    trigButton.setColour(juce::Label::textColourId, juce::Colours::purple);
    trigButton.setToggleState(false, juce::NotificationType::dontSendNotification);
    trigButton.onClick = [this]() {play();};
}

LaserShotSynthAudioProcessorEditor::~LaserShotSynthAudioProcessorEditor()
{
}

//==============================================================================
void LaserShotSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colour (178, 176, 255));

    g.setColour(juce::Colours::purple);
    g.setFont (15.0f);
    g.drawFittedText("Laser shot synth", 0, 8, getWidth(), 5, juce::Justification::centred, 1);
}

void LaserShotSynthAudioProcessorEditor::resized()
{
    const int width = getWidth()/2;
    const int height = getHeight();
    const int border = 20;
    tuneKnob.setBounds(width/2+border, 0+border, width-border, height/4-border);
    pitchEnvKnob.setBounds(width/2+border, height/4+border, width-border, height/4-border);
    decayKnob.setBounds(width/2+border, 2*(height/4)+border, width-border, height/4-border);
    trigButton.setBounds(width/2+border, 3*(height/4)+border, width-border, height/4-border);
}

void LaserShotSynthAudioProcessorEditor::sliderValueChanged(juce::Slider *slider)
{
    if(slider == &tuneKnob)
    {
        audioProcessor.setTune(tuneKnob.getValue()) ;
    }
    if(slider == &pitchEnvKnob)
    {
        audioProcessor.setPitchEnv(pitchEnvKnob.getValue()) ;
    }
    if(slider == &decayKnob)
    {
        audioProcessor.setPitchDecay(decayKnob.getValue()) ;
    }
}
/*
void LaserShotSynthAudioProcessorEditor::handleNoteOn (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    printf("\nNOTE PRESSED\n");
    printf("Received note %d\n",midiNoteNumber);
    // frequency calculation from midi note data
    double nota = 0.0;
    nota = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    printf("Calculated frequency %f\n",nota);
    audioProcessor.addVoice(nota);
}
void LaserShotSynthAudioProcessorEditor::handleNoteOff (juce::MidiKeyboardState* source, int midiChannel, int midiNoteNumber, float velocity)
{
    auto nota = juce::MidiMessage::getMidiNoteInHertz (midiNoteNumber);
    printf("NOTE RELEASED\n");
    audioProcessor.deactivateVoice(nota);
}
*/

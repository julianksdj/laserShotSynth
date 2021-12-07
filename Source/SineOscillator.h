//
//  SineOscillator.h
//  fmsynth
//
//  Created by Keepin' Soul on 21/11/2021.
//

#ifndef SineOscillator_h
#define SineOscillator_h

class SineOscillator {
public:
    SineOscillator()
    {
    };
    void setFrequency (float frequency)
    {
        auto cyclesPerSample = frequency / currentSampleRate;
        angleDelta = cyclesPerSample * juce::MathConstants<double>::twoPi;
    };
    float getNextSample(int channel)
    {
        currentFreq = ((freq-freqEnv)/(float)(decaySamples-1))*(envCount-1)+freqEnv;
        envCount++;
        setFrequency(currentFreq);

        float sample = std::sin(currentAngle[channel]);
        currentAngle[channel] += angleDelta;
        currentAngleSW[channel] += angleDeltaSW;
        if (currentAngle[channel]>=juce::MathConstants<double>::twoPi)
            currentAngle[channel] -= juce::MathConstants<double>::twoPi;
        if (currentAngleSW[channel]>=juce::MathConstants<double>::twoPi)
            currentAngleSW[channel] -= juce::MathConstants<double>::twoPi;
        return sample;
    };
    float getFrequency()
    {
        return freq;
    };
    void setFreq(float m)
    {
        freq = m;
    };
    void setSampleRate(float sr)
    {
        currentSampleRate = sr;
    };
    // laser shot
    void setPitchDecay(float d)
    {
        decay = d;
        decaySamples = decay * currentSampleRate;
    };
    void setPitchEnv(float p)
    {
        pitchEnv = p;
        freqEnv= pitchEnv * freq;
    };
    void setTune(float t)
    {
        tune = t;
    };
    
private:
    float currentAngle[2], currentAngleSW[2], angleDelta, angleDeltaSW;
    float currentSampleRate;
    float freq, freqSW, currentFreq,initialFreq;
    float modAmp;
    float modAmpSmoothed;
    float decay, tune, pitchEnv; // pitch decay
    int envCount=0;
    int decaySamples;
    float freqEnv;
};

#endif /* SineOscillator_h */

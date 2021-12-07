//
//  Voice.h
//  fmsynth
//
//  Created by Keepin' Soul on 28/11/2021.
//

#ifndef Voice_h
#define Voice_h

#include "Envelope.h"
#include "SineOscillator.h"

class Voice
{

public:
    
    // voice features functions
    bool isActive ()
    {
        if (env.getCarrAmp()<=0.0000001)
            return false;
        else
            return true;
    };
    
    // Oscillator functions
    void setFrequency (float f)
    {
        osc.setFrequency(f);
    };
    void setFreq (float f)
    {
        osc.setFreq(f);
    };
    float getNextSample(int channel) //noexcept
    {
        return osc.getNextSample(channel);
    };
    float getFrequency()
    {
        return osc.getFrequency();
    };

    // envelope functions
    float getEnvelope()
    {
        return env.getEnvelope();
    };
    void setAttack(float a)
    {
        env.setAttack(a);
    };
    void setDecay(float d)
    {
        env.setDecay(d);
    };
    void setSustain(float s)
    {
        env.setSustain(s);
    };
    void setRelease(float r)
    {
        env.setRelease(r);
    };
    void setSampleRate(int sr)
    {
        env.setSampleRate(sr);
    };
    void setCarrAmp(float a)
    {
        env.setCarrAmp(a);
    };
    void setNoteOn(bool n)
    {
        env.setNoteOn(n);
    };
    void resetEnvCount()
    {
        env.resetEnvCount();
    };
    void setSampleRate(float sr)
    {
        osc.setSampleRate(sr);
        env.setSampleRate(sr);
    };
    
    //laser shot new functions
    void setPitchDecay(float d)
    {
        osc.setPitchDecay(d);
    };
    void setPitchEnv(float p)
    {
        osc.setPitchEnv(p);
    };
    void setTune(float t)
    {
        osc.setPitchEnv(t);
    };
    
    
private:
    Envelope env;
    SineOscillator osc;
};

#endif /* Voice_h */

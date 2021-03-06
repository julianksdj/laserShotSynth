//
//  Envelope.h
//  fmsynth
//
//  Created by Keepin' Soul on 28/11/2021.
//

#ifndef Envelope_h
#define Envelope_h

class Envelope
{

public:
    Envelope()
    {
        envCount = 0;
    };
    
    float getEnvelope()
    {
        //Calculate envelope
        if(noteOn==true) //pressed note on the keyboard
        {
            if (envCount < attackSamples)
            {
                carrAmp+=(0.125/attackSamples); //the amplitude raises until max amplitude is reached
            }
            else if (envCount < daSamples)
            {
                carrAmp-=((0.125-sustainLevel)/decaySamples); //the amplitude decreases until sustain level is reached
            }
            releaseLevel = carrAmp; // saves the amplitude state
        }
        else //released note on the keyboard
        {
            if(carrAmp>0.0000001)
                carrAmp-=(releaseLevel/releaseSamples); //amplitude decreases until silence
        }
        envCount++;
        return carrAmp;
    };
    
    void setAttack(float a)
    {
        attackTime = a;
        attackSamples = currentSampleRate * attackTime;
    };
    void setDecay(float d)
    {
        decayTime = d;
        decaySamples = currentSampleRate * decayTime;
        daSamples = decaySamples + attackSamples;
    };
    void setSustain(float s)
    {
        sustainLevel = s;
    };
    void setRelease(float r)
    {
        releaseTime = r;
        releaseSamples = currentSampleRate * releaseTime;
    };
    float getCarrAmp(){
        return carrAmp;
    };
    void setCarrAmp(float a){
        carrAmp=a;
    };
    void setNoteOn(bool n){
        noteOn = n;
    };
    void resetEnvCount(){
        envCount = 0;
    };
    void setSampleRate(float sr){
        currentSampleRate = sr;
    };
    
private:
    float currentSampleRate;
    float carrAmp;
    float attackTime, decayTime, sustainLevel, releaseTime;
    int attackSamples, decaySamples, releaseSamples, daSamples;
    int envCount;
    bool noteOn;
    float releaseLevel;
};


#endif /* Envelope_h */

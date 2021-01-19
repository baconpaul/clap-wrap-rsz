/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <set>

//==============================================================================
/**
*/

struct FakeSurgeParameter {
    FakeSurgeParameter(const std::string n, float v, int i) : streaming_name(n), value(v), id(i) {}

    int id;
    float value;
    std::string streaming_name;

    void setValueFromDAW(float f) {
        if( value != f ) {
            value = f;
        }
    }

};

class ToyJuceAudioProcessor;

struct FSPRangedAdapter : public juce::RangedAudioParameter
{
    explicit FSPRangedAdapter(FakeSurgeParameter *weakRef, ToyJuceAudioProcessor *proc)
    : p(weakRef), proc(proc),
    RangedAudioParameter(weakRef->streaming_name, weakRef->streaming_name, "Label" ),
    range(0.0, 1.0, 0.01 )
    {}

    float getValue() const override { return p->value; }
    void setValue(float v) override;
    float getDefaultValue() const override { return 0.5; }
    float getValueForText(const juce::String &text) const override { return std::atof(text.toRawUTF8());}
    const juce::NormalisableRange<float>& getNormalisableRange() const override { return range; }

    juce::NormalisableRange<float> range;
    FakeSurgeParameter *p = nullptr; // don't own it
    ToyJuceAudioProcessor *proc = nullptr;
};

template <typename T, int qSize = 4096> class ToyJuceUIQueue
{
public:
    ToyJuceUIQueue() : af(qSize) {}
    bool push(const T &ad)
    {
        auto ret = false;
        int start1, size1, start2, size2;
        af.prepareToWrite(1, start1, size1, start2, size2);
        if (size1 > 0)
        {
            dq[start1] = ad;
            ret = true;
        }
        af.finishedWrite(size1 + size2);
        return ret;
    }
    bool pop(T &ad)
    {
        bool ret = false;
        int start1, size1, start2, size2;
        af.prepareToRead(1, start1, size1, start2, size2);
        if (size1 > 0)
        {
            ad = dq[start1];
            ret = true;
        }
        af.finishedRead(size1 + size2);
        return ret;
    }
    juce::AbstractFifo af;
    T dq[qSize];
};

class ToyJuceAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    ToyJuceAudioProcessor();
    ~ToyJuceAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

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

    void setParameterFromUI(int id, float f)
    {
        uiMessageQ.push(std::make_pair(id,f));
    }
    ToyJuceUIQueue<std::pair<int,float>> uiMessageQ;

    std::vector<std::unique_ptr<FakeSurgeParameter>> fsparams;
    std::atomic<bool> newValues;

    std::vector<juce::RangedAudioParameter*> params;
private:

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToyJuceAudioProcessor)
};

inline void FSPRangedAdapter::setValue(float v) {
    p->setValueFromDAW(v);
    proc->newValues = true;
}
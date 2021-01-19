/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ToyJuceAudioProcessorEditor  : public juce::AudioProcessorEditor,
         juce::Slider::Listener
{
public:
    ToyJuceAudioProcessorEditor (ToyJuceAudioProcessor&);
    ~ToyJuceAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void sliderValueChanged(juce::Slider *) override;

    struct IdleTimer : juce::Timer {
        IdleTimer(ToyJuceAudioProcessorEditor *ed) : ed(ed) {}
        ~IdleTimer() = default;
        void timerCallback() override { ed->idle(); }
        ToyJuceAudioProcessorEditor *ed;
    };
    void idle();
private:
    std::unique_ptr<IdleTimer> idleTimer;


    struct juceSliderWithParam : public juce::Slider {
        FakeSurgeParameter *p;
    };
    std::vector<std::unique_ptr<juceSliderWithParam>> sliders;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ToyJuceAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ToyJuceAudioProcessorEditor)
};

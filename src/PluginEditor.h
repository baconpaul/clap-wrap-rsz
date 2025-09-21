/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ResizeContents;

class ResizeEditor  : public juce::AudioProcessorEditor
{
public:
    static constexpr int uiW{400}, uiH{250};
    ResizeEditor (ResizeAudioProcessor&);
    ~ResizeEditor();

    void resized() override;
    void paint(juce::Graphics &g) { g.fillAll(juce::Colours::green); }
    void doSize(int);

    std::unique_ptr<ResizeContents> contents;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ResizeAudioProcessor& processor;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResizeEditor)
};

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

#define uiW 400
#define uiH 250

//==============================================================================
/**
*/
class ResizeContents;

class ResizeEditor  : public juce::AudioProcessorEditor
{
public:
    ResizeEditor (ResizeAudioProcessor&);
    ~ResizeEditor();

    void resized() override;
    void paint(juce::Graphics &g) { g.fillAll(juce::Colours::yellow); }
    void doSize(int);

    std::unique_ptr<ResizeContents> contents;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ResizeAudioProcessor& processor;

    float resizeRatio = 1.0f;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ResizeEditor)
};

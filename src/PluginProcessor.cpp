/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;

//==============================================================================
ResizeAudioProcessor::ResizeAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withOutput ("Output", AudioChannelSet::stereo(), true)
        )
{
}

ResizeAudioProcessor::~ResizeAudioProcessor()
{
}

//==============================================================================
const String ResizeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ResizeAudioProcessor::acceptsMidi() const
{
    return true;
}

bool ResizeAudioProcessor::producesMidi() const
{
    return false;
}

bool ResizeAudioProcessor::isMidiEffect() const
{
    return false;
}

double ResizeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ResizeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ResizeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ResizeAudioProcessor::setCurrentProgram (int index)
{
}

const String ResizeAudioProcessor::getProgramName (int index)
{
    return {};
}

void ResizeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ResizeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void ResizeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool ResizeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
        && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;

    return true;
}

void ResizeAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}

//==============================================================================
bool ResizeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ResizeAudioProcessor::createEditor()
{
    return new ResizeEditor (*this);
}

//==============================================================================
void ResizeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void ResizeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ResizeAudioProcessor();
}

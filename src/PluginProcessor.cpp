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
ToyJuceAudioProcessor::ToyJuceAudioProcessor()
    : AudioProcessor (BusesProperties()
                      .withOutput ("Output", AudioChannelSet::stereo(), true)
        )
{
}

ToyJuceAudioProcessor::~ToyJuceAudioProcessor()
{
}

//==============================================================================
const String ToyJuceAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ToyJuceAudioProcessor::acceptsMidi() const
{
    return true;
}

bool ToyJuceAudioProcessor::producesMidi() const
{
    return false;
}

bool ToyJuceAudioProcessor::isMidiEffect() const
{
    return false;
}

double ToyJuceAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ToyJuceAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ToyJuceAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ToyJuceAudioProcessor::setCurrentProgram (int index)
{
}

const String ToyJuceAudioProcessor::getProgramName (int index)
{
    return {};
}

void ToyJuceAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void ToyJuceAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void ToyJuceAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool ToyJuceAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void ToyJuceAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
}

//==============================================================================
bool ToyJuceAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* ToyJuceAudioProcessor::createEditor()
{
    return new ToyJuceAudioProcessorEditor (*this);
}

//==============================================================================
void ToyJuceAudioProcessor::getStateInformation (MemoryBlock& destData)
{
}

void ToyJuceAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ToyJuceAudioProcessor();
}

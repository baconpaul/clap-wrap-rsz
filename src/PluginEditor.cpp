/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;


//==============================================================================
ToyJuceAudioProcessorEditor::ToyJuceAudioProcessorEditor (ToyJuceAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (784, 742);

    int ypos = 30;
    for( auto &p : processor.fsparams )
    {
        auto t = p->streaming_name;
        auto v = p->value;

        std::cout << "Value is " << v << std::endl;

        auto sl = std::make_unique<juceSliderWithParam>();
        sl->p = p.get();
        sl->setRange(0.f, 1.f );
        sl->setBounds( 110, ypos, 300, 28 );
        sl->setValue(v, juce::NotificationType::dontSendNotification);
        sl->addListener(this);
        addAndMakeVisible(sl.get());
        sliders.push_back(std::move(sl));

        ypos += 30;
    }

    idleTimer = std::make_unique<IdleTimer>(this);
    idleTimer->startTimer(1000 / 30);
}

ToyJuceAudioProcessorEditor::~ToyJuceAudioProcessorEditor()
{
}

//==============================================================================
void ToyJuceAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    int ypos = 30;
    for( auto &p : processor.fsparams )
    {
        auto t = p->streaming_name;
        auto v = p->value;

        String s = t + " " + std::to_string(v);
        g.setColour( Colour(255,255,255));
        g.drawText(s, 10, ypos, 100, 20, Justification::centredLeft);

        ypos += 30;
    }
}

void ToyJuceAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void ToyJuceAudioProcessorEditor::sliderValueChanged(juce::Slider *s) {
    auto jsp = dynamic_cast<juceSliderWithParam *>(s);
    if( jsp )
    {
        processor.setParameterFromUI(jsp->p->id, jsp->getValue());
        repaint();
    }
}

void ToyJuceAudioProcessorEditor::idle()
{
    if( processor.newValues )
    {
        processor.newValues = false;
        for( auto &s : sliders )
        {
            if( s->getValue() != s->p->value )
            {
                s->setValue(s->p->value, juce::NotificationType::dontSendNotification);
            }
        }
        repaint();
    }
}

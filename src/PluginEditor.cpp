/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

using namespace juce;


std::array zooms{1.f, 1.5f, 0.75f, 2.f};

class ResizeContents : public juce::Component
{
public:
    ResizeEditor &ed;
    ResizeContents(ResizeEditor &e) : ed(e)
    {
        for (int i=0; i<nSizes; ++i)
        {
            auto b = std::make_unique<juce::TextButton>(std::to_string((int)(zooms[i] * 100)) + "%");
            b->onClick = [i, w = juce::Component::SafePointer(this)](){if (w) w->ed.doSize(i);};
            addAndMakeVisible(*b);
            sizeButtons[i] = std::move(b);
        }
    }

    void paint(juce::Graphics &g) override
    {
        g.fillAll(juce::Colour(0x40, 0x20, 0x00));
        g.setColour(juce::Colours::white);
        g.setFont(11);
        g.drawText(std::string("BUILT ") + __DATE__ + " " + __TIME__, getLocalBounds(), juce::Justification::centred);
        g.drawText(wtd, getLocalBounds().withTrimmedTop(30), juce::Justification::centred);
    }

    void resized() override
    {
        std::cout << getLocalBounds().toString() << std::endl;
        auto lb = getLocalBounds(); // .transformedBy(getTransform().inverted());
        auto bx = lb.reduced(10).withHeight(40);
        auto bw = bx.getWidth() / (nSizes);
        bx = bx.withWidth(bw);
        for (int i=0; i<nSizes; ++i) {
            std::cout << "Button i to " << bx.reduced(2).toString() << std::endl;
            sizeButtons[i]->setBounds(bx.reduced(2));
            bx = bx.translated(bw, 0);
        }
    }

    void setWTD(const juce::String &s) {
        if (s == "Undefined")
            wtd = "CLAP";
        else
            wtd = s;
    }
    juce::String wtd;

    static constexpr int nSizes{4};
    std::array<std::unique_ptr<juce::Button>, nSizes> sizeButtons;
};

//==============================================================================
ResizeEditor::ResizeEditor (ResizeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    contents = std::make_unique<ResizeContents>(*this);
    addAndMakeVisible(*contents);
    setResizable (true, true);
    setResizeLimits (uiW / 2, uiH / 2, uiW * 2, uiH * 2);
    getConstrainer()->setFixedAspectRatio ((double)uiW / (double)uiH);
    doSize(0);
    contents->setWTD(processor.getWrapperTypeDescription(processor.wrapperType));
}

ResizeEditor::~ResizeEditor()
{
}

void ResizeEditor::resized()
{
    contents->setBounds(getLocalBounds().reduced(4).transformedBy(contents->getTransform().inverted()));
}

void ResizeEditor::doSize(int i)
{
    auto z = zooms[i];
    contents->setTransform(juce::AffineTransform().scaled(z));
    contents->setTopLeftPosition(4, 4);
    setSize((int)(uiW * z), (int)(uiH*z));
}

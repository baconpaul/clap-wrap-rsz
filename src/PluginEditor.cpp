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
        setSize((int)uiW, (int)uiH);

    }

    void paint(juce::Graphics &g) override
    {
        g.fillAll(juce::Colour(0x40, 0x20, 0x00));
        g.setColour(juce::Colours::white);
        g.setFont(11);
        g.drawText(std::string("BUILT ") + __DATE__ + " " + __TIME__, getLocalBounds(), juce::Justification::topLeft);
        g.drawText(wtd, getLocalBounds().withTrimmedTop(15), juce::Justification::topLeft);

        g.drawText(ratioString, getLocalBounds().withTrimmedTop(30), juce::Justification::topLeft);
        g.drawText(String(getWidth()) + " x " + String(getHeight()), getLocalBounds().withTrimmedTop(45), juce::Justification::topLeft);
    }

    void resized() override
    {

    }

    void setRatioString(const juce::String& s) 
    { 
        ratioString = s; 
    }

    void setWTD(const juce::String &s) {
        if (s == "Undefined")
            wtd = "CLAP";
        else
            wtd = s;
    }
    juce::String wtd;
    juce::String ratioString;

    static constexpr int nSizes{4};
    std::array<std::unique_ptr<juce::Button>, nSizes> sizeButtons;
};

//==============================================================================
ResizeEditor::ResizeEditor (ResizeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    contents = std::make_unique<ResizeContents>(*this);

    setResizable (true, true);
    setResizeLimits (uiW / 2, uiH / 2, uiW * 2, uiH * 2);
    getConstrainer()->setFixedAspectRatio ((double)uiW / (double)uiH);
    setSize (uiW * resizeRatio, uiH * resizeRatio);
    
    addAndMakeVisible (*contents);
    contents->setSize((int)uiW, (int)uiH);
    resized();

    contents->setWTD(processor.getWrapperTypeDescription(processor.wrapperType));
}

ResizeEditor::~ResizeEditor()
{
}

void ResizeEditor::resized()
{
    resizeRatio = jlimit(0.5, 2.0, (double)getWidth() / (double)uiH);

    auto transform = AffineTransform::scale (resizeRatio);
    if (contents)
    {
        contents->setRatioString(String(resizeRatio));
        contents->setSize(getWidth(), getHeight());
        contents->setTransform(transform);
        contents->setTopLeftPosition(0, 0);
    }
}

void ResizeEditor::doSize(int i)
{
    auto z = zooms[i];
    contents->setTransform(juce::AffineTransform().scaled(z));
    contents->setTopLeftPosition(4, 4);
    setSize((int)(uiW * z), (int)(uiH*z));
}

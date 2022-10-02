/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

// The plugin Editor is where all the visual apperances and look and feel of your plugin come from along with ways to interact.

//==============================================================================

// The constructor is only called on initialization.
ArchitectureBasicsAudioProcessorEditor::ArchitectureBasicsAudioProcessorEditor (ArchitectureBasicsAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // A basic setup of a slider with its style and text box below.
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 50);
    addAndMakeVisible(gainSlider);

    // The attachment is a unique pointer of type AudioProcessorValueTreeState::SliderAttachment.
    // It contains a reference to the apvts, the ID of the parameter, and the slider to which it connects to.
    gainSliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "GAIN", gainSlider);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

// Any objects that need to be safely destroyed happens here.
ArchitectureBasicsAudioProcessorEditor::~ArchitectureBasicsAudioProcessorEditor()
{
}

//==============================================================================

// Paint is what is happening in this very component right now graphics wise.
void ArchitectureBasicsAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

// Where any child components are setup that area meant to be loaded.
void ArchitectureBasicsAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    // The bounds of the component.
    gainSlider.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 50, 200, 100);
}

/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class ArchitectureBasicsAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    ArchitectureBasicsAudioProcessorEditor (ArchitectureBasicsAudioProcessor&);
    ~ArchitectureBasicsAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // When the class is created, it creates from the top down which means when the class is destroyed it is from the bottom up.
    
    // A JUCE slider
    juce::Slider gainSlider;

    // The Slider Attachment goes below the slider so that when the destructor is called the attachment is destroyed before the gain slider.
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainSliderAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    ArchitectureBasicsAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ArchitectureBasicsAudioProcessorEditor)
};

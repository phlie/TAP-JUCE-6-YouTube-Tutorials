#pragma once

#include <JuceHeader.h>
#include "BlueComponent.h"
#include "RedComponent.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent  : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //==============================================================================

    juce::Slider slider1;

    // An instance of the BlueComponent.
    BlueComponent blueComponent;

    // An instance of RedComponent.
    RedComponent redComponent;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

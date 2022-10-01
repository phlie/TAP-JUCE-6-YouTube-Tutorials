/*
  ==============================================================================

    BlueComponent.h
    Created: 1 Oct 2022 1:23:16pm
    Author:  phlie

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class BlueComponent  : public juce::Component
{
public:
    BlueComponent();
    ~BlueComponent() override;

    // Paint is a function that is in our juce::Component class which is overriden because we want our own version of it.
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BlueComponent)
};

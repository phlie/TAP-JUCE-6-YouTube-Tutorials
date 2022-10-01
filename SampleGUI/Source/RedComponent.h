/*
  ==============================================================================

    RedComponent.h
    Created: 1 Oct 2022 1:30:40pm
    Author:  phlie

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class RedComponent  : public juce::Component
{
public:
    RedComponent();
    ~RedComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (RedComponent)
};

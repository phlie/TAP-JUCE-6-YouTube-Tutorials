/*
  ==============================================================================

    BlueComponent.cpp
    Created: 1 Oct 2022 1:23:16pm
    Author:  phlie

  ==============================================================================
*/

#include <JuceHeader.h>
#include "BlueComponent.h"

//==============================================================================
BlueComponent::BlueComponent()
{
}

BlueComponent::~BlueComponent()
{
}

void BlueComponent::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::skyblue);
}

void BlueComponent::resized()
{
}

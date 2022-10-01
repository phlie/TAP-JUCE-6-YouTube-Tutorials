/*
  ==============================================================================

    RedComponent.cpp
    Created: 1 Oct 2022 1:30:40pm
    Author:  phlie

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RedComponent.h"

//==============================================================================
RedComponent::RedComponent()
{


}

RedComponent::~RedComponent()
{
}

void RedComponent::paint (juce::Graphics& g)
{
    // Used to show the total bounds of the component.
    //g.fillAll(juce::Colours::white);

    // Choose the color to paint with.
    g.setColour(juce::Colours::orangered);

    // Fill an Ellipse in the center of the screen.
    g.fillEllipse(getWidth() / 2 - 100, getHeight() / 2 - 100, 200, 200);
}

void RedComponent::resized()
{

}

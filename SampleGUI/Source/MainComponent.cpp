#include "MainComponent.h"

//==============================================================================

// The class constructor, called once which creats the component itself.
MainComponent::MainComponent()
{
    // Any juce objects need to be preceeded with the juce keyword.
    // The SliderStyle is within the Slider class
    // LinearHorizontal is an enum type contained within SliderStyle
    slider1.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);

    // Sets the slider range to be within 0 to 1, although its newInterval value is left as its default of 0, without change.
    // We want it to only be changable within 0.1 increments, so that is the last argument.
    slider1.setRange(0.0f, 1.0f, 0.1f);

    // Sets the textbox below the slider to be of style below, with it being read only and its width and height
    slider1.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);

    // Sets the Sliders default value.
    slider1.setValue(0.5f);

    // Since it is a type of component this Component method while work on it.
    addAndMakeVisible(slider1);

    // Adds a child component to this one and then makes the child component visible.
    addAndMakeVisible(blueComponent);

    // Add and make visible another child component.
    addAndMakeVisible(redComponent);

    // Only happens once when the class is constructed.
    setSize (500, 400);
}

MainComponent::~MainComponent()
{
}

//==============================================================================


// The paint method is for how the app looks graphic design wise and is called quite often.
// This is the main component in which it is responsible for its own graphics and what is actually happening in the component itself.
void MainComponent::paint (juce::Graphics& g)
{
    // The Juce Colours class has many colors already defined which can be accessed for graphics
    g.fillAll (juce::Colours::black);

    /*
    // Set Font allows you to choose a font size.
    g.setFont (juce::Font (32.0f));

    // First you set the color and then you paint with it.
    g.setColour (juce::Colours::orange);
    g.drawText ("Keep it Raving!", getLocalBounds(), juce::Justification::left, true); */
}

// Other components that sit inside of the main component are basically called in here.
// The background or main component holds children which are other components.
void MainComponent::resized()
{
    // Sets the bounds of the child component.
    blueComponent.setBounds(0, 0, getWidth(), getHeight() / 2);

    // The order the components are drawn in is top of the resized() function to the bottom.
    redComponent.setBounds(getWidth() / 2 - 100, getHeight() / 2 - 100, 200, 200);

    // Sets the horizontal slider to be centered in the screen.
    slider1.setBounds(getWidth() / 2 - 200, getHeight() / 2 + 100, 400, 100);
}

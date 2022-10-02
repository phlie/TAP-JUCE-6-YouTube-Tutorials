/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

// Called when the plugin is first created an istantiates everything that is needed.
ArchitectureBasicsAudioProcessor::ArchitectureBasicsAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
// apvts must be explicitly intialized because it does not have a default constructor which is a contstructor without arguments.
// When the constructor is called, before it goes into the body of the constructor, this initialization list is called first.
// The pointer to this class must be dereferenced. Its name is "Parameters", and it uses our layout function.
), apvts(*this, nullptr, "Parameters", createParameters())
#endif
{
}

// The destructor.
ArchitectureBasicsAudioProcessor::~ArchitectureBasicsAudioProcessor()
{
}

//==============================================================================
const juce::String ArchitectureBasicsAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ArchitectureBasicsAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool ArchitectureBasicsAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool ArchitectureBasicsAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double ArchitectureBasicsAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ArchitectureBasicsAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ArchitectureBasicsAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ArchitectureBasicsAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ArchitectureBasicsAudioProcessor::getProgramName (int index)
{
    return {};
}

void ArchitectureBasicsAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================

// Prepare to play is called every time that the button to play within the DAW is called before it actually starts playing.
void ArchitectureBasicsAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void ArchitectureBasicsAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool ArchitectureBasicsAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

// This is where the actual audio comes in, and exits your plugin.
// It is meant to be running at all times while playing and quickly at that.
// This is where the changing of the audio actually happens.

// This is where an audio DSP processes that you are doing do their processing.
// This function is specially designed to run at a quick rate to ensure data is always flowing through the plugin and doesn't slow down the DAW.
// The AudioBuffer is where the audio information is stored in the form of a buffer with its data type being float.
void ArchitectureBasicsAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    //=======================================
    // Don't console out in the process block
    //=======================================

    // Get Raw Parameter Value while return a std::atomic variable which the value of can then be gotten with...
    auto g = apvts.getRawParameterValue("GAIN");

    // ... load(), which actually gets the value safely between threads.
    auto gLoaded = g->load();

    //=============
    // Audio Buffer
    //============

    // Holds information that tells our speakers how to move in and out to produce the sound that our instrument or effect makes.
    // Normally an Audio Buffer has two channels if it is in stereo mode, the Left and the Right, channel.
    // It starts at index 0 and continues to the size of the buffer minus one.
    // Normally audio data needs to be within the range -1.0 to 1.0.
    
    // It is important to know how many channels an Audio Buffer has, along with the total number of samples.
    auto numberOfChannels = buffer.getNumChannels();
    auto numberOfSamplesInBuffer = buffer.getNumSamples();

    // Used to read from the buffer but doesn't actually work to write to the buffer. For the Left channel:
    auto readTheBuffer = buffer.getReadPointer(0);

    // Other times we might want to write to the buffer. For the right channel the code is as follows:
    auto writeTheBuffer = buffer.getWritePointer(1);

    // The standard setup to loop through every sample within every channel.
    for (auto channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        auto* writePointer = buffer.getWritePointer(channel);

        // This loops through each sample in the buffer.
        for (auto sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            // Finally for testing purposes we will create some white noise which is between -1.0 and 1.0 times the gain set by the slider.
            writePointer[sample] = (rand.nextFloat() - 0.5f) * 2.0f * gLoaded;
        }
    }
}

//==============================================================================
bool ArchitectureBasicsAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ArchitectureBasicsAudioProcessor::createEditor()
{
    return new ArchitectureBasicsAudioProcessorEditor (*this);
}

//==============================================================================

// Get State Information allows you to call things for when your plugin is loaded such as variables and parameters.
void ArchitectureBasicsAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

// This is where the state of the plugin is saved before the project is closed.
void ArchitectureBasicsAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

juce::AudioProcessorValueTreeState::ParameterLayout ArchitectureBasicsAudioProcessor::createParameters()
{
    // A vector that contains unique pointers of type Ranged Audio Parameter.
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Push back onto the vector a unique pointer of type Audio Parameter Float with reference name "GAIN".
    // The name the DAW's see, "Gain" is useful for automating parameters wihtin a daw.
    // Finally its the minimum value, maximum value, and the default value.
    params.push_back(std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", 0.0f, 1.0f, 0.5f));

    // Returns the parameter layout.
    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new ArchitectureBasicsAudioProcessor();
}

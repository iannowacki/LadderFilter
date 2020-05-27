/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LadderFilterAudioProcessor::LadderFilterAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, Identifier("PARAMETERS"),
{ std::make_unique<AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 20000.0f),
    std::make_unique<AudioParameterFloat>("resonance", "Resonance", 0.0f, 1.10f, 0.15f),
    std::make_unique<AudioParameterFloat>("drive", "Drive", 1.0f, 25.0f, 1.0f),
    std::make_unique<AudioParameterChoice>("mode", "Filter Type", StringArray("LPF12", "LPF24", "HPF12", "HPF24"), 0)}
    )
#endif
{
    const StringArray params = {"cutoff", "resonance", "drive", "mode"};
    for(int i=0; i<=3; ++i)
    {
        // adds a listener to each parameter in array.
        treeState.addParameterListener(params[i], this);
    }
}

LadderFilterAudioProcessor::~LadderFilterAudioProcessor()
{
}

//==============================================================================
const String LadderFilterAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool LadderFilterAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool LadderFilterAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool LadderFilterAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double LadderFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int LadderFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int LadderFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void LadderFilterAudioProcessor::setCurrentProgram (int index)
{
}

const String LadderFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void LadderFilterAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void LadderFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    dsp::ProcessSpec spec;
    
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    ladderFilter.reset();
    ladderFilter.prepare(spec);
    ladderFilter.setEnabled(true);
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void LadderFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool LadderFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void LadderFilterAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float>block(buffer);
    auto processingContext = dsp::ProcessContextReplacing<float>(block);
    ladderFilter.process(processingContext);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
}

//==============================================================================
bool LadderFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* LadderFilterAudioProcessor::createEditor()
{
    return new LadderFilterAudioProcessorEditor (*this, treeState);
}

//==============================================================================
void LadderFilterAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void LadderFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new LadderFilterAudioProcessor();
}
//==============================================================================
// Function called when parameter changed
void LadderFilterAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
    if(parameterID == "cutoff")
        ladderFilter.setCutoffFrequencyHz(newValue);
    
    else if (parameterID == "resonance")
        ladderFilter.setResonance(newValue);
    
    else if (parameterID == "drive" )
        ladderFilter.setDrive(newValue);
    
    else if (parameterID == "mode")
    {
        switch ((int)newValue) {
        case 0: ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::LPF12);
                break;
        case 1: ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::LPF24);
                break;
        case 2: ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::HPF12);
                break;
        case 3: ladderFilter.setMode(juce::dsp::LadderFilter<float>::Mode::HPF24);
                break;
        
        }
    }
}

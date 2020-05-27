/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LadderFilterAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    LadderFilterAudioProcessorEditor (LadderFilterAudioProcessor&,
AudioProcessorValueTreeState&);
    ~LadderFilterAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    
    Slider cutoffDial;
    Slider resonanceDial;
    Slider driveDial;
    ComboBox modeSel;
    
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> resonanceValue;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> driveValue;
    std::unique_ptr <AudioProcessorValueTreeState::ComboBoxAttachment> modeChoice;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    LadderFilterAudioProcessor& processor;
    AudioProcessorValueTreeState& treeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LadderFilterAudioProcessorEditor)
};

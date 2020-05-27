/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
LadderFilterAudioProcessorEditor::LadderFilterAudioProcessorEditor
(LadderFilterAudioProcessor& p, AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), processor (p), treeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (230, 230);
    
    //Cutoff Frequency
    cutoffValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
    (treeState, "cutoff", cutoffDial);
    cutoffDial.setSliderStyle(Slider::RotaryVerticalDrag);
    cutoffDial.setRange(20.0f, 20000.0f, 0.0f);
    cutoffDial.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox,true, 0, 0);
    addAndMakeVisible(&cutoffDial);
    
    // Resonance
    resonanceValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "resonance", resonanceDial);
    
    // Drive
    driveValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(treeState, "drive", driveDial);
    driveDial.setSliderStyle(Slider::RotaryVerticalDrag);
    driveDial.setRange(1.0f, 25.0f, 1.0f);
    driveDial.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&driveDial);
    
    // Mode Selection
    modeChoice = std::make_unique<AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "mode", modeSel);
    modeSel.addItem("LPF12", 1);
    modeSel.addItem("LPF24", 2);
    modeSel.addItem("HPF12", 3);
    modeSel.addItem("HPF24", 4);
    addAndMakeVisible(&modeSel);
}

LadderFilterAudioProcessorEditor::~LadderFilterAudioProcessorEditor()
{
}

//==============================================================================
void LadderFilterAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::antiquewhite);
    g.setColour (Colours::black);
    
    //Title Text
    g.setFont (30);
    g.drawFittedText ("Ladder Filter", 10, 20, 210, 10, Justification::centred, 1, 0.0f);
    
    //Frequency, Resonance & Drive labels
    g.setFont(25);
    g.drawFittedText("F", 55, 85, 10, 10, Justification::centred, 1, 0.0f);
    g.drawFittedText("R", 165, 85, 10, 10, Justification::centred, 1, 0.0f);
    g.drawFittedText("D", 55, 175, 12, 12, Justification::centred, 1, 0.0f);
    
}

void LadderFilterAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    cutoffDial.setBounds(10, 40, 100, 100);
    resonanceDial.setBounds(120, 40, 100, 100);
    driveDial.setBounds(10, 130, 100, 100);
    modeSel.setBounds(127.5, 169.5, 75, 75);
}

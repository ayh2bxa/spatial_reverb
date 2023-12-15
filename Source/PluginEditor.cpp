/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Spatial_reverbAudioProcessorEditor::Spatial_reverbAudioProcessorEditor (Spatial_reverbAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (200, 400);
    mixSlider.setRange(0.f, 1.f);
    mixSlider.setValue(0.f);
    mixSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    mixSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 100, 25);
    mixSlider.addListener(this);
    addAndMakeVisible(mixSlider);
}

Spatial_reverbAudioProcessorEditor::~Spatial_reverbAudioProcessorEditor()
{
}

//==============================================================================
void Spatial_reverbAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Spatial_reverbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    mixSlider.setBounds(getLocalBounds());
}

void Spatial_reverbAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    if (slider == &mixSlider) {
        audioProcessor.mix = mixSlider.getValue();
    }
}

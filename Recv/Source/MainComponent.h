/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public Component,
                        private InterprocessConnection,
                        private Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void connectionMade() override
    {
        printf("Connected\n");
    }
    
    void connectionLost() override
    {
        printf("Disconnected\n");
    }
    
    void messageReceived (const MemoryBlock& message) override
    {
        ++cnt;
    }
    
    void timerCallback() override
    {
        int c = cnt.exchange (0);
        printf ("%d messages per second\n", c);
    }

private:
    Atomic<int> cnt;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

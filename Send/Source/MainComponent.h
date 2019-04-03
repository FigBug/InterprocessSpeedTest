/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class MainComponent   : public Component,
                        private InterprocessConnection,
                        private Timer,
                        private Thread
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();
    
    void connectionMade() override
    {
        printf("Connected\n");
        connected = true;
        
        startThread();
    }
    
    void connectionLost() override
    {
        printf("Disconnected\n");
        connected = false;
        
        stopThread (1000);
    }
    
    void messageReceived (const MemoryBlock& message) override
    {
    }
    
    void timerCallback() override
    {
        if (! isConnected())
            connectToPipe ("ipcTest", -1);
    }
    
    void run() override
    {
        MemoryBlock mb;
        mb.setSize (64, 0);
        
        while (! threadShouldExit())
        {
            sendMessage (mb);
        }
    }
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    //==============================================================================
    bool connected = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

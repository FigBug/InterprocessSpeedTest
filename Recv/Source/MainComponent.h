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
                        private Timer,
                        private Thread
{
public:
    //==============================================================================
    MainComponent()
        : InterprocessConnection (false), Thread ("UD")
    {
        startTimerHz (1);
        setSize (600, 400);
        
        if (! createPipe ("ipcTest", -1))
            printf ("Can't create pipe\n");
        
        startThread();
    }
    
    ~MainComponent();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void run() override
    {
        MemoryBlock mb;
        mb.setSize (65 * 1024);
        
        if (! sock.bindToPort (54231))
            printf ("Can't bind\n");
        
        while (! threadShouldExit())
        {
            sock.read (mb.getData(), (int) mb.getSize(), true);
            ++cnt;
        }
    }
    
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
    DatagramSocket sock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

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
    enum Mode
    {
        IPC,
        UDP
    };
    
    //==============================================================================
    MainComponent()
      : InterprocessConnection (false),
        Thread ("Sender")
    {
        startTimerHz (1);
        setSize (600, 400);
        
        if (mode == UDP)
            startThread();
    }
    
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
        if (! isConnected() && mode == IPC)
            connectToPipe ("ipcTest", -1);
    }
    
    void run() override
    {
        MemoryBlock mb;
        mb.setSize (64, 0);
        
        while (! threadShouldExit())
        {
            if (mode == IPC)
                sendMessage (mb);
            else if (mode == UDP)
                sock.write ("127.0.0.1", 54231, mb.getData(), (int) mb.getSize());
        }
    }
    
    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    
private:
    //==============================================================================
    bool connected = false;
    Mode mode = UDP;
    DatagramSocket sock;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};

# InterprocessSpeedTest
Testing how fast JUCE's InterprocessConnection is 

Test machine:  
macOS Mojave  
2.9 GHz Intel Core i5  
8 GB 1867 MHz DDR3  
MacBook Pro (Retina, 13-inch, Early 2015)  

InterprocessConnection PIPE - 300,000 messages per second  
DatagramSocket - 120 message per second (wtf?)

Test Machine:  
Windows 10  
3.60 GHz Intel Core i7 4790
32 GB

InterprocessConnection PIPE - 95,000 messages per second  
DatagramSocket - 60 messages per second (wtf?)

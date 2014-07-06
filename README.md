DRA818U/V Radio Module Arduino Library
======
This is a small library which handles the configuration of the Dorji DRA818 radio modules. The datasheet for these modules is somewhat lacking in details, and some quirks were discovered during testing.

To install, copy the DRA818 folder to your Arduino Libraries folder. You should then be able open Arduino and choose the "DRA818_Basic" example from the file mnu. 

Important Note: The DRA818 modules use 3V logic levels for IO. Most Arduino boards operate at 5V, and will need level conversion to connect to the modules safely. 
You can (as far as I've found) use 3.3V logic levels directly, and there are 3.3v Arduino clones available, such as the Seeduino.

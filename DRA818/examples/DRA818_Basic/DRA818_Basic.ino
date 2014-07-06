/*
    DRA818_Basic - Basic example of how to use the DRA818 Configuration Library

    Copyright (C) 2014 Mark Jessop <vk5qi@rfhead.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    For a full copy of the GNU General Public License, 
    see <http://www.gnu.org/licenses/>.
*/

#include <SoftwareSerial.h>
#include "DRA818.h"

//
// IO Definitions
//
#define PTT     10  // PTT pin. This is active low.
#define PD      11  // Power Down pin. This need to start low, then be set high before programming.

//
//  Serial Communication Definitions
//
// The DRA818 Library supports using any Serial communications library that extends the 'Stream' class.
// For our purposes, this means we can either use Hardware Serial, from the 'Serial' library, or we can use
// Software Serial, from the SoftwareSerial library.

// Uncomment the following lines, and change pin numbers as appropriate to use SoftwareSerial.
#define SOFTSERIAL 1
#define DRA_RXD 2   // The Arduino IO line that is connected to the DRA818's TXD pin. 
                    // We *receive* TTL Serial from the DRA818 on this pin.
                    // Only a limited number of Arduino IO lines can be used to RX data.
                    // See http://arduino.cc/en/Reference/SoftwareSerial for more information.

#define DRA_TXD 3   // The Arduino IO line connected to the DRA818's RXD pin.
                    // We *send* TTL serial to the DRA818 on this pin.

SoftwareSerial dra_serial(DRA_RXD, DRA_TXD); // Instantiate the Software Serial Object.
DRA818 dra(&dra_serial, PTT); // Instantiate the DRA818 Control Object, using the SoftwareSerial interface.

// Comment the above, and uncomment the following to use Hardware Serial.
//DRA818 dra(&Serial, PTT);

void setup(){
    // Initialise our Serial interface.
    #ifdef SOFTSERIAL
        dra_serial.begin(9600);
    #else
        Serial.begin(9600);
    #endif

    // Now we configure the DRA818
    pinMode(PD, OUTPUT);
    digitalWrite(PD, HIGH);

    // The following functions are not instantaneously set, you need to call writeFreq to program them.
    dra.setFreq(146.525);
    dra.setTXCTCSS(9); // 9 = 91.5 Hz, See https://en.wikipedia.org/wiki/CTCSS for a list.
    dra.setSquelch(3);  // Squelch level 3.
    dra.setRXCTCSS(0); // No CTCSS on RX.

    dra.writeFreq(); // Write out frequency settings to the DRA module.

    // These functions are instantaneously written to the DRA module.
    dra.setVolume(4); // Set output volume to '4'.

    dra.setFilters(true, true, true); // Sets all filters (Pre/De-Emphasis, High-Pass, Low-Pass) on.

}

void loop(){
    // Key the PTT on and off repeatedly.
    digitalWrite(PTT, LOW); // PTT is Active low, so this turns the PTT on.
    delay(1000);
    digitalWrite(PTT, HIGH); // PTT off.
    delay(1000); 
}
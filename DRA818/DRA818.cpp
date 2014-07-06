/*
    DRA818.cpp - DRA818U/V Comms Library.

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

#include "Arduino.h"
#include "DRA818.h"
#include <stdio.h>
#include <Stream.h>


DRA818::DRA818(Stream *serial, uint8_t PTT){
    this->serial = serial;
    this->PTT_PIN = PTT;
    pinMode(this->PTT_PIN, OUTPUT);
    digitalWrite(this->PTT_PIN, HIGH);

    this->tx_ctcss = 0;
    this->rx_ctcss = 0;
    this->tx_freq =  146.500;

    this->volume = 4;
    this->squelch = 0;
    this->preemph = 0;
    this->highpass = 0;
    this->lowpass = 0;
}


void DRA818::setFreq(float tx_freq){
    if( (tx_freq>136.0 && tx_freq<174.00 ) || (tx_freq>410.0 && tx_freq<480.000) ){
        this->tx_freq = tx_freq;
    }
}

// Refer to https://en.wikipedia.org/wiki/CTCSS for CTCSS values.
void DRA818::setTXCTCSS(uint8_t ctcss){
    if(ctcss<=38){
        this->tx_ctcss = ctcss;
    }
}
void DRA818::setRXCTCSS(uint8_t ctcss){
    if(ctcss<=38){
        this->rx_ctcss = ctcss;
    }
}

void DRA818::setSquelch(uint8_t sql){
    if(sql<=8){
        this->squelch = sql;
    }
}

void DRA818::writeFreq(){
    digitalWrite(this->PTT_PIN, HIGH);// Set PTT off, so we can communicate with the uC.
    delay(100); // Delay for a bit, to let the uC boot up (??)

    char freq_buffer[10];
    dtostrf(this->tx_freq,8,4,freq_buffer);
    sprintf(this->buffer,"AT+DMOSETGROUP=0,%s,%s,%04d,%1d,%04d\r\n",freq_buffer,freq_buffer,this->tx_ctcss,this->squelch,this->rx_ctcss);
    this->serial->write(this->buffer);
}

void DRA818::setVolume(uint8_t vol){
    if(vol>=1 || vol<=8){
        this->volume = vol;
    }

    digitalWrite(this->PTT_PIN, HIGH); // Set PTT off, so we can communicate with the uC.
    delay(100); // Delay for a bit, to let the uC boot up (??)

    sprintf(this->buffer,"AT+DMOSETVOLUME=%1d\r\n",this->volume);
    this->serial->write(this->buffer);
}

void DRA818::setFilters(boolean preemph, boolean highpass, boolean lowpass){
    // Gratuitous use of the ternary operator.
    this->preemph=preemph?0:1;
    this->highpass=highpass?0:1;
    this->lowpass=lowpass?0:1;

    digitalWrite(this->PTT_PIN, HIGH); // Set PTT off, so we can communicate with the uC.
    delay(100); // Delay for a bit, to let the uC boot up (??)

    sprintf(this->buffer,"AT+SETFILTER=%1d,%1d,%1d\r\n",this->preemph,this->highpass,this->lowpass);
    this->serial->write(this->buffer);
}



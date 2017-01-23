/*
    DRA818.h - DRA818U/V Comms Library.

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

#ifndef DRA818_h
#define DRA818_h

#include <Stream.h>

class DRA818 {
    public:
        // Constructors
        DRA818(Stream *serial, uint8_t PTT);

        void setFreq(float freq);

        void setTXCTCSS(uint8_t tx_ctcss);
        void setRXCTCSS(uint8_t rx_ctcss);
        void setSquelch(uint8_t sql);
        void setVolume(uint8_t vol);
		void setFilters(boolean preemph, boolean highpass, boolean lowpass);
        void writeFreq();

    private:
        Stream *serial;
        uint8_t PTT_PIN;
        uint8_t tx_ctcss;
        uint8_t rx_ctcss;
        float tx_freq;
        uint8_t volume;
        uint8_t squelch;
        uint8_t preemph;
        uint8_t highpass;
        uint8_t lowpass;

        char buffer[60];
};
#endif
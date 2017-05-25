/*
 * Copyright (C) 2016
 * Authors : ???
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _TM1637_H_
#define _TM1637_H_

#include <stdint.h>


#define ADDR_AUTO  0x40
#define ADDR_FIXED 0x44

#define POSITION_COLON 1

#define DIGIT_UNKOWN 0x08
#define DIGIT_NULL   0x00
#define DIGIT_MINUS  0x40

#define dio MBED_DIP9
#define clk MBED_DIP10

int _off;
int _colon;
uint8_t _brightness;
uint8_t _content[4];

int TM1637_init(int clkpin, int diopin);
int TM1637_output(int light, int colon, uint8_t raw[4]);
int TM1637_send(uint8_t data);
int TM1637_sendRawDigits(int light, uint8_t raw[4]);
int TM1637_output_position(int light,int position, int colon, uint8_t val);
void TM1637_start();
void TM1637_stop();
void TM1637_setBrightness(uint8_t brightness);

#endif

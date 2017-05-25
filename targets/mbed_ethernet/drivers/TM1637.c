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

#include <rflpc17xx/rflpc17xx.h>
#include <TM1637.h>
#include <connectors.h>

const uint8_t DIGIT_TABLE[] = {0x3f, 0x06, 0x5b, 0x4f,
                              0x66, 0x6d, 0x7d, 0x07,
                              0x7f, 0x6f, 0x77, 0x7c,
                              0x39, 0x5e, 0x79, 0x71, 0x63,0x39
                             };

inline uint8_t conv(uint8_t n)
{
   uint8_t segments;

   if (n <= sizeof(DIGIT_TABLE)) {
       segments = DIGIT_TABLE[n];
   }else if (n == 0xFF) {
       segments = DIGIT_NULL;
   } else {
       segments = DIGIT_UNKOWN;
   }

   return segments;
}

void TM1637_start()
{
  rflpc_gpio_set_pin_mode_output(dio, 1);
  rflpc_gpio_set_pin_mode_output(clk, 1);
  rflpc_gpio_set_pin_mode_output(dio, 0);
  rflpc_gpio_set_pin_mode_output(clk, 0);
}

void TM1637_stop()
{
  rflpc_gpio_set_pin_mode_output(clk, 0);
  rflpc_gpio_set_pin_mode_output(dio, 0);
  rflpc_gpio_set_pin_mode_output(clk, 1);
  rflpc_gpio_set_pin_mode_output(dio, 1);
}

int TM1637_init(int clkpin, int diopin)
{
    rflpc_gpio_set_pin_mode_output(diopin, 1);
    rflpc_gpio_set_pin_mode_output(clkpin, 1);
    _brightness = 2;
    _colon      = 0;
    _off        = 1;
    uint8_t i;
    for (i = 0; i < sizeof(_content); i++) {
        _content[i] = DIGIT_NULL;

    }
    TM1637_sendRawDigits(1, _content);

    return 1;
}

int TM1637_output(int light, int colon, uint8_t raw[4])
{
    uint8_t  i;
    for (i = 0; i < 4; i++) {
        _content[i] = conv(raw[i]);
    }
    if (colon) {
        _content[POSITION_COLON] |= 0x80;
    }
    TM1637_start();
    TM1637_send(ADDR_AUTO);
    TM1637_stop();
    TM1637_start();
    TM1637_send(0xC0);
    for (i = 0; i < 4; i++) {
        TM1637_send(_content[i]);
    }
    TM1637_stop();

    TM1637_setBrightness(light);

    return 0;
}

int TM1637_send(uint8_t data)
{
    uint8_t i;
    for (i = 0; i < 8; i++) {
        rflpc_gpio_set_pin_mode_output(clk, 0);
        rflpc_gpio_set_pin_mode_output(dio, data & 1);
        data >>= 1;
        rflpc_gpio_set_pin_mode_output(clk, 1);
    }

    // check ack
    rflpc_gpio_set_pin_mode_output(clk, 0);
    rflpc_gpio_set_pin_mode_output(dio, 1);
    rflpc_gpio_set_pin_mode_output(clk, 1);
    rflpc_gpio_set_pin_mode_input(dio, RFLPC_PIN_MODE_RESISTOR_NONE );

    uint16_t count = 0;
    while (rflpc_gpio_get_val(dio)) {
        count++;
        if (count >= 200) {
            rflpc_gpio_set_pin_mode_output(dio, 1);
            return 0;
        }
    }

    rflpc_gpio_set_pin_mode_output(dio, 1);
    return 1;
}

// Send bit per bit to every segment per column.
// For exemple, to print 9317 it's: TM1637_sendRawDigits(3, {0x6F,0x4F,0x06,0x07})
// If you wanna turn on the colon, you need to put b7 to 1 in the second digit.
// For example with 93:17, its {0x6F,0xCF,0x06,0x07}
//      b0
// b5 |    | b1
//      b6
// b4 |    | b2
//      b3
int TM1637_sendRawDigits(int light, uint8_t raw[4])
{
    uint8_t i;
    for (i=0; i < 4; i++) {
        _content[i] = raw[i];
    }

    TM1637_start();
    TM1637_send(ADDR_AUTO);
    TM1637_stop();
    TM1637_start();
    TM1637_send(0xC0);
    for (i=0; i < 4; i++) {
        TM1637_send(raw[i]);
    }
    TM1637_stop();
    TM1637_setBrightness(light);
    return 0;
}

// brightness can go from 0 to 7
void TM1637_setBrightness(uint8_t brightness)
{
    if (brightness > 7)
        brightness = 7;

    _brightness = brightness;

    TM1637_start();
    TM1637_send(0x88 | _brightness);
    TM1637_stop();
}


int TM1637_output_position(int light,int position, int colon, uint8_t val)
{
    if(position > 4 && position < 0)
        return;

    _content[position]=conv(val);

    if (colon) {
        _content[POSITION_COLON] |= 0x80;
    }

    TM1637_sendRawDigits(light, _content);
    return 0;
}

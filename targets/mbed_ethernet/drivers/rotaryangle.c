/*
 * Copyright (C) 2016
 * Authors : AOUDIA MONCEF, ADANSAR MOHAMED, Alexandre Bécart & Aymeric Ducroquetz based on (Jimmy MARMIN, Mahamoud Mohamed FARAH and Alexandre Bécart work)
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

#include <rotaryangle.h>
#include <stdio.h>
#include <rflpc17xx/rflpc17xx.h>
#include <connectors.h>
#include <base_shield_v20.h>


#define ADC_REF 5//reference voltage of ADC is 5v.If the Vcc switch on the seeeduino
              //board switches to 3V3, the ADC_REF should be 3.3
#define GROVE_VCC 5//VCC of the grove interface is normally 5v
#define FULL_ANGLE 300//full value of the rotary angle is 300 degrees
static rflpc_pin_t _pin;

extern const connector_pins_t CONNECTORS[];

// FIX ADC : A supprimer lors de la prochaine release de RFLPC
static int _pin_to_adc_function(rflpc_pin_t pin)
{
   switch (pin) {
      case RFLPC_PIN_P0_23:
      case RFLPC_PIN_P0_24:
      case RFLPC_PIN_P0_25:
      case RFLPC_PIN_P0_26:
         return 0x01;
      case RFLPC_PIN_P0_3:
      case RFLPC_PIN_P0_2:
         return 0x02;
      case RFLPC_PIN_P1_30:
      case RFLPC_PIN_P1_31:
      default:
         return 0x03;
   }
}
// FIX ADC

void rotary_init(connector_t connector) {
  _pin = CONNECTORS[connector].pin1;
  rflpc_adc_init(_pin, RFLPC_CCLK_8);

  // FIX ADC : A supprimer lors de la prochaine release de RFLPC.
  rflpc_pin_set(_pin, _pin_to_adc_function(_pin), RFLPC_PIN_MODE_RESISTOR_PULL_UP, 0);
  // FIX ADC
}

int rotary_read_angle() {
  rflpc_adc_sample(_pin);
  int sensor_value = rflpc_adc_read(_pin);

  return (sensor_value * ADC_REF * FULL_ANGLE) / (GROVE_VCC * 4095);
}

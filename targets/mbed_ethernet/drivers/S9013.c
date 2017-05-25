/*
 * Copyright (C) 2016
 * Authors : Moncef AOUDIA, Mohamed ADANSAR and Aymeric Ducroquetz
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

#include <S9013.h>
#include <connectors.h>
#include <rflpc17xx/rflpc17xx.h>

extern const connector_pins_t CONNECTORS[];

static rflpc_pin_t _pin;

void init_buzzer(connector_t connector) {
  _pin = CONNECTORS[connector].pin1;

  rflpc_gpio_set_pin_mode_output(_pin, 0);
}

void set_buzzer() {
  rflpc_gpio_set_pin(_pin);
}

void clr_buzzer() {
  rflpc_gpio_clr_pin(_pin);
}

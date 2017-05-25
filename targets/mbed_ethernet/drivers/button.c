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

#include <button.h>
#include <connectors.h>


extern const connector_pins_t CONNECTORS[];

static rflpc_pin_t _pin;

void init_button(connector_t connector) {
  _pin = CONNECTORS[connector].pin1;

  rflpc_gpio_set_pin_mode_input(_pin, RFLPC_PIN_MODE_RESISTOR_PULL_DOWN);
}

int get_value_button() {
  return rflpc_gpio_get_pin(_pin);
}

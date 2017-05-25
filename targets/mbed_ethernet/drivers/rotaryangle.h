/*
 * Copyright (C) 2016
 * Authors : AOUDIA MONCEF ADANSAR MOHAMED based on (Jimmy MARMIN, Mahamoud Mohamed FARAH and Alexandre Bécart work)
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
 
#ifndef _ROTARYANGLE_H_
#define _ROTARYANGLE_H_

#include <rflpc17xx/rflpc17xx.h>
#include <connectors.h>
#include <base_shield_v20.h>

void rotary_init(connector_t connector);

int rotary_read_angle();

#endif //_ROTARYANGLE_H_

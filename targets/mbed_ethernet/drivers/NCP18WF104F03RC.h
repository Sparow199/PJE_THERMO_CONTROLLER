/*  
	authors : Jamal BOUDJAJ
		 Rida Darmal

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.


*/

#ifndef __NCP18WF104F03RC_H
#define __NCP18WF104F03RC_H

#include <rflpc17xx/rflpc17xx.h>
#include <connectors.h>
#include <base_shield_v20.h>


/*Procédure d'initialisation du pin pour utilisation de l'ADC*/
/*Cette procédure remplace la procédure rflpc normalement utilisé 'rfpc_adc_init()' car buggué.*/
void NCP18WF104F03RC_init_pin(rflpc_pin_t analog_pin);


/*Fonction qui retourne la valeur lu par le pin analogique*/
uint16_t NCP18WF104F03RC_read_temp(rflpc_pin_t analog_pin);

#endif

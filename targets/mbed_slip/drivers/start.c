/*
* Copyright or © or Copr. 2010, Thomas SOETE
* 
* Author e-mail: thomas@soete.org
* 
* This software is a computer program whose purpose is to design an
* efficient Web server for very-constrained embedded system.
* 
* This software is governed by the CeCILL license under French law and
* abiding by the rules of distribution of free software.  You can  use, 
* modify and/ or redistribute the software under the terms of the CeCILL
* license as circulated by CEA, CNRS and INRIA at the following URL
* "http://www.cecill.info". 
* 
* As a counterpart to the access to the source code and  rights to copy,
* modify and redistribute granted by the license, users are provided only
* with a limited warranty  and the software's author,  the holder of the
* economic rights,  and the successive licensors  have only  limited
* liability. 
* 
* In this respect, the user's attention is drawn to the risks associated
* with loading,  using,  modifying and/or developing or reproducing the
* software by the user in light of its specific status of free software,
* that may mean  that it is complicated to manipulate,  and  that  also
* therefore means  that it is reserved for developers  and  experienced
* professionals having in-depth computer knowledge. Users are therefore
* encouraged to load and test the software's suitability as regards their
* requirements in conditions enabling the security of their systems and/or 
* data to be ensured and,  more generally, to use and operate it in the 
* same conditions as regards security. 
* 
* The fact that you are presently reading this means that you have had
* knowledge of the CeCILL license and that you accept its terms.
*/

#include <string.h>
#include "types.h"

// Defined by linkscript
struct __cs3_region
{
  unsigned flags;	/* Flags for this region.  None defined yet.  */
  uint8_t *init;	/* Initial contents of this region.  */
  uint8_t *data;	/* Start address of region.  */
  size_t init_size;	/* Size of initial data.  */
  size_t zero_size; 	/* Additional size to be zeroed.  */
};
extern const struct __cs3_region __cs3_regions;

// Program Entry
void main(void);

void _start(void)
{
	// Copy .data
	memcpy(__cs3_regions.data, __cs3_regions.init, __cs3_regions.init_size);

	// Zero .bss
	memset(__cs3_regions.data+__cs3_regions.init_size, 0, __cs3_regions.zero_size);

	// Start main
	main();

	// Loop forever
	while(1);
}

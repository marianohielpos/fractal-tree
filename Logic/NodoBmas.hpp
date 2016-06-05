/*
 * NodoBmas.hpp
 *
 *  Created on: Jun 5, 2016
 *      Author: rorridatos
 */

#ifndef LOGIC_NODOBMAS_HPP_
#define LOGIC_NODOBMAS_HPP_

#include "NodoProducto.hpp"

// Clase Nodo B+
class NodoBmas{
   public:
	NodoProducto claves [5];
	NodoBmas     *ramas [5];
	NodoBmas     *shojas;
	int cuentas;

	// Prototipos
	NodoBmas ();
	virtual ~NodoBmas();
};

#endif /* LOGIC_NODOBMAS_HPP_ */

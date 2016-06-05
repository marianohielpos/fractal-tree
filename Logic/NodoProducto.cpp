/*
 * NodoProducto.cpp
 *
 *  Created on: Jun 5, 2016
 *      Author: rorridatos
 */

#include "NodoProducto.hpp"

// Constructor
NodoProducto::NodoProducto(){
	Codigo      = 0;
	Precio      = 0;
	Descripcion = "";
}
// Constructor
NodoProducto::NodoProducto(int cod, int pres, string des){
	Codigo      = cod;
	Precio      = pres;
	Descripcion = des;
}

NodoProducto::~NodoProducto() {
	// TODO Auto-generated destructor stub
}


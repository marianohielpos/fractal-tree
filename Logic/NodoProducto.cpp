/*
 * NodoProducto.cpp
 *
 *  Created on: Jun 5, 2016
 *      Author: rorridatos
 */

#include "NodoProducto.hpp"

// Constructor
NodoProducto::NodoProducto(){
	ID = 0;
//	Codigo.;
//	Descripcion = "";
}
// Constructor
NodoProducto::NodoProducto(int ide, string cod, string des){
	ID = ide;
	Codigo = cod;
	Descripcion = des;
}

NodoProducto::~NodoProducto() {
	// TODO Auto-generated destructor stub
}


/*
 * NodoProducto.hpp
 *
 *  Created on: Jun 5, 2016
 *      Author: rorridatos
 */

#ifndef LOGIC_NODOPRODUCTO_HPP_
#define LOGIC_NODOPRODUCTO_HPP_

#include <string>
using namespace std;

//Clase NodoProducto
class NodoProducto{
public:
	int  ID;
	string Codigo;
	string Descripcion;

	// Prototipos
	NodoProducto ();
	NodoProducto(int ide, string cod, string des);
	virtual ~NodoProducto();

};

#endif /* LOGIC_NODOPRODUCTO_HPP_ */

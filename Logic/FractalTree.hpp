#ifndef _FRACTALTREE_H_
#define _FRACTALTREE_H_
/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * f-tree.h
 * Copyright (C) 2016 Rorri Datos <rncorral@yahoo.com.ar>
 *
 * fractal-tree.git is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * fractal-tree.git is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <fstream>
#include <string>
//#include "../Common/Node.hpp"
//#include "../DataAccess/Persistance.hpp"
using namespace std;

//Clase NodoProducto
class NodoProducto{
	public:
	int    Codigo;
	int    Precio;
	string Descripcion;

	// Prototipos
	NodoProducto ();
	NodoProducto(int cod, int pres, string des);
};

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

// Clase Nodo B+
class NodoBmas{
    public:
	NodoProducto claves [5];
	NodoBmas     *ramas [5];
	NodoBmas     *shojas;
	int cuentas;

	// Prototipos
	NodoBmas ();
};

// Costructor
NodoBmas::NodoBmas(){
    cuentas = 0;
}

class FractalTree
{
public:
	NodoBmas *raiz, *Xr, *P, *N, *vsam;
	int k, cuentas, MAX, MIN, nivel;
	NodoProducto mediana;
	bool esta, ea;
	double contT, contTot;
	int eli;
	int arreglo[50];
	//bandera es del archivo maestro, y bandera2
    int bandera, bandera2;
	//Prototipos
	FractalTree(){
		cuentas = k = 0;
		esta    = ea = false;
		MAX     = 4;
		MIN     = 2;
		nivel   =0;
		vsam    = raiz = P = N = Xr = NULL;
		contT= contTot=bandera = bandera2 = eli =0;
	}
	void refrescar ();
	void insertar (NodoProducto);
	void empujar(NodoProducto, NodoBmas *);
	void meterHoja();
	bool arbolVacio(NodoBmas *);
	void dividir ();
	void doblar (NodoBmas *);
	//imprime el arbol en orden por la referencia de la raiz
	void print_rec ();
	void print_rec_aux (NodoBmas *nodo);//auxiliar
	bool buscarNodo (NodoProducto clave, NodoBmas *nodo);
	bool buscar (NodoProducto clave, NodoBmas *nodo);
	//busca si una clace existe o no en el arbol
	bool buscar (NodoProducto clave);
	//da la altura
	int  Altura ();
	//imprime en anchura
	void Anchura();
	void Anchura_aux (NodoBmas *, int , int);
	//imprime por niveles auxiliar de anchura aux
	void ImprimeNivel(NodoBmas *, int);
	//imprime por la referencia de orden
	void Imprimir ();
	//carga el archivo de productos
	void Cargar();

	/***********  Recorridos **************************/

	void postOrdenRecursivo(NodoBmas *r);
	void postOrdenIterativo(NodoBmas *r);
	void preOrdenRecursivo(NodoBmas *r);
	void preOrdenIterativo(NodoBmas *r);

	void postOrdenRecursivoAux(NodoBmas *r);
	void postOrdenIterativoAux(NodoBmas *r);
	void preOrdenRecursivoAux(NodoBmas *r);
	void preOrdenIterativoAux(NodoBmas *r);

	//bool buscarNodo (int clave, Node *pagina);
	bool Buscar (int clave);
	//elimina al archivo
	void Eliminar(int);
	//ve si c esta en el archivo
	int Esta(int c);
	NodoProducto* Encontrar(int c);

	bool EstaArreglo(int num);
	void ImprimirArreglo();

protected:

private:
	 

};

#endif // _F_TREE_H_


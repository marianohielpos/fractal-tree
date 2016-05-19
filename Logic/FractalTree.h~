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

#ifndef _FRACTALTREE_H_
#define _FRATREE_H_

class FractalTree
{
public:
	Node *raiz, *Xr, *P, *N, *vsam;
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
	void empujar(NodoProducto, Node *);
	void meterHoja();
	bool arbolVacio(Node *);
	void dividir ();
	void doblar (Node *);
	//imprime el arbol en orden por la referencia de la raiz
	void print_rec ();
	void print_rec_aux (Node *nodo);//auxiliar
	bool buscarNodo (NodoProducto clave, Node *nodo);
	bool buscar (NodoProducto clave, Node *nodo);
	//busca si una clace existe o no en el arbol
	bool buscar (NodoProducto clave);
	//da la altura
	int  Altura ();
	//imprime en anchura
	void Anchura();
	void Anchura_aux (Node *, int , int);
	//imprime por niveles auxiliar de anchura aux
	void ImprimeNivel(Node *, int);
	//imprime por la referencia de orden
	void Imprimir ();
	//carga el archivo de productos
	void Cargar();

	/***********  Recorridos **************************/

	void postOrdenRecursivo(Node *r);
	void postOrdenIterativo(Node *r);
	void preOrdenRecursivo(Node *r);
	void preOrdenIterativo(Node *r);

	void postOrdenRecursivoAux(Node *r);
	void postOrdenIterativoAux(Node *r);
	void preOrdenRecursivoAux(Node *r);
	void preOrdenIterativoAux(Node *r);

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


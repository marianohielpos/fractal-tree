/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * f-tree.cc
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
#include "../Logic/FractalTree.hpp"

// Metodo refrescar
void FractalTree::refrescar(){
	nivel = Altura ();
	NodoBmas *aux = raiz;

	while (!arbolVacio(aux->ramas[0]))
		aux= aux->ramas[0];

	vsam = aux;
}

// Metodo de Insertar
void FractalTree::insertar (NodoProducto clave){
	ea = false;
	empujar (clave, raiz);
	if(ea){
		NodoBmas *nuevo = new NodoBmas();
		nuevo->cuentas = 1;
		nuevo->claves[1] = mediana;
		nuevo->ramas [0] = raiz;
		nuevo->ramas [1] = Xr;
		raiz = nuevo;
	}
	refrescar();
}

// Metodo Empujar
void FractalTree::empujar (NodoProducto clave, NodoBmas *nodo){
	if(nodo == NULL){
		ea= true;
		mediana= clave;
		Xr= NULL;
	}
	else{
		esta = buscarNodo (clave, nodo);
		if(esta)
			cout << "\nCodigo Repetido: "<< clave.Codigo << endl;
		else{
			empujar (clave, nodo->ramas[k]);
			buscarNodo(clave, nodo);

			if(ea){
				if(nodo->cuentas < MAX){
					//cout << "Voy a meterhoja!" <<endl;
					ea = false;
					P = nodo;
					// Usa las variables globales
					meterHoja();
				}
				else{
					//cout << "Voy a dividir!" << endl;
					ea = true;
					P = nodo;
					// Usa las variables globales.
					dividir();
				}
			}
		}
	}
}

// Metodo Meter Hoja que usa las variables globales: Mediana, P, K, Xr
void FractalTree::meterHoja(){
	for(int i = P->cuentas; i >= k + 1; i--){
			P->claves[i + 1] = P->claves[i];
			P->ramas [i + 1] = P->ramas [i];
	}
	P->claves[k + 1] = mediana;
	P->ramas [k + 1] = Xr;
	P->cuentas++;
}

// Metodo Dividir Nodo que usa las variables asignadas por Meter Hoja Mediana, P, K, Xr.
void FractalTree::dividir(){
	NodoBmas *mde = new NodoBmas();
	int pos;

	if (k <= MIN)
		pos= MIN;
	else
		pos= MIN+1;

	for(int i= pos+1; i <= MAX; i++){
		mde->claves[i-pos] = P->claves[i];
		mde->ramas [i-pos] = P->ramas [i];
	}

	mde->cuentas = MAX-pos;
	P->cuentas = pos;

	if (k <= MIN)
		meterHoja();
	else{
		k = k-pos;
		NodoBmas *aux = P;
		P = mde;
		meterHoja();
		P = aux;
	}
	mediana = P->claves[P->cuentas];

	if(arbolVacio(P->ramas[0]))
		doblar(mde);

	mde->ramas[0] = P->ramas[P->cuentas];
	mde->shojas = P->shojas;
	P->shojas = mde;

	P->cuentas--;
	Xr= mde;
}

// Metodo que duplica un Nodo
void FractalTree::doblar (NodoBmas *mde){
	for(int i = mde->cuentas; i >= 1; i--){
		mde->claves[i + 1] = mde->claves[i];
		mde->ramas [i + 1] = mde->ramas [i];
	}
	mde->claves[ 1] = mediana;
	mde->cuentas++;
}

// Metodo Arbol Vacio
bool FractalTree::arbolVacio(NodoBmas *nodo){
    return ((nodo == NULL) || (nodo->cuentas == 0));
}

// Metodo buscar que retorna si el nodo existe o no
bool FractalTree::buscar(NodoProducto clave){
	return buscarNodo (clave, raiz);
}

// Metodo buscar que retorna si el nodo existe o no
bool FractalTree::buscar(NodoProducto clave, NodoBmas *nodo){
	if(nodo->cuentas == 0)
		esta = false;
	else{
		buscarNodo(clave, nodo);
		if(esta)
			N= nodo;
		else
			esta = buscar(clave, nodo->ramas[k]);
	}
	return esta;
}

// Metodo buscar nodo
bool FractalTree::buscarNodo(NodoProducto clave, NodoBmas *nodo){
        if(nodo == NULL)
        	return false;
        else{
			if(clave.Codigo < nodo->claves[1].Codigo){
					k = 0;
					return esta = false;
			}
			else{
				k = nodo->cuentas;
				while((k > 1) && (clave.Codigo <nodo->claves[k].Codigo))
					k--;

				esta = (clave.Codigo == nodo->claves[k].Codigo);
			}
			return esta;
        }
}

// Realiza un Imprimir Recursivo
void FractalTree::print_rec (){
    if (!arbolVacio(raiz)){
        print_rec_aux(raiz);
        cout << endl;
    }
    else
    	cout << "\nEl Arbol B+ esta Vacio!" << endl;
}

// Metodo auxiliar de print_rec
void FractalTree::print_rec_aux (NodoBmas *nodo){
	if(!arbolVacio(nodo)){
		print_rec_aux (nodo->ramas[0]);
		for(int i = 1; i <= nodo->cuentas; i++){
			cout << nodo->claves[i].Codigo << " ";
			print_rec_aux (nodo->ramas[i]);
		}
	}
}

// Metodo que retorna la Altura del arbol B+
int FractalTree::Altura (){
	int res = 0;
	NodoBmas *aux = raiz;
	if (arbolVacio(aux)){
		cout << "\nEl Arbol B+ esta Vacio!" << endl;
		return 0;
	}
	else{
		while (!arbolVacio(aux)){
			res++;
			aux = aux->ramas[0];
		}
		return res;
	}
}


// Realiza el recorrido en Anchura
void FractalTree:: Anchura(){
	int largo = Altura();
	int con = 1;
	NodoBmas *pg = raiz;
	cout<<"Impresion del arbol B+ en anchura:"<<endl;
	Anchura_aux (pg, largo, con);
	cout << endl;
}

// Metodo auxiliar de Anchura
void FractalTree:: Anchura_aux (NodoBmas *nodo, int largo, int con){
	if (arbolVacio(nodo)){
	}
	else{
		if (largo >= con){
			ImprimeNivel (nodo, con);
			con++;
			Anchura_aux(nodo,largo, con);
		}
	}
}

void FractalTree::ImprimeNivel (NodoBmas *nodo, int con){
	if(arbolVacio(nodo)){
	}
	else{
		if (con == 1){
			for(int i= 1; i<= nodo->cuentas; i++){
				cout<<nodo->claves[i].Codigo<<" ";
			}
		}
		else{
			con--;
			for(int r= 0; r <= nodo->cuentas; r++)
				ImprimeNivel(nodo->ramas[r], con);
		}
	}
}

// Metodo Imprimir Arbol B+
void FractalTree ::Imprimir (){
	NodoBmas *aux= vsam;
	if (arbolVacio(aux))
		cout << "\nEl Arbol B+ esta Vacio!" << endl;
	else{
		cout<<"Impresion del arbol B+:"<<endl;
		while (!arbolVacio(aux)){
			for (int i= 1; i <= aux->cuentas; i++)
				cout<<aux->claves[i].Codigo<<" ";
			aux = aux->shojas;
		}
	}
	cout << endl;
}

/****************************/

bool FractalTree::Buscar(int c){
    int i;

    NodoBmas *nodo = vsam;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->cuentas); i++){
            if (nodo->claves[i].Codigo == c){
                return  true;
            }
        }
        nodo = (*nodo).shojas;
    }
    return false;
}

//ve si el el codigo c existe
int FractalTree:: Esta(int c){
    int i;
    NodoBmas *nodo = vsam;
    while (nodo != NULL){
        i = 0;
        for(; i <= ((nodo->cuentas) - 1); i++){
            if (nodo->claves[i].Codigo == c)
            return  true;
        }
        nodo = (*nodo).shojas;
    }
    return false;
}

//encuentra y retorna el nodo buscado
NodoProducto* FractalTree:: Encontrar(int c){
    int i;
    NodoBmas *nodo = vsam;
    NodoProducto *siesta;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->cuentas); i++){
            if (nodo->claves[i].Codigo == c){
                siesta = new NodoProducto (nodo->claves[i].Codigo ,
				nodo->claves[i].Precio, nodo->claves[i].Descripcion);/////ojo
                return  siesta;
            }
        }
        nodo = (*nodo).shojas;
    }
    return NULL;
}

/*******************************************************************************************/
/*******************************************************************************************/

void FractalTree::preOrdenRecursivo(NodoBmas *raiz){
	preOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativa */
void FractalTree::preOrdenRecursivoAux(NodoBmas *raiz){

	NodoBmas *pg = raiz;

	if( raiz != NULL ){

		cout << pg->claves[1].Codigo << " ";

		// llamada recursiva por la primera hoja
		this->preOrdenRecursivoAux(pg->ramas[0]);

		if(pg->ramas[0] != NULL){
			// llamada recursiva por la primera hoja
			this->preOrdenRecursivoAux(pg->ramas[1]);
		}

		for(int i = 2; i <= pg->cuentas; i++){

			cout << pg->claves[i].Codigo  << " ";
			this->preOrdenRecursivoAux(pg->ramas[i]);
		}
	}

}

//fstream file7("PostOrRecBmas.txt", ios::out); //archivo salida de recorrido

void FractalTree::postOrdenRecursivo(NodoBmas *raiz){
	postOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma recursiva */
void FractalTree::postOrdenRecursivoAux(NodoBmas *raiz){

	NodoBmas *pg = raiz;

	if( raiz != NULL ){

		// llamada recursiva por la primera hoja
		this->postOrdenRecursivoAux(pg->ramas[0]);

		if(pg->ramas[0] != NULL){
			// llamada recursiva por la primera hoja
			this->postOrdenRecursivoAux(pg->ramas[1]);
		}

		cout << pg->claves[1].Codigo << " ";

		for(int i = 2; i <= pg->cuentas; i++){
			this->postOrdenRecursivoAux(pg->ramas[i]);
			cout << pg->claves[i].Codigo  << " ";

		}
	}
}
/**************************************************************/

//fstream file8("PreOrIteBmas.txt", ios::out); //archivo salida de recorrido

void FractalTree::preOrdenIterativo(NodoBmas *raiz){
	preOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void FractalTree::preOrdenIterativoAux(NodoBmas *raiz){
	NodoBmas *pg = raiz;

	if( raiz != NULL ){

		cout << pg->claves[1].Codigo << " ";

		// llamada recursiva por la primera hoja
		this->preOrdenIterativoAux(pg->ramas[0]);

		if(pg->ramas[0] != NULL){
				// llamada recursiva por la primera hoja
				this->preOrdenIterativoAux(pg->ramas[1]);
		}

		for(int i = 2; i <= pg->cuentas; i++){

			cout << pg->claves[i].Codigo  << " ";
			this->preOrdenIterativoAux(pg->ramas[i]);
		}
	}

}

//fstream file9("PostOrIteBmas.txt", ios::out); //archivo salida de recorrido

void FractalTree::postOrdenIterativo(NodoBmas *raiz){
	postOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void FractalTree::postOrdenIterativoAux(NodoBmas *raiz){
	NodoBmas *pg = raiz;

	if( raiz != NULL ){

		// llamada recursiva por la primera hoja
		this->postOrdenIterativoAux(pg->ramas[0]);

		if(pg->ramas[0] != NULL){
			// llamada recursiva por la primera hoja
			this->postOrdenIterativoAux(pg->ramas[1]);
		}

		cout << pg->claves[1].Codigo << " ";

		for(int i = 2; i <= pg->cuentas; i++){
			this->postOrdenIterativoAux(pg->ramas[i]);
			cout << pg->claves[i].Codigo  << " ";
		}
	}
}



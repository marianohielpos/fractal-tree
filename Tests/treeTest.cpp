#include <iostream>
#include <fstream>
#include <string>
#include "../Logic/FractalTree.hpp"
using namespace std;

int main(){
	FractalTree FT;
	NodoProducto temp;
	cout << "Test Arbol \n";
	temp.ID = 60;
	temp.Codigo = "ABC";
	temp.Descripcion = "Descripcion ABC \n";
	FT.insertar(temp);
	temp.ID = 45;
	temp.Codigo = "ABD";
	temp.Descripcion = "Descripcion ABD \n";
	FT.insertar(temp);
	FT.Imprimir();

	return 0;
}

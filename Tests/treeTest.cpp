#include <iostream>
#include <fstream>
#include <string>
#include "../Logic/FractalTree.hpp"
using namespace std;

int main(){
	FractalTree FT;
	NodoProducto temp;
	cout << "Test Arbol \n";
	temp.ID = 19;
	temp.Codigo = "ABC";
	temp.Descripcion = "Descripcion ABC \n";
	FT.insertar(temp);
	temp.ID = 7;
	FT.insertar(temp);
	temp.ID = 13;
	FT.insertar(temp);
	temp.ID = 37;
	FT.insertar(temp);
	temp.ID = 53;
	FT.insertar(temp);
	/*temp.ID = 2;
	FT.insertar(temp);
	temp.ID = 3;
	FT.insertar(temp);
	temp.ID = 5;
	FT.insertar(temp);
	temp.ID = 17;
	FT.insertar(temp);
	temp.ID = 25;
	FT.insertar(temp);*/

	cout << "altura: " << FT.Altura() << endl;
	FT.Imprimir();
	//FT.Anchura();

	return 0;
}

#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>
using namespace std;

/// vector q retorna un vector con los alfabetos del automata 
vector <char> CargarAlfabeto()
{
	ifstream Archivo("Alfabeto.txt");
	vector <char> Estados;
	char esta;
	
	Archivo >> esta;
	while (!Archivo.eof())
	{
		Estados.push_back(esta);
		Archivo >> esta;	
	}
	Archivo.close();
	return Estados;
}

/// funcion que retona la posicion donde se encuentra la letra del alfabeto
int BuscarLetra(vector<char> Alfabeto, char Letra)
{
	int b;
	for(b=0; b <int(Alfabeto.size()); b++)
	{
		if(Alfabeto[b] == Letra)
			break;
	}
	return b;
}


/// retorna la matriz de incidencia del automata
int** MatrizIncidencia(int CanEstados, int CanLAlfabeto, vector<char> Alfabeto)
{
	int** Matriz;
	Matriz = (int**)malloc(CanEstados * sizeof(int*)); /// Estados
	
	for(int b=0; b <CanEstados; b++)
	{
		Matriz[b] = (int*)malloc(CanLAlfabeto * sizeof(int)); /// Alfabeto
	}
	

	/// Se llena la Matriz de incidencia como si no tuviera transiciones para luego modificarla
	for(int b=0; b <CanEstados; b++)
	{
		for(int c=0; c <CanLAlfabeto; c++)
		{
			Matriz[b][c] = -1;
		}
	}
	
	
	
	/// Se cargan las transiciones en la Matriz de incidencia
	
	///Documento donde estan las transiciones de cada estado
	ifstream Transi("Transiciones.txt");
	
	int Estado, EstadoSig;
	char Transicion;
	
	Transi >> Estado;
	Transi >> EstadoSig;
	Transi >> Transicion;
	
	
	while (!Transi.eof())
	{
		Matriz[Estado][BuscarLetra(Alfabeto, Transicion)] = EstadoSig;
		Transi >> Estado;
		Transi >> EstadoSig;
		Transi >> Transicion;
		
	}
	Transi.close();
	return Matriz;
}


///Funcion de transicion de Estados, para el estado Siguiente
int EstadoSiguiente(vector<char> Alfabeto, int** MatrizIncidencia, int EstadoActual, char Letra)
{
	 /// -2, porq se asume que la letra del alfabeto no existe, si existe se cambiar en el transcurso del siglo
	int PosLetra = -2;
	
	for(int b=0; b<int(Alfabeto.size()); b++)
	{
		if(Alfabeto[b] == Letra)
		{
			PosLetra=b;
			break;
		}
	}
	
	/// Significa que la letra no pertenece al lenguaje del automata
	if(PosLetra==-2)
	{
		return -2;
	}
	else
	{
		return MatrizIncidencia[EstadoActual][PosLetra];
	}
}



///Funcion donde se cargan los estados finales, y q tipo es
multimap<int,string> CargarEstFinales()
{
	multimap<int,string> Finales;
	ifstream Archivo("Finales.txt");
	
	
	
	while(!Archivo.eof())
	{
		int Estado;
		Archivo >> Estado;
		
		string Tipo;
		Archivo >> Tipo;
		
		cout << Tipo << endl;
		Finales.insert(pair<int,string>(Estado, Tipo));
	}
	
	Archivo.close();
	return Finales;
}





int main()
{	
	
	vector<char> Alfabeto = CargarAlfabeto();

	int** Incidencia = MatrizIncidencia(53, int(Alfabeto.size()), Alfabeto);
	
	
	cout << "Estado Siguiente:   " << EstadoSiguiente(Alfabeto, Incidencia, 0, '') << endl;
	
	
	multimap<int,string>  LS;
	LS = CargarEstFinales();
	
	return 0;
	
}

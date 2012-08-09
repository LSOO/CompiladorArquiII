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
	
	
	int Estado;
	Archivo >> Estado;
		
	string Tipo;
	Archivo >> Tipo;
	while(!Archivo.eof())
	{ 
		
		Finales.insert(pair<int,string>(Estado, Tipo));
		Archivo >> Estado;
		
		Archivo >> Tipo;
	}
	
	Archivo.close();
	Finales.insert(pair<int,string>(Estado, Tipo));
	return Finales;
}



/// Funcion que retorna si el estado al que llego es estado final
/// 1 si llego a estado Final, 0 no llego a estado final
int SiEsFinal(multimap<int,string> EFinal, int NEstado)
{
	return EFinal.count(NEstado);	
}
	

/// Funcion que retorna el token al q al que pertenece el estado final
/// Esta funcion se utilizacion cuando SiEsFinal retorna 1, porq si retorna 1 ese estado tiene un token asignado y es un estado final
string TokenEstado(multimap<int,string> EFinal, int NEstado)
{
	return EFinal.find(NEstado)->second;
}

/*
int main()
{	
	
	vector<char> Alfabeto = CargarAlfabeto();

	int** Incidencia = MatrizIncidencia(53, int(Alfabeto.size()), Alfabeto);
	
	
	
	
	multimap<int,string>  LS;
	LS = CargarEstFinales();
	
	cout << "Token Estado Final:   " << TokenEstado(LS, SiEsFinal(LS, EstadoSiguiente(Alfabeto, Incidencia, 0, ';'))) << endl;
	return 0;
	
}*/


int main()
{	
	
	vector<char> Alfabeto = CargarAlfabeto();

	int** Incidencia = MatrizIncidencia(54, int(Alfabeto.size()), Alfabeto);
	
	
	
	int a;
	a = EstadoSiguiente(Alfabeto, Incidencia, 51, ']');
	cout << "Estado Siguiente:   " << a << endl;
	
	
	multimap<int,string>  LS;
	LS = CargarEstFinales();
	
	cout << "Token:   " << TokenEstado(LS, a) << endl;
	
	return 0;
	
}

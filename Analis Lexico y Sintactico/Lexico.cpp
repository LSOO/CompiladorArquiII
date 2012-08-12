#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "ManejadorLineas.h"
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



int main()
{	





	/// ESTO SE CARGA AL INICIO DEL PROGRAMA

	/// Cargo el Alfabeto del Automata
	vector<char> Alfabeto = CargarAlfabeto();


	/// Se Carga Matriz de Incidencia
	int** Incidencia = MatrizIncidencia(52, int(Alfabeto.size()), Alfabeto);


	/// Se Cargan los Estado Finales
	multimap<int,string>  EFinales = CargarEstFinales();













	///


	/// Analisis Lexico Suponiedo que ya tenemos las lineas cargadas
	ManejadorLineas LineasTexto;



	/// Se Cargan las "Lineas"

	LineasTexto.AddInstruc("etiquet:,,,,;"); // Linea 1
	LineasTexto.AddInstruc("ADD [255],R3;"); // Linea 2
	LineasTexto.AddInstruc("ADD R15,200;"); // Linea 3
	LineasTexto.AddInstruc("ADD [R15],R3;"); // Linea 4
	LineasTexto.AddInstruc("ADD R15,[R3];"); // Linea 5
	LineasTexto.AddInstruc("etiquet:,,,,;"); // Linea 6
	LineasTexto.AddInstruc("ADD [255],R3;"); // Linea 7
	LineasTexto.AddInstruc("ADD R15,200;"); // Linea 8
	LineasTexto.AddInstruc("ADD [R15],R3;"); // Linea 9
	LineasTexto.AddInstruc("ADD R15,[R3];"); // Linea 10




	/// varible q endica si puede seguir de linea
	bool PassLinea = true;


	/// Inicio ciclos Analisis Lexcio, Para Sacar el Contenido de cada Linea
	for(int b = 0; b < LineasTexto.CanInst(); b++)
	{
		/// Se Agrega la Linea en un Vector Temporal
		vector<string> Temporal =LineasTexto.SaberInstLinea(b);

		/// Vector temporal donde se van a almacenas los token
		vector<string> Tokens;


		/// Condicion para ver si evaluan las siguiente lineas
		if(PassLinea == true)
		{

			/// Variable q indica si se pasa a tokens
			bool PassToken = true;




			bool LexicoPalLinea = true;

			/// Ciclo que recore las subcadenas de la Linea
			for(int c = 0; c <int(Temporal.size()); c++)
			{

				if(LexicoPalLinea == true)
				{
					///String temporal donde se va a gurdar la subCadena para recorrerla
					string Tempo = Temporal[c];


					/// Estado Inicial del Automta
					int EstadoActual = 0;



					/// Ciclo para recorrer los caracterez
					for(int z = 0; z < int(Tempo.size()); z++)
					{
						EstadoActual = EstadoSiguiente(Alfabeto, Incidencia, EstadoActual, Tempo[z]);



						/// -2 indica que la letra que leyo no pertenece al Alfabeto
						/// -1 que no tiene estado siguiente con esa letra y ese estado
						if(EstadoActual == -1 or EstadoActual == -2)
						{
							cout << "Seria Sacar Aviso, Error en la Palabra " << Temporal[c] << "  de la Instruccion, no Pertenece al Lenguaje:    " << b << endl;
							PassToken = false;
							LexicoPalLinea = false;
							PassLinea = false;
							break;

						}

					}
					if(PassToken == true)
					{
						if(SiEsFinal(EFinales, EstadoActual) == 1)
						{
							Tokens.push_back(TokenEstado(EFinales, EstadoActual));
							//cout << "Token al q pertenece:   "  << TokenEstado(EFinales, EstadoActual) << endl;
						}
						else
						{
							LexicoPalLinea = false;
							PassLinea = false;
							break;
						}

					}
				}
				else
				{
					PassLinea = false;
					break;
				}

			}

			///Aca se Agregaria el token
			LineasTexto.AddTokenLinea(Tokens);
		}
		else
		{
			break;
		}

	}

	if(PassLinea)
	{
		cout << "Paso a Analis Sintactico" << endl;
		cout << "Cantidad Lineas Tokens:   " << LineasTexto.CanTok() << endl;
	}


	return 0;
	
}

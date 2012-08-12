/*
 * Linea.h
 *
 *  Created on: 7/08/2012
 *      Author: Luis Santiago Osorio
 */

#include <iostream>
#include <vector>
using namespace std;


#ifndef LINEA_H_
#define LINEA_H_

class Linea {
private:
	vector<string> Line;

	/// Funciones privadas q sacar las subcadenas de las subcadenas

	/// Modificica la entrada y le agrega ciertos caracteres para que sea mas facil de sacar las subcadena
	string ModiEntrada(string Cadena);

	/// Saca las Subcadenas de las subcadenas
	vector<string> SubCadenas(string Cadena);

public:
	Linea();

	/// PArte las Instruccion en subcadenas para el Analisis Lexico
	void Partir(string Instruccion);


	/// Coje la instruccion ya partida en vectores y la guarda en la clase
	void Partir(vector<string> Instruccion);


	/// Funcion que retorna El contenido de la Linea
	vector<string> SaberLinea();


	/// Funcion que modifica la etiqueta despudes del Analisis Lexico
	/// Osea Elimina la etiqueta que esta en la posicion 0 para luego
	///  Agregarla un diccionario
	void ModiEtLinea();



	/// Modifica el Valor de la Etiqueta en el BRM,BRME,BRMI, Jump
	void ModiValorEtiqueta(int pos, string Valor);

	virtual ~Linea();




};

#endif /* LINEA_H_ */

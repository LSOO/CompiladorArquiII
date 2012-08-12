/*
 * ManejadorLineas.cpp
 *
 *  Created on: 7/08/2012
 *      Author: Luis Santiago Osorio
 */

#include "ManejadorLineas.h"

ManejadorLineas::ManejadorLineas() {
	// TODO Auto-generated constructor stub

}

ManejadorLineas::~ManejadorLineas() {
	// TODO Auto-generated destructor stub
}


void ManejadorLineas::AddInstruc(string Cadena)
{
	/// Linea temporal
	Linea Tem;

	Tem.Partir(Cadena);

	Instruccion.push_back(Tem);


}


void ManejadorLineas::AddInstruc(vector<string> Cadena)
{
	/// Linea temporal
	Linea Tem;
	Tem.Partir(Cadena);

	Instruccion.push_back(Tem);
}



void ManejadorLineas::AddTokenLinea(vector<string> Tokens)
{
	Linea Tem;
	Tem.Partir(Tokens);

	TokensInstr.push_back(Tem);
}



int ManejadorLineas::CanInst()
{
	return int(Instruccion.size());
}


int ManejadorLineas::CanTok()
{
	return int(TokensInstr.size());
}



vector<string> ManejadorLineas::SaberInstLinea(int pos)
{

	return Instruccion[pos].SaberLinea();
}



vector<string> ManejadorLineas::SaberTokLinea(int pos)
{

	return TokensInstr[pos].SaberLinea();
}

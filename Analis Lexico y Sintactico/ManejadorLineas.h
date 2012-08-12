/*
 * ManejadorLineas.h
 *
 *  Created on: 7/08/2012
 *      Author: Luis Santiago Osorio
 */

#ifndef MANEJADORLINEAS_H_
#define MANEJADORLINEAS_H_

#include "Linea.h"

class ManejadorLineas: public Linea {
private:

	vector<Linea> Instruccion;

	vector<Linea> TokensInstr;


public:
	ManejadorLineas();

	void AddInstruc(string Cadena);
	void AddInstruc(vector<string> Cadena);

	void AddTokenLinea(vector<string> Tokens);

	int CanInst();
	int CanTok();


	vector<string> SaberInstLinea(int pos);
	vector<string> SaberTokLinea(int pos);
	virtual ~ManejadorLineas();
};

#endif /* MANEJADORLINEAS_H_ */

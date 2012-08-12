/*
 * Linea.cpp
 *
 *  Created on: 7/08/2012
 *      Author: Luis Santiago Osorio
 */

#include "Linea.h"

Linea::Linea() {
	// TODO Auto-generated constructor stub

}

Linea::~Linea() {
	// TODO Auto-generated destructor stub
}



string Linea::ModiEntrada(string Cadena)
{
	for(int b = 0; b < int(Cadena.size()); b++)
	{
		if(Cadena[b]== 32 or Cadena[b]=='\t') /// Espacion en Blanco ASCII
		{
			Cadena[b] = 32;
		}
	}
	Cadena.append("|");
	return Cadena;
}



vector<string> Linea::SubCadenas(string Cadena)
{
	string tmp = ModiEntrada(Cadena);


		/// Ciclo para parti las cadenas y dejarlas sin espacio
	vector<string> tempo;
	int b = 0;
	while(b < int(tmp.size()))
	{
		if(tmp[b] == 32 or tmp[b] == '|')
		{

			if(int(tmp.substr(0,b).size()) > 0)
			{
				///cout << "Sub Cadena sin espacio:    " << tmp.substr(0,b) << endl;
				string tm = tmp.substr(0,b);
				tm.append("|");
				tempo.push_back(tm);
			}
			tmp.erase(0, b + 1);
			b = 0;
		}
		else
		{
			b++;
		}
	}



	vector<string> Final;

	/// Cilos que Sacan las subcadenas de la Subcadenas
	for(int b=0; b < int(tempo.size()); b++)
	{
		int c=0;
		string temporal = tempo[b];
		while(c < int(temporal.size()))
		{

			if(temporal[c]=='|' or temporal[c]==',' or temporal[c]==';'  or temporal[c]==':')
			{
					/// Hay una , o un ;
				if(int(temporal.substr(0,c).size()) == 0)
				{
					if(temporal[c]!='|')
					{
						string a="";
						a = a + temporal[c];
						Final.push_back(a);
						//cout << "Sub Agregar 1:  " << temporal[c] << endl;
					}

				}

					/// Cuando hay mas de un caracter
				else
				{
					if(temporal[c]==':')

						Final.push_back(temporal.substr(0,c+1));
					else
						Final.push_back(temporal.substr(0,c));


					//cout << "sub Agregar 2:  " << temporal.substr(0,c) << endl;


					if(temporal[c] != '|' and temporal[c]!=':')
					{
						//cout << "sub Agregar 3:  " << temporal[c] << endl;
						string a = "";
						a = a + temporal[c];
						Final.push_back(a);
					}
				}
				temporal.erase(0,c+1);
				c=0;
			}
			else

				c++;
		}
	}



	return Final;
}


void Linea::Partir(string Instruccion)
{
	Line = this->SubCadenas(this->ModiEntrada(Instruccion));
}



void Linea::Partir(vector<string> Instruccion)
{
	Line = Instruccion;
}


vector<string> Linea::SaberLinea()
{
	return Line;
}


void Linea::ModiEtLinea()
{
	Line.erase(Line.begin());
}


void Linea::ModiValorEtiqueta(int pos, string Valor)
{
	Line[pos] = Valor;
}

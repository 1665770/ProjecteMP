#ifndef CANDY_H
#define CANDY_H
#include "utils.h"


using namespace std;

class Candy
{
private:
	TipusCandy m_tipus;
	ColorCandy m_color;
public:
	Candy() { m_tipus = NO_TIPUS; m_color = NO_COLOR; }

	Candy(TipusCandy nouTipus, ColorCandy nouColor) { m_tipus = nouTipus; m_color = nouColor; } //ANDREU
	TipusCandy getTipus() const { return m_tipus; }
	ColorCandy getColor() const { return m_color; }

	void convertirAString(string& color) const; // retorna el candy com a una string

	void setTipus(const TipusCandy& nouTipus) { m_tipus = nouTipus; }
	void setColor(const ColorCandy& nouColor) { m_color = nouColor; }

	bool comprovaCompatibilitat(const Candy& candy2) const { return m_color == candy2.getColor(); } // TRUE SI COMPATIBLES, FALSE SI INCOMPATIBLES
};
Candy StringACandy(const string& stri);

ofstream& operator<<(ofstream& output, const Candy& candy);
ifstream& operator>>(ifstream& input, Candy& candy); // en llegir d'un fitxer et retorna el candy, serveix pel metode inicialitza de partida

Candy StringACandy(const string& stri);

ofstream& operator<<(ofstream& output, const Candy& candy);
ifstream& operator>>(ifstream& input, Candy& candy); // en llegir d'un fitxer et retorna el candy, serveix pel metode inicialitza de partida


#endif
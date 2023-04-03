#include "utils.h"

ostream& operator<<(ostream& output, const Candy& candy)
{
	output << "Caramel " << candy.getColor() << " de tipus " << candy.getTipus() << endl;

	return output;
}

istream& operator>>(istream& input, const Candy& candy)
{
	cout << "Introdueix el color del caramel: "; // no sé
}
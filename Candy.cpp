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

string& convertirAString(string& stri, const Candy& candy)
{
	string color, tipus;
	switch (candy.getColor())
	{
	case 0:
		color = "verd";
		break;
	case 1:
		color = "lila";
		break;
	case 2:
		color = "blau";
		break;
	case 3:
		color = "taronja";
		break;
	case 4:
		color = "vermell";
		break;
	case 5:
		color = "groc";
		break;
	default:
		color = "sense color";
		break;
	}

	switch (candy.getTipus())
	{
	case 0:
		tipus = "normal";
		break;
	case 1:
		tipus = "ratllat";
		break;
	default:
		tipus = "sense tipus";
		break;
	}
	stri = "Caramel " + color + " de tipus " + tipus;
}
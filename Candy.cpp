#include "Candy.h"

Candy StringACandy(const string& stri)
{
	Candy candy;
	if (stri == "R")
	{
		candy.setColor(VERMELL);
		candy.setTipus(NORMAL);
	}
	else if (stri == "O")
	{
		candy.setColor(TARONJA);
		candy.setTipus(NORMAL);
	}
	else if (stri == "Y")
	{
		candy.setColor(GROC);
		candy.setTipus(NORMAL);
	}
	else if (stri == "B")
	{
		candy.setColor(BLAU);
		candy.setTipus(NORMAL);
	}
	else if (stri == "G")
	{
		candy.setColor(VERD);
		candy.setTipus(NORMAL);
	}
	else if (stri == "P")
	{
		candy.setColor(LILA);
		candy.setTipus(NORMAL);
	}
	return candy;
}

//ostream& operator<<(ostream& output, const Candy& candy)
//{
//
//	output << candy.convertirAString();
//
//	return output;
//}

//istream& operator>>(istream& input, const Candy& candy)
//{
//	cout << "Introdueix el color del caramel: "; // no sé
//}

ofstream& operator<<(ofstream& output, const Candy& candy)
{
	string str = "-";
	candy.convertirAString(str);
	output << str;
	return output;
}

ifstream& operator>>(ifstream& input, Candy& candy)
{
	string color;
	input >> color;
	candy = StringACandy(color);
	return input;
}

void Candy::convertirAString(string& color) const
{
	color = "-";

	switch (m_color)
	{
	case VERD:
		color = "G";
		break;
	case LILA:
		color = "P";
		break;
	case BLAU:
		color = "B";
		break;
	case TARONJA:
		color = "O";
		break;
	case VERMELL:
		color = "R";
		break;
	case GROC:
		color = "Y";
		break;
	default:
		break;
	}
	// aquest script cambiara quan fem el ratllat, ara per ara tots son normals
}


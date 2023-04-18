#include "utils.h"

int main()
{
	string nom1 = "CandyCrush.txt";
	string nom2 = "CandyCrushOut.txt";
	Partida partida;
	partida.inicialitza(nom1);
	partida.escriuTauler(nom2);
	return 0;
}
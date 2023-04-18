#include "Partida.h"

int main()
{
	string nom1 = "CandyCrush.txt";
	string nom2 = "CandyCrushOut.txt";
	Partida partida;
	partida.inicialitza(nom1);
	Posicio pos1(2, 1);
	Posicio pos2(2, 2);
	partida.fesMoviment(pos1, pos2);
	partida.escriuTauler(nom2);
	return 0;
}
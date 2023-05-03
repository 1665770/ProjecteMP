#ifndef PARTIDA_H
#define PARTIDA_H
#include "Tauler.h"

class Partida
{
public:
	Partida() { m_nMoviments = 0; m_nObjectius = 0; }
	void inicialitza(const string& nomFitxer);
	void fesMoviment(const Posicio& pos1, const Posicio& pos2);
	void escriuTauler(const string& nomFitxer);
	bool comprovacioH();
	bool comprovacioV();
private:
	Tauler m_tauler;
	Candy m_objectiu;
	int m_nMoviments;
	int m_nObjectius;
	vector <Posicio> PosicionsABorrarH;
	vector <Posicio> PosicionsABorrarV;
	vector <MatchEspecial> CaramelsRatllats;
};

void afegeixPosicions(vector <Posicio> &posicions, Posicio pos);

#endif
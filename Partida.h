#ifndef PARTIDA_H
#define PARTIDA_H
#include "Posicio.h"
#include "Tauler.h"
#include "Candy.h"
#include "utils.h"


class Partida
{
public:
	Partida() { m_nMoviments = 0; m_nObjectius = 0; }
	void inicialitza(const string& nomFitxer);
	void fesMoviment(const Posicio& pos1, const Posicio& pos2);
	void escriuTauler(const string& nomFitxer);
	bool comprovacio();
private:
	Tauler m_tauler;
	Candy m_objectiu;
	int m_nMoviments;
	int m_nObjectius;
};

#endif
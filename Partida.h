#pragma once
#include "utils.h"

class Partida
{
public:
	void inicialitza(const string& nomFitxer);
	void fesMoviment(const Posicio& pos1, const Posicio& pos2);
	void escriuTauler(const string& nomFitxer);

private:
	Tauler m_tauler;

};

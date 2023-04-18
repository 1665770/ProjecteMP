#pragma once
#include "Posicio.h"
#include "Tauler.h"
#include "Candy.h"
#include "utils.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Partida
{
public:
	Partida() { m_nMoviments = 0; m_nObjectius = 0; }
	void inicialitza(const string& nomFitxer);
	void fesMoviment(const Posicio& pos1, const Posicio& pos2);
	void escriuTauler(const string& nomFitxer);
private:
	Tauler m_tauler;
	Candy m_objectiu;
	int m_nMoviments;
	int m_nObjectius;
	bool comprovacio();
};

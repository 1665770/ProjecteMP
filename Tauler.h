#pragma once
#include "Candy.h"
#include "Posicio.h"

using namespace std;

#define N_FILES 10
#define N_COLUMNES 10

class Tauler
{
public:
	void setCandy(const Posicio& pos, const Candy& candy) { m_tauler[pos.GetFila()][pos.GetColumna()] = candy; }
	Candy& GetCandy(const Posicio& pos) { return m_tauler[pos.GetFila()][pos.GetColumna()]; }
private:
	Candy m_tauler[N_FILES][N_COLUMNES];
};

ofstream& operator<<(ofstream& output, Tauler& tauler);
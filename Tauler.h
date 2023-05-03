#ifndef TAULER_H
#define TAULER_H
#include "Candy.h"
#include "Posicio.h"
#include "matchEspecial.h"

using namespace std;

#define N_FILES 10
#define N_COLUMNES 10

class Tauler
{
public:
	Tauler() { indexNouCarmel = 0; } //ANDREU
	void setCandy(const Posicio& pos, const Candy& candy) { m_tauler[pos.GetFila()][pos.GetColumna()] = candy; }
	Candy& GetCandy(const Posicio& pos) { return m_tauler[pos.GetFila()][pos.GetColumna()]; }
	void BorraPosicions(vector<Posicio> PosicionsABorrarH, vector<Posicio> PosicionsABorrarV, vector<MatchEspecial> CaramelsRatllats, Posicio pos1, Posicio pos2, TipusMatch tipus);
	void BaixaCandys();
	void GeneraNousCandys(); //ANDREU
	void CreaRatllat(vector<MatchEspecial> CaramelsRatllats);
	void DeterminaRatllatSecundari(vector<MatchEspecial> CaramelsRatllats);
private:
	Candy m_tauler[N_FILES][N_COLUMNES];
	int indexNouCarmel; //ANDREU
};
ofstream& operator<<(ofstream& output, Tauler& tauler);
ifstream& operator>>(ifstream& input, Tauler& tauler);
#endif
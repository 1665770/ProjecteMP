#ifndef TAULER_H
#define TAULER_H
#include "Candy.h"
#include "Posicio.h"

using namespace std;

#define N_FILES 10
#define N_COLUMNES 10

class Tauler
{
public:
	Tauler() { indexNouCarmel = 0; } //ANDREU
	void setCandy(const Posicio& pos, const Candy& candy) { m_tauler[pos.GetFila()][pos.GetColumna()] = candy; }
	Candy& GetCandy(const Posicio& pos) { return m_tauler[pos.GetFila()][pos.GetColumna()]; }
	void BorraPosicions(Posicio PosicionsABorrarV[], Posicio PosicionsABorrarH[], Posicio CaramelsRatllats[], Posicio pos1, Posicio pos2, TipusMatch tipus);
	void BaixaCandys();
	void GeneraNousCandys(); //ANDREU
	void CreaRatllat(Posicio CaramelsRatllats[], Direccio direccioCaramel[], ColorCandy colorCaramel[]);
	void DeterminaRatllatPrimari(Posicio CaramelsRatllats[],const Posicio& pos1,const Posicio& pos2, Direccio direccioCaramel[], ColorCandy colorCaramel[]);
	void DeterminaRatllatSecundari(Posicio CaramelsRatllats[], Posicio PosicionsABorrarH[], Direccio direccioCaramel[], ColorCandy colorCaramel[]);
private:
	Candy m_tauler[N_FILES][N_COLUMNES];
	int indexNouCarmel; //ANDREU
};

ofstream& operator<<(ofstream& output, Tauler& tauler);
ifstream& operator>>(ifstream& input, Tauler& tauler);
#endif
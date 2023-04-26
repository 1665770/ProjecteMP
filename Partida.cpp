#include "partida.h"

#include "partida.h"
#include "Tauler.h"
#include "Posicio.h"

void Partida::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		string aux;
		int naux;
		Tauler taux;
		fitxer >> aux;
		m_objectiu = StringACandy(aux);
		fitxer >> naux;
		m_nObjectius = naux;
		fitxer >> naux;
		m_nMoviments = naux;
		fitxer >> taux;
		m_tauler = taux;
		fitxer.close();
	}
}

void afegeixPosicions(Posicio posicions[], Posicio pos)
{
	int i = 0;
	bool trobat = false;
	while (i < (N_FILES * N_COLUMNES) && !trobat)
	{
		if (posicions[i] == pos)
		{
			trobat = true;
		}
		else if (posicions[i].GetFila() == -1)
		{
			posicions[i] = pos;
			trobat = true;
		}
		else
			i++;
	}
}

void inicialitzaPosicions(Posicio posicions[])
{
	int i = 0;
	while (posicions[i].GetColumna() != -1)
	{
		posicions[i].inicialitza();
		i++;
	}
}


void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2) //ES DONA PER SOPOSAT QUE LES DUES POSICIONS SÓN CONTIGUES
{
	Candy aux = m_tauler.GetCandy(pos1);
	m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
	m_tauler.setCandy(pos2, aux);

	// arrays que porten les posicions dels candys a borrar diferenciats per match horitzontal i match vertical
	Posicio PosicionsABorrarH[N_FILES * N_COLUMNES];
	Posicio PosicionsABorrarV[N_FILES * N_COLUMNES];
	// array que porta els candy, direccio i la primera posicio,d'on hi ha una fila o columna de 4 candys iguals
	Posicio PosicionsRatllat[N_FILES * N_COLUMNES];
	bool matchH = comprovacioH(PosicionsABorrarH, PosicionsRatllat);
	bool matchV = comprovacioV(PosicionsABorrarV, PosicionsRatllat);
	if (!matchH && !matchV)
	{
		Candy aux = m_tauler.GetCandy(pos1);
		m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
		m_tauler.setCandy(pos2, aux);
	}
	else
	{
		// borra els candis dels arrays de posicions i a més crea els ratllats
		m_tauler.BorraPosicions(PosicionsABorrarH, PosicionsABorrarV, PosicionsRatllat, pos1, pos2, MATCHING_PRIMARI);
		m_tauler.BaixaCandys();
		m_tauler.GeneraNousCandys();
		inicialitzaPosicions(PosicionsABorrarH);
		inicialitzaPosicions(PosicionsABorrarV);
		inicialitzaPosicions(PosicionsRatllat);
		matchH = comprovacioH(PosicionsABorrarH, PosicionsRatllat);
		matchV = comprovacioV(PosicionsABorrarV, PosicionsRatllat);
		while (matchH || matchV)
		{
			m_tauler.BorraPosicions(PosicionsABorrarH, PosicionsABorrarV, PosicionsRatllat, pos1, pos2, MATCHING_SECUNDARI);
			m_tauler.BaixaCandys();
			m_tauler.GeneraNousCandys();
			inicialitzaPosicions(PosicionsABorrarH);
			inicialitzaPosicions(PosicionsABorrarV);
			inicialitzaPosicions(PosicionsRatllat);
			matchH = comprovacioH(PosicionsABorrarH, PosicionsRatllat);
			matchV = comprovacioV(PosicionsABorrarV, PosicionsRatllat);
		}
	}
}

bool Partida::comprovacioH(Posicio posicionsBorrables[], Posicio posicionsRatllat[]) // RETORNA TRUE SI S'HA DE BORRAR ALMENYS UNA POSICIÓ
{
	for (int fila = 0; fila < N_FILES; fila++) // AIXÒ COMPROVA SI HI HA COMPATIBILITAT A LES FILES
	{
		int columna = 0, nConcatenades = 1;
		while (columna < N_COLUMNES - 1 && columna + nConcatenades < N_COLUMNES)
		{
			Posicio posicioActual(fila, columna);

			if (m_tauler.GetCandy(posicioActual).comprovaCompatibilitat(m_tauler.GetCandy(posicioActual.sumaColumna(nConcatenades))))
			{
				nConcatenades++;
				if (nConcatenades == 3)
				{
					afegeixPosicions(posicionsBorrables, posicioActual);
					afegeixPosicions(posicionsBorrables, posicioActual.sumaColumna(nConcatenades - 2));
					afegeixPosicions(posicionsBorrables, posicioActual.sumaColumna(nConcatenades - 1));
				}
				else if (nConcatenades == 4)
				{
					afegeixPosicions(posicionsBorrables, posicioActual.sumaColumna(nConcatenades - 1));
					// guarda la primera posicio de la fila on ha d'apareixer el ratllat
					afegeixPosicions(posicionsRatllat, posicioActual);
				}
				else if (nConcatenades > 4)
				{
					afegeixPosicions(posicionsBorrables, posicioActual.sumaColumna(nConcatenades - 1));
				}
			}
			else
			{
				columna += nConcatenades;
				nConcatenades = 1;
			}

		}
	}
	return (posicionsBorrables[0].GetFila() != -1);
}

bool Partida::comprovacioV(Posicio posicionsBorrables[], Posicio posicionsRatllat[])
{
	for (int columna = 0; columna < N_FILES; columna++) // AIXÒ COMPROVA SI HI HA COMPATIBILITAT A LES COLUMNES
	{
		int fila = 0, nConcatenades = 1;
		while (fila < N_FILES - 1 && fila + nConcatenades < N_FILES)
		{
			Posicio posicioActual(fila, columna);

			if (m_tauler.GetCandy(posicioActual).comprovaCompatibilitat(m_tauler.GetCandy(posicioActual.sumaFila(nConcatenades))))
			{
				nConcatenades++;
				if (nConcatenades == 3)
				{
					afegeixPosicions(posicionsBorrables, posicioActual);
					afegeixPosicions(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 2));
					afegeixPosicions(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 1));
				}
				else if (nConcatenades == 4)
				{
					afegeixPosicions(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 1));
					// guarda la primera posicio de la columna on ha d'apareixer el ratllat
					afegeixPosicions(posicionsRatllat, posicioActual);
				}
				else if (nConcatenades > 4)
				{
					afegeixPosicions(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 1));
				}
			}
			else
			{
				fila += nConcatenades;
				nConcatenades = 1;
			}

		}
	}

	return (posicionsBorrables[0].GetFila() != -1);
}

void Partida::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		fitxer << m_objectiu << " " << m_nObjectius << " " << m_nMoviments << endl;
		fitxer << m_tauler;
		fitxer.close();
	}
}
// intercambia dos Candys de posicio del tauler sempre que La funcio que comprova ho permeti

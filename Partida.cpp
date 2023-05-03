#include "partida.h"

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

void afegeixPosicions(vector <Posicio> &posicions, Posicio pos)
{
	vector<Posicio>::iterator it;
	it = posicions.begin();
	it = find(posicions.begin(), posicions.end(), pos);
	if (it == posicions.end())
	{
		posicions.push_back(pos);
	}
}

void afegeixRatllat(vector <MatchEspecial> &matchRatllat, MatchEspecial m)
{
	/*vector<MatchEspecial>::iterator it;
	it = matchRatllat.begin();
	it = find(matchRatllat.begin(), matchRatllat.end(), m);
	if (it == matchRatllat.end())
	{*/
		matchRatllat.push_back(m);
	//}
}

void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2) //ES DONA PER SOPOSAT QUE LES DUES POSICIONS SÓN CONTIGUES
{
	Candy aux = m_tauler.GetCandy(pos1);
	m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
	m_tauler.setCandy(pos2, aux);

	// arrays que porten les posicions dels candys a borrar diferenciats per match horitzontal i match vertical
	// array que porta els candy, direccio i la primera posicio,d'on hi ha una fila o columna de 4 candys iguals
	bool matchH = comprovacioH();
	bool matchV = comprovacioV();
	if (!matchH && !matchV)
	{
		Candy aux = m_tauler.GetCandy(pos1);
		m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
		m_tauler.setCandy(pos2, aux);
	}
	else
	{
		// borra els candis dels arrays de posicions i a més crea els ratllats
		m_nMoviments--;
		m_tauler.BorraPosicions(PosicionsABorrarH, PosicionsABorrarV, CaramelsRatllats, pos1, pos2, MATCHING_PRIMARI);
		m_tauler.BaixaCandys();
		m_tauler.GeneraNousCandys();
		PosicionsABorrarH.clear();
		PosicionsABorrarV.clear();
		CaramelsRatllats.clear();
		matchH = comprovacioH();
		matchV = comprovacioV();
		while (matchH || matchV)
		{
			m_tauler.BorraPosicions(PosicionsABorrarH, PosicionsABorrarV, CaramelsRatllats, pos1, pos2, MATCHING_SECUNDARI);
			m_tauler.BaixaCandys();
			m_tauler.GeneraNousCandys();
			PosicionsABorrarH.clear();
			PosicionsABorrarV.clear();
			CaramelsRatllats.clear();
			matchH = comprovacioH();
			matchV = comprovacioV();
		}
	}
}

bool Partida::comprovacioH() // RETORNA TRUE SI S'HA DE BORRAR ALMENYS UNA POSICIÓ
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
					afegeixPosicions(PosicionsABorrarH, posicioActual);
					afegeixPosicions(PosicionsABorrarH, posicioActual.sumaColumna(nConcatenades - 2));
					afegeixPosicions(PosicionsABorrarH, posicioActual.sumaColumna(nConcatenades - 1));
				}
				else if (nConcatenades == 4)
				{
					afegeixPosicions(PosicionsABorrarH, posicioActual.sumaColumna(nConcatenades - 1));
					// guarda la primera posicio de la fila on ha d'apareixer el ratllat
					MatchEspecial m(posicioActual, m_tauler.GetCandy(posicioActual).getColor(), HORIZONTAL);
					afegeixRatllat(CaramelsRatllats, m);
				}
				else if (nConcatenades > 4)
				{
					afegeixPosicions(PosicionsABorrarH, posicioActual.sumaColumna(nConcatenades - 1));
				}
			}
			else
			{
				columna += nConcatenades;
				nConcatenades = 1;
			}
		}
	}
	return (PosicionsABorrarH.size() != 0);
}

bool Partida::comprovacioV()
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
					afegeixPosicions(PosicionsABorrarV, posicioActual);
					afegeixPosicions(PosicionsABorrarV, posicioActual.sumaFila(nConcatenades - 2));
					afegeixPosicions(PosicionsABorrarV, posicioActual.sumaFila(nConcatenades - 1));
				}
				else if (nConcatenades == 4)
				{
					afegeixPosicions(PosicionsABorrarV, posicioActual.sumaFila(nConcatenades - 1));
					// guarda la primera posicio de la columna on ha d'apareixer el ratllat
					MatchEspecial m(posicioActual, m_tauler.GetCandy(posicioActual).getColor(), VERTICAL);
					afegeixRatllat(CaramelsRatllats, m);
				}
				else if (nConcatenades > 4)
				{
					afegeixPosicions(PosicionsABorrarV, posicioActual.sumaFila(nConcatenades - 1));
				}
			}
			else
			{
				fila += nConcatenades;
				nConcatenades = 1;
			}

		}
	}

	return (PosicionsABorrarV.size() != 0);
}

void Partida::escriuTauler(const string& nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		//fitxer << m_objectiu << " " << m_nObjectius << " " << m_nMoviments << endl;
		fitxer << m_tauler;
		fitxer.close();
	}
}
// intercambia dos Candys de posicio del tauler sempre que La funcio que comprova ho permeti

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

void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2) //ES DONA PER SOPOSAT QUE LES DUES POSICIONS SÓN CONTINUES
{
	Candy aux = m_tauler.GetCandy(pos1);
	m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
	m_tauler.setCandy(pos2, aux);
	Posicio PosicionsABorrar[N_FILES * N_COLUMNES];
	if (!comprovacio(PosicionsABorrar))
	{
		Candy aux = m_tauler.GetCandy(pos1);
		m_tauler.setCandy(pos1, m_tauler.GetCandy(pos2));
		m_tauler.setCandy(pos2, aux);
	}
	else
	{
		// s'haura de comprovar si hi ha rallat
		m_tauler.BorraPosicions(PosicionsABorrar);
		m_tauler.BaixaCandys(PosicionsABorrar);
		// falta posar els nous candys i repetir
	}
}

bool Partida::comprovacio(Posicio posicionsBorrables[]) // RETORNA TRUE SI S'HA DE BORRAR ALMENYS UNA POSICIÓ
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
				else if (nConcatenades > 3)
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
				else if (nConcatenades > 3)
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

#pragma once

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
		fitxer >> aux;
		m_objectiu = StringACandy(aux);
		fitxer >> naux;
		m_nObjectius = naux;
		fitxer >> naux;
		m_nMoviments = naux;
		for (int i = 0; i < N_FILES; i++)
		{
			for (int j = 0; j < N_COLUMNES; j++)
			{
				Posicio pos(i, j);
				Candy candy;
				fitxer >> candy;
				m_tauler.setCandy(pos, candy);
			}
		}
		fitxer.close();
	}
}

void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2) //ES DONA PER SOPOSAT QUE LES DUES POSICIONS SÓN CONTINUES, S'HAURIA DE COMPROVAR TAMBÉ???
{
	char direccioMoviment=dirMoviment() // S'HA DE SABER EN QUINA DIRECCIÓ ES FA EL CANVI DE CARAMEL PER CARAMEL PER SABER QUINES COMPROVACIONS S'HAN DE FER.
	bool conectivitatHoritzontal = false, conectivitatVertical = false;
	Posicio posicioConectable;
	posicioConectable.setFila(pos2.GetFila());
	posicioConectable.setColumna(pos2.GetColumna() + 1);
	if (m_tauler.GetCandy(pos1).comprovaCompatibilitat(m_tauler.GetCandy(posicioConectable) && posicioConectable.GetColumna()+1<N_COLUMNES) // COMPROVA COMPATIBILITAT HORITZONTAL AMB COLUMNA DE LA DRETA
	{
		conectivitatHoritzontal = true;
	}
	else
	{
		posicioConectable.setColumna(pos2.GetColumna()-1);
		if (m_tauler.GetCandy(pos1).comprovaCompatibilitat(m_tauler.GetCandy(posicioConectable)) && posicioConectable.GetColumna() - 1 > 0) // COMPROVA COMPATIBILITAT HORITZONTAL AMB COLUMNES DE L'ESQUERRA
		{
			conectivitatHoritzontal = true;
		}
	}

	posicioConectable.setColumna(pos2.GetColumna());
	posicioConectable.setFila(pos2.GetFila() + 1);
	if (m_tauler.GetCandy(pos1).comprovaCompatibilitat(m_tauler.GetCandy(posicioConectable) && posicioConectable.GetFila() + 1 < N_FILES)) // COMPROVA COMPATIBILITAT VERTICAL AMB FILA DE BAIX
	{
		conectivitatVertical = true;
	}
	else
	{
		posicioConectable.setFila(pos2.GetFila() - 1);
		if (m_tauler.GetCandy(pos1).comprovaCompatibilitat(m_tauler.GetCandy(posicioVertical)) && posicioConectable.GetFila() - 1 > 0)
		{
			conectivitatVertical = true;
		}
	}

}

void afegeixPosicions(Posicio posicions[], Posicio pos)
{
	int i = 0;
	while (i < (N_FILES * N_COLUMNES))
	{
		if (posicions[i].GetFila() == -1)
		{
			posicions[i] = pos;
			break;
		}
		else
			i++;
	}
}

bool Partida::comprovacio() // RETORNA TRUE SI S'HA DE BORRAR ALMENYS UNA POSICIÓ
{
	Posicio posicionsBorrables[N_FILES * N_COLUMNES]; 

	for (int fila = 0; fila < N_FILES; fila++) // AIXÒ COMPROVA SI HI HA COMPATIBILITAT A LES FILES
	{
		int columna = 0, nConcatenades=1;
		while (columna < N_COLUMNES-1)
		{
			Posicio posicioActual(fila, columna);

			if (m_tauler.GetCandy(posicioActual).comprovaCompatibilitat(m_tauler.GetCandy(posicioActual.sumaColumna(nConcatenades))))
			{
				nConcatenades++;
				if (nConcatenades == 3)
				{
					afegeixPosicio(posicionsBorrables,posicioActual);
					afegeixPosicio(posicionsBorrables, posicioActual.sumaColumna(nConcatenades - 2));
					afegeixPosicio(posicionsBorrables,posicioActual.sumaColumna(nConcatenades-1));
				}
				else if (nConcatenades>3)
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
		while (fila < N_FILES - 1)
		{
			Posicio posicioActual(fila, columna);

			if (m_tauler.GetCandy(posicioActual).comprovaCompatibilitat(m_tauler.GetCandy(posicioActual.sumaFila(nConcatenades))))
			{
				nConcatenades++;
				if (nConcatenades == 3)
				{
					afegeixPosicio(posicionsBorrables, posicioActual);
					afegeixPosicio(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 2));
					afegeixPosicio(posicionsBorrables, posicioActual.sumaFila(nConcatenades - 1));
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

	return (posicionsBorrables[0].GetFila() != -1)
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
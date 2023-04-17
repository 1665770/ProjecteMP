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
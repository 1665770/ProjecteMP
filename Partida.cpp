#include "partida.h"

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

//void Partida::fesMoviment(const Posicio& pos1, const Posicio& pos2)
//{
//
//}
//

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
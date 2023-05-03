#include "Tauler.h"





void DeterminaRatllatPrimari(vector<MatchEspecial> CaramelsRatllats, const Posicio& pos1, const Posicio& pos2)
{
	//com que el match es primari nomes he de comprovar si la primera posicio de caramels ratllats
	//coincideix en fila o columna amb alguna de les posicions
	if (CaramelsRatllats.size() != 0)
	{
		if (pos1.GetColumna() != pos2.GetColumna())
		{
			if (CaramelsRatllats[0].GetFila() == pos1.GetFila())
				CaramelsRatllats[0].setPos(pos1);
			else
				CaramelsRatllats[0].setPos(pos2);
		}
		else
		{
			if (CaramelsRatllats[0].GetColumna() == pos1.GetColumna())
				CaramelsRatllats[0].setPos(pos1);
			else
				CaramelsRatllats[0].setPos(pos2);
		}
	}
	if (CaramelsRatllats.size() > 1)
	{
		if (pos1.GetColumna() != pos2.GetColumna())
		{
			if (CaramelsRatllats[1].GetFila() == pos1.GetFila())
				CaramelsRatllats[1].setPos(pos1);
			else
				CaramelsRatllats[1].setPos(pos2);
		}
		else
		{
			if (CaramelsRatllats[1].GetColumna() == pos1.GetColumna())
				CaramelsRatllats[1].setPos(pos1);
			else
				CaramelsRatllats[1].setPos(pos2);
		}
	}
}

void Tauler::DeterminaRatllatSecundari(vector<MatchEspecial> CaramelsRatllats)
{
	// com ara es match secundari nomes fa falta mirar la direccio perque caramelsRatllats ja esta posat com es vol
	vector<MatchEspecial>::iterator it;
	it = CaramelsRatllats.begin();
	while (it != CaramelsRatllats.end())
	{
		it->cambiaDireccio();
		it++;
	}
}
void Tauler::CreaRatllat(vector<MatchEspecial> CaramelsRatllats)
{
	vector<MatchEspecial>::iterator it;
	it = CaramelsRatllats.begin();
	while (it != CaramelsRatllats.end())
	{
		m_tauler[it->GetFila()][it->GetColumna()].setColor(it->GetColor());
		if (it->GetDir() == HORIZONTAL)
		{
			m_tauler[it->GetFila()][it->GetColumna()].setTipus(RATLLAT_HORIZONTAL);
		}
		else
		{
			m_tauler[it->GetFila()][it->GetColumna()].setTipus(RATLLAT_VERTICAL);
		}
		it++;
	}
}

// cambia els candys del array a candys buits
void Tauler::BorraPosicions(vector<Posicio> PosicionsABorrarH, vector<Posicio> PosicionsABorrarV, vector<MatchEspecial> CaramelsRatllats, Posicio pos1, Posicio pos2, TipusMatch tipus)
{
	// Primer determinarem a on es crearan els ratllats i la seva direccio i color
	if (tipus == MATCHING_PRIMARI)
	{
		DeterminaRatllatPrimari(CaramelsRatllats, pos1, pos2);
	}
	if (tipus == MATCHING_SECUNDARI)
	{
		DeterminaRatllatSecundari(CaramelsRatllats);
	}
	// ara toca borrar els caramels falta detectar si es ratllat i borrar la fila o columna
	int i = 0;
	while (i < PosicionsABorrarH.size())
	{
		if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() != RATLLAT_HORIZONTAL && m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() != RATLLAT_VERTICAL)
		{
			m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].setTipus(NO_TIPUS);
		}
		else if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() == RATLLAT_HORIZONTAL)
		{
			int fila = PosicionsABorrarH[i].GetFila();
			m_tauler[fila][PosicionsABorrarH[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[fila][PosicionsABorrarH[i].GetColumna()].setTipus(NO_TIPUS);
			for (int columna = 0; columna < N_COLUMNES; columna++)
			{
				if (columna != PosicionsABorrarH[i].GetColumna())
				{
					Posicio pos(PosicionsABorrarH[i].GetFila(), columna);
					PosicionsABorrarH.push_back(pos);
				}
			}
		}
		else if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() == RATLLAT_VERTICAL)
		{

			int columna = PosicionsABorrarH[i].GetColumna();
			m_tauler[PosicionsABorrarH[i].GetFila()][columna].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarH[i].GetFila()][columna].setTipus(NO_TIPUS);
			for (int fila = 0; fila < N_FILES; fila++)
			{
				if (fila != PosicionsABorrarH[i].GetFila())
				{
					Posicio pos(fila, PosicionsABorrarH[i].GetColumna());
					PosicionsABorrarH.push_back(pos);
				}
			}
		}
		i++;
	}

	i = 0;

	while (i < PosicionsABorrarV.size())
	{
		if (m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() != RATLLAT_VERTICAL && m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() != RATLLAT_HORIZONTAL)
		{
			m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].setTipus(NO_TIPUS);
		}
		else if (m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() == RATLLAT_HORIZONTAL)
		{
			int fila = PosicionsABorrarV[i].GetFila();
			m_tauler[fila][PosicionsABorrarV[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[fila][PosicionsABorrarV[i].GetColumna()].setTipus(NO_TIPUS);
			for (int columna = 0; columna < N_COLUMNES; columna++)
			{
				if (columna != PosicionsABorrarV[i].GetColumna())
				{
					Posicio pos(fila, columna);
					PosicionsABorrarV.push_back(pos);
				}
			}
		}
		else if (m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() == RATLLAT_VERTICAL)
		{
			int columna = PosicionsABorrarV[i].GetColumna();
			m_tauler[PosicionsABorrarV[i].GetFila()][columna].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarV[i].GetFila()][columna].setTipus(NO_TIPUS);
			for (int fila = 0; fila < N_FILES; fila++)
			{
				if (fila != PosicionsABorrarV[i].GetFila())
				{
					Posicio pos(fila, columna);
					PosicionsABorrarV.push_back(pos);
				}
			}
		}
		i++;
	}
	// finalment creem els ratllats a les posicions que els hi pertoquen
	CreaRatllat(CaramelsRatllats);
}

// Baixa tots els candys que tinguin candys buits a sota
void Tauler::BaixaCandys()
{
	for (int j = 0; j < N_COLUMNES; j++)
	{
		Posicio posicioBuida;
		int i = N_FILES - 1;
		while (i >= 0)
		{
			Posicio pos(i, j);
			//miro la primera pos de candy buit
			if (GetCandy(pos).getColor() == NO_COLOR && posicioBuida.GetColumna() == -1)
			{
				posicioBuida = pos;
			}
			//  si te un candy buit per sota el intercambio i torno el punter a abaix
			else if (GetCandy(pos).getColor() != NO_COLOR && posicioBuida.GetColumna() != -1)
			{
				Candy candyBuit;
				i = posicioBuida.GetFila();
				setCandy(posicioBuida, GetCandy(pos));
				setCandy(pos, candyBuit);
				posicioBuida.setFila(posicioBuida.GetFila() - 1);
			}
			i--;
		}
	}
}

void Tauler::GeneraNousCandys() // FA QUE ES GENERIN NOUS CANDYS A LES POSICIONS BUIDES
{
	for (int fila = N_FILES - 1; fila >= 0; fila--)
	{
		for (int columna = 0; columna < N_COLUMNES; columna++)
		{
			if (m_tauler[fila][columna].getColor() == NO_COLOR)
			{
				ColorCandy nouColor = NO_COLOR;
				switch (indexNouCarmel)
				{
				case 0:
					nouColor = VERMELL;
					break;
				case 1:
					nouColor = TARONJA;
					break;
				case 2:
					nouColor = GROC;
					break;
				case 3:
					nouColor = BLAU;
					break;
				case 4:
					nouColor = VERD;
					break;
				case 5:
					nouColor = LILA;
					break;
				};

				Candy nouCandy(NORMAL, nouColor);
				m_tauler[fila][columna] = nouCandy;
				indexNouCarmel++;
				if (indexNouCarmel == N_TIPUS_CARMELS)
					indexNouCarmel = 0;
			}
		}
	}
}

ofstream& operator<<(ofstream& output, Tauler& tauler)
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			Posicio pos(i, j);
			output << tauler.GetCandy(pos);
			if (j < N_COLUMNES - 1)
			{
				output << " ";
			}
		}
		if (i < N_FILES - 1)
			output << endl;
	}
	return output;
}

ifstream& operator>>(ifstream& input, Tauler& tauler)
{
	for (int i = 0; i < N_FILES; i++)
	{
		for (int j = 0; j < N_COLUMNES; j++)
		{
			Posicio pos(i, j);
			Candy candy;
			input >> candy;
			tauler.setCandy(pos, candy);
		}
	}
	return input;
}
#include "Tauler.h"

void Tauler::DeterminaRatllatPrimari(Posicio CaramelsRatllats[], const Posicio& pos1, const Posicio& pos2, Direccio direccioCaramel[], ColorCandy colorCaramel[])
{
	//com que el match es primari nomes he de comprovar si la primera posicio de caramels ratllats
	//coincideix en fila o columna amb alguna de les posicions
	if (CaramelsRatllats[0].GetColumna() != -1)
	{
		if (pos1.GetColumna() == pos2.GetColumna())
		{
			direccioCaramel[0] = HORIZONTAL;
			if (CaramelsRatllats[0].GetFila() == pos1.GetFila())
				CaramelsRatllats[0] = pos1;
			else
				CaramelsRatllats[0] = pos2;
		}
		else
		{
			direccioCaramel[0] = VERTICAL;
			if (CaramelsRatllats[0].GetColumna() == pos1.GetColumna())
				CaramelsRatllats[0] = pos1;
			else
				CaramelsRatllats[0] = pos2;
		}
		colorCaramel[0] = m_tauler[CaramelsRatllats[0].GetFila()][CaramelsRatllats[0].GetColumna()].getColor();
	}
}

void Tauler::DeterminaRatllatSecundari(Posicio CaramelsRatllats[], Posicio PosicionsABorrarH[], Direccio direccioCaramel[], ColorCandy colorCaramel[])
{
	// com ara es match secundari nomes fa falta mirar la direccio perque caramelsRatllats ja esta posat com es vol
	int i = 0;
	while (CaramelsRatllats[i].GetColumna() != -1)
	{
		if (CaramelsRatllats[i].buscaPosicio(PosicionsABorrarH) != -1)
		{
			direccioCaramel[i] = HORIZONTAL;
		}
		else
		{
			direccioCaramel[i] = VERTICAL;
		}
		colorCaramel[i] = m_tauler[CaramelsRatllats[i].GetFila()][CaramelsRatllats[i].GetColumna()].getColor();
		i++;
	}
}
void Tauler::CreaRatllat(Posicio CaramelsRatllats[], Direccio direccioCaramel[], ColorCandy colorCaramel[])
{
	int i = 0;
	while (CaramelsRatllats[i].GetColumna() != -1)
	{
		m_tauler[CaramelsRatllats[i].GetFila()][CaramelsRatllats[i].GetColumna()].setColor(colorCaramel[i]);
		if (direccioCaramel[i] = HORIZONTAL)
		{
			m_tauler[CaramelsRatllats[i].GetFila()][CaramelsRatllats[i].GetColumna()].setTipus(RATLLAT_HORIZONTAL);
		}
		else
		{
			m_tauler[CaramelsRatllats[i].GetFila()][CaramelsRatllats[i].GetColumna()].setTipus(RATLLAT_VERTICAL);
		}
		i++;
	}
}

// cambia els candys del array a candys buits
void Tauler::BorraPosicions(Posicio PosicionsABorrarH[], Posicio PosicionsABorrarV[], Posicio CaramelsRatllats[], Posicio pos1, Posicio pos2, TipusMatch tipus)
{
	Direccio direccioCaramel[N_COLUMNES * N_FILES];
	ColorCandy colorCaramel[N_COLUMNES * N_FILES];
	// Primer determinarem a on es crearan els ratllats i la seva direccio i color
	if (tipus == MATCHING_PRIMARI)
	{
		DeterminaRatllatPrimari(CaramelsRatllats, pos1, pos2, direccioCaramel, colorCaramel);
	}
	if (tipus == MATCHING_SECUNDARI)
	{
		DeterminaRatllatSecundari(CaramelsRatllats, PosicionsABorrarH, direccioCaramel, colorCaramel);
	}
	// ara toca borrar els caramels falta detectar si es ratllat i borrar la fila o columna
	int i = 0;
	while (PosicionsABorrarH[i].GetColumna() != -1)
	{
		if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() != RATLLAT_HORIZONTAL && m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() != RATLLAT_VERTICAL)
		{
			m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].setTipus(NO_TIPUS);
		}
		else if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() == RATLLAT_HORIZONTAL)
		{
			for (int columna = 0;columna < N_COLUMNES;columna++)
			{
				m_tauler[PosicionsABorrarH[i].GetFila()][columna].setTipus(NO_TIPUS);
				m_tauler[PosicionsABorrarH[i].GetFila()][columna].setColor(NO_COLOR);
			}
		}
		else if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() == RATLLAT_VERTICAL)
		{
			for (int fila = 0;fila < N_FILES;fila++)
			{
				m_tauler[fila][CaramelsRatllats[i].GetColumna()].setTipus(NO_TIPUS);
				m_tauler[fila][CaramelsRatllats[i].GetColumna()].setColor(NO_COLOR);
			}
		}
		i++;
	}

	i = 0;

	while (PosicionsABorrarV[i].GetColumna() != -1)
	{
		if (m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() != RATLLAT_VERTICAL && m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() != RATLLAT_HORIZONTAL)
		{
			m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].setColor(NO_COLOR);
			m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].setTipus(NO_TIPUS);
		}
		else if (m_tauler[PosicionsABorrarV[i].GetFila()][PosicionsABorrarV[i].GetColumna()].getTipus() == RATLLAT_VERTICAL)
		{
			for (int fila = 0;fila < N_FILES;fila++)
			{
				m_tauler[fila][CaramelsRatllats[i].GetColumna()].setTipus(NO_TIPUS);
				m_tauler[fila][CaramelsRatllats[i].GetColumna()].setColor(NO_COLOR);
			}
		}
		else if (m_tauler[PosicionsABorrarH[i].GetFila()][PosicionsABorrarH[i].GetColumna()].getTipus() == RATLLAT_HORIZONTAL)
		{
			for (int columna = 0;columna < N_COLUMNES;columna++)
			{
				m_tauler[CaramelsRatllats[i].GetFila()][columna].setTipus(NO_TIPUS);
				m_tauler[CaramelsRatllats[i].GetFila()][columna].setColor(NO_COLOR);
			}
		}

		i++;
	}
	// finalment creem els ratllats a les posicions que els hi pertoquen
	CreaRatllat(CaramelsRatllats, direccioCaramel, colorCaramel);
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
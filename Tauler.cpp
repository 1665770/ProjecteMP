#include "Tauler.h"

// cambia els candys del array a candys buits
void Tauler::BorraPosicions(Posicio PosicionsABorrar[])
{
	int i = 0;
	while (PosicionsABorrar[i].GetColumna() != -1)
	{
		m_tauler[PosicionsABorrar[i].GetFila()][PosicionsABorrar[i].GetColumna()].setColor(NO_COLOR);
		m_tauler[PosicionsABorrar[i].GetFila()][PosicionsABorrar[i].GetColumna()].setTipus(NO_TIPUS);
		i++;
	}
}

// Baixa tots els candys que tinguin candys buits a sota
void Tauler::BaixaCandys(Posicio PosicionsBorrades[])
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

void Tauler::GeneraNousCandys() //ANDREU // FA QUE ES GENERIN NOUS CANDYS A LES POSICIONS BUIDES
{
	for (int fila = N_FILES-1;fila >= 0;fila++)
	{
		for (int columna = 0;columna < N_COLUMNES;columna++)
		{
			if (m_tauler[fila][columna].getColor() == -1)
			{
				int nouColor;
				switch (indexNouCarmel)
				{
				case 0:
					nouColor = 4;
					break;
				case 1:
					nouColor = 3;
					break;
				case 2:
					nouColor = 5;
					break;
				case 3:
					nouColor = 2;
					break;
				case 4:
					nouColor = 0;
					break;
				case 5:
					nouColor = 1;
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
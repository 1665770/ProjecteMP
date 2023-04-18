#include "Tauler.h"

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
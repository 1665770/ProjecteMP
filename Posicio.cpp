#include "posicio.h"

int Posicio::buscaPosicio(Posicio llista[])
{
	int i = 0;
	bool trobat = false;
	while (llista[i].GetColumna() != -1 && !trobat)
	{
		if (llista[i].GetColumna() == m_columna && llista[i].GetFila() == m_fila)
			trobat = true;
		else
			i++;
	}
	if (!trobat)
		i = -1;
	return i;
}
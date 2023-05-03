#ifndef POSICIO_H
#define POSICIO_H
#include "utils.h"

class Posicio
{
private:
	int m_fila;
	int m_columna;
public:
	Posicio() { m_fila = -1; m_columna = -1; }
	Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; }
	int GetFila() const { return m_fila; }
	int GetColumna() const { return m_columna; }
	void setFila(const int fila) { m_fila = fila; }
	void setColumna(const int columna) { m_columna = columna; }
	void set(int fila, int columna) { m_fila = fila; m_columna = columna; }
	void inicialitza() { m_fila = -1; m_columna = -1; }
	bool esBuit() { return m_fila == -1 && m_columna == -1; }

	Posicio sumaFila(int filaASumar) { Posicio pos(m_fila + filaASumar, m_columna); return pos; }
	Posicio sumaColumna(int ColumnaASumar) { Posicio pos(m_fila, m_columna + ColumnaASumar); return pos; }
	int buscaPosicio(Posicio llista[]);
	bool operator==(const Posicio& pos) { return m_fila == pos.m_fila && m_columna == pos.m_columna; }
};



#endif
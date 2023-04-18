#pragma once

class Posicio
{
private:
	int m_fila;
	int m_columna;
public:
	Posicio(int fila, int columna) { m_fila = fila; m_columna = columna; }
	int GetFila() const { return m_fila; }
	int GetColumna() const { return m_columna; }
	void setFila(const int fila) { m_fila = fila; }
	void setColumna(const int columna) { m_columna = columa; }

	Posicio sumaFila(int filaASumar) { Posicio pos(m_fila+filaASumar,m_columna); return pos; }
	Posicio sumaColumna(int ColumnaASumar) { Posicio pos(m_fila, m_columna+ColumnaASumar); return pos; }
};

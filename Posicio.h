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
};

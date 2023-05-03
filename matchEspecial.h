#ifndef MATCHESPECIAL_H
#define MATCHESPECIAL_H
#include "utils.h"

class MatchEspecial
{
public:
	MatchEspecial() { m_color = NO_COLOR; m_dir = DESCONEGUDA; }
	MatchEspecial(Posicio pos, ColorCandy color, Direccio dir) { m_pos = pos; m_color = color; m_dir = dir; }
	void setPos(Posicio pos) { m_pos = pos; }
	int GetFila() const { return m_pos.GetFila(); }
	int GetColumna() const { return m_pos.GetColumna(); }
	ColorCandy GetColor() const { return m_color; }
	Direccio GetDir() const { return m_dir; }
	void cambiaDireccio() 
	{
		if (m_dir == HORIZONTAL)
			m_dir = VERTICAL;
		else
			m_dir = HORIZONTAL;
	}
private:
	Posicio m_pos;
	ColorCandy m_color;
	Direccio m_dir;
};

#endif
#pragma once

typedef enum
{
	VERD,
	LILA,
	BLAU,
	TARONJA,
	VERMELL,
	GROC,
	NO_COLOR
} ColorCandy;

typedef enum
{
	NORMAL,
	RATLLAT,
	NO_TIPUS
} TipusCandy;

class Candy
{
private:
	TipusCandy m_tipus;
	ColorCandy m_color;

public:
	int getTipus() const { return m_tipus; } // no sé
	int getColor() const { return m_color; } // no sé

	void setTipus(const TipusCandy& nouTipus) { m_tipus = nouTipus; }
	void setColor(const ColorCandy& nouColor) { m_color = nouColor; }

	bool comprovaCompatibilitat(const Candy& candy2) const { return m_tipus == candy2.getTipus(); }
	
};

ostream& operator<<(ostream& output, const Candy& candy);
istream& operator>>(istream& input, const Candy& candy);
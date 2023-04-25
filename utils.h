#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

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
    RATLLAT_HORIZONTAL,
    RATLLAT_VERTICAL,
    NO_TIPUS
} TipusCandy;

typedef enum
{
    MATCHING_PRIMARI,
    MATCHING_SECUNDARI
} TipusMatch;

typedef enum
{
    HORIZONTAL,
    VERTICAL,
    DESCONEGUDA
} Direccio;

#define N_FILES 10
#define N_COLUMNES 10
#define N_TIPUS_CARMELS 6 //ANDREU

#endif
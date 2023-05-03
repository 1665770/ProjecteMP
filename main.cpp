#include "partida.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void llegeixTauler(ifstream& fitxer, char tauler[MAX_FILES][MAX_COLUMNES])
{
	char c;
	int i = 0;
	fitxer >> c;
	while (!fitxer.eof() && (i < MAX_FILES))
	{
		int j = 0;
		cout << "Comment :=>>";
		while (!fitxer.eof() && (j < MAX_COLUMNES))
		{
			cout << " " << c;
			tauler[i][j] = c;
			j++;
			fitxer >> c;
		}
		cout << endl;
		i++;
	}
	fitxer.close();
}


bool comparaTaulers(char taulerResultat[MAX_FILES][MAX_COLUMNES], char taulerEsperat[MAX_FILES][MAX_COLUMNES])
{
	bool iguals = true;
	int i = 0;
	while (iguals && (i < MAX_FILES))
	{
		int j = 0;
		while (iguals && (j < MAX_COLUMNES))
		{
			if (taulerResultat[i][j] != taulerEsperat[i][j])
				iguals = false;
			else
				j++;
		}
		i++;
	}
	return iguals;
}

bool comparaResultatPartida(const string& nomFitxerResultat, const string& nomFitxerEsperat)
{
	bool correcte = false;
	ifstream fitxerEsperat, fitxerResultat;
	char taulerResultat[MAX_FILES][MAX_COLUMNES];
	char taulerEsperat[MAX_FILES][MAX_COLUMNES];

	fitxerEsperat.open(nomFitxerEsperat);
	fitxerResultat.open(nomFitxerResultat);
	if ((!fitxerEsperat.is_open()) || (!fitxerResultat.is_open()))
		cout << "Comment :=>> Error obrint els fitxers de resultat" << endl;
	else
	{
		cout << "Comment :=>> --------------------------" << endl;
		cout << "Comment :=>> RESULTAT ESPERAT PAS A PAS" << endl;
		cout << "Comment :=>> --------------------------" << endl;
		cout << "Comment :=>> " << endl;
		string linia;
		bool resultatFinal = false;
		getline(fitxerEsperat, linia);
		while (!fitxerEsperat.eof() && !resultatFinal)
		{
			cout << "Comment :=>> " << linia << endl;
			if (linia.find("RESULTAT FINAL") != string::npos)
				resultatFinal = true;
			getline(fitxerEsperat, linia);
		}
		if (resultatFinal)
		{
			cout << "Comment :=>> " << linia << endl;
			llegeixTauler(fitxerEsperat, taulerEsperat);
			cout << "Comment :=>> ----------------------------" << endl;
			cout << "Comment :=>> " << endl;
			cout << "Comment :=>> ----------------------------" << endl;
			cout << "Comment :=>> RESULTAT OBTINGUT" << endl;
			cout << "Comment :=>> ----------------------------" << endl;
			cout << "Comment :=>> " << endl;
			llegeixTauler(fitxerResultat, taulerResultat);
			cout << "Comment :=>> ----------------------------" << endl;
			cout << "Comment :=>> " << endl;
			if (comparaTaulers(taulerResultat, taulerEsperat))
			{
				cout << "Comment :=>> RESULTAT CORRECTE" << endl;
				correcte = true;
			}
			else
			{
				cout << "Comment :=>> ERROR. El tauler final no es igual al tauler esperat" << endl;
				correcte = false;
			}
		}
		else
			cout << "Comment :=>> No es pot trobar el resultat final al fitxer amb el resultat esperat" << endl;
	}
	return correcte;



}

int main()
{
	Partida partida;

	float grade = 0.0;
	bool correcte = true;

	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> Iniciant test" << endl;
	cout << "Comment :=>> =============" << endl;
	cout << "Comment :=>> " << endl;


	// NO MATCHING
	cout << "Comment :=>> ---------------------------" << endl;
	cout << "Comment :=>> TEST 1: Intercanvi no valid" << endl;
	cout << "Comment :=>> ---------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_no_matching.txt");
	Posicio posInicial(2, 3);
	Posicio posFinal(2, 4);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_no_matching.txt");
	correcte = comparaResultatPartida("./data/resultat_no_matching.txt", "./data/resultat_no_matching_esperat.txt");
	if (correcte)
		grade += 0.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	//	MATCHING VERTICAL
	cout << "Comment :=>> --------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 2: Intercanvi que genera una combinacio en vertical" << endl;
	cout << "Comment :=>> --------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_matching_vertical.txt");
	posInicial.set(5, 2);
	posFinal.set(5, 3);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_matching_vertical.txt");
	correcte = comparaResultatPartida("./data/resultat_matching_vertical.txt", "./data/resultat_matching_vertical_esperat.txt");
	if (correcte)
		grade += 0.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// MATCHING HORIZONTAL
	cout << "Comment :=>> ----------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 3: Intercanvi que genera una combinacio en horizontal" << endl;
	cout << "Comment :=>> ----------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_matching_horizontal.txt");
	posInicial.set(1, 6);
	posFinal.set(2, 6);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_matching_horizontal.txt");
	correcte = comparaResultatPartida("./data/resultat_matching_horizontal.txt", "./data/resultat_matching_horizontal_esperat.txt");
	if (correcte)
		grade += 0.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// MATCHING VERTICAL + MATCHING HORIZONTAL
	cout << "Comment :=>> ------------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 4: Intercanvi que genera una combinacio en vertical" << endl;
	cout << "Comment :=>>         + Intercanvi que genera una combinacio en horizontal" << endl;
	cout << "Comment :=>> ------------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;	partida.inicialitza("./data/partida_matching_vertical_horizontal.txt");
	posInicial.set(5, 2);
	posFinal.set(5, 3);
	partida.fesMoviment(posInicial, posFinal);
	posInicial.set(1, 6);
	posFinal.set(2, 6);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_matching_vertical_horizontal.txt");
	correcte = comparaResultatPartida("./data/resultat_matching_vertical_horizontal.txt", "./data/resultat_matching_vertical_horizontal_esperat.txt");
	if (correcte)
		grade += 1.0;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// DOBLE MATCHING	
	cout << "Comment :=>> ----------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 5: Intercanvi que genera una dues combinacions alhora" << endl;
	cout << "Comment :=>> ----------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;	
	partida.inicialitza("./data/partida_doble_matching.txt");
	posInicial.set(1, 7);
	posFinal.set(1, 8);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_doble_matching.txt");
	correcte = comparaResultatPartida("./data/resultat_doble_matching.txt", "./data/resultat_doble_matching_esperat.txt");
	if (correcte)
		grade += 1.0;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// MATCHING CASCADA
	cout << "Comment :=>> -------------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 6: Intercanvi que genera una segona combinacio en cadena" << endl;
	cout << "Comment :=>> -------------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_matching_cascada.txt");
	posInicial.set(4, 3);
	posFinal.set(4, 4);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_matching_cascada.txt");
	correcte = comparaResultatPartida("./data/resultat_matching_cascada.txt", "./data/resultat_matching_cascada_esperat.txt");
	if (correcte)
		grade += 1.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// MATCHING DOBLE CASCADA
	cout << "Comment :=>> -------------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 7: Intercanvi que genera una cadena de dues combinacions" << endl;
	cout << "Comment :=>> -------------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_matching_doble_cascada.txt");
	posInicial.set(2, 0);
	posFinal.set(2, 1);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_matching_doble_cascada.txt");
	correcte = comparaResultatPartida("./data/resultat_matching_doble_cascada.txt", "./data/resultat_matching_doble_cascada_esperat.txt");
	if (correcte)
		grade += 1.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// RATLLAT_HORIZONTAL
	cout << "Comment :=>> -----------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 8: Intercanvi que genera un caramel ratllat horizontal" << endl;
	cout << "Comment :=>>         + Intercanvi que elimina el caramel ratllat" << endl;
	cout << "Comment :=>> -----------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_ratllat_horizontal.txt");
	posInicial.set(2, 0);
	posFinal.set(2, 1);
	partida.fesMoviment(posInicial, posFinal);
	posInicial.set(3, 1);
	posFinal.set(4, 1);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_ratllat_horizontal.txt");
	correcte = comparaResultatPartida("./data/resultat_ratllat_horizontal.txt", "./data/resultat_ratllat_horizontal_esperat.txt");
	if (correcte)
		grade += 1.0;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	// RATLLAT_VERTICAL
	cout << "Comment :=>> -----------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 9: Intercanvi que genera un caramel ratllat vertical" << endl;
	cout << "Comment :=>>         + Intercanvi que elimina el caramel ratllat" << endl;
	cout << "Comment :=>> -----------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_ratllat_vertical.txt");
	posInicial.set(3, 2);
	posFinal.set(4, 2);
	partida.fesMoviment(posInicial, posFinal);
	posInicial.set(4, 2);
	posFinal.set(4, 3);
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_ratllat_vertical.txt");
	correcte = comparaResultatPartida("./data/resultat_ratllat_vertical.txt", "./data/resultat_ratllat_vertical_esperat.txt");
	if (correcte)
		grade += 1.0;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;	
	cout << "Comment :=>> " << endl;

	// RATLLAT_HORIZONTAL_CASCADA
	cout << "Comment :=>> --------------------------------------------------------------------------" << endl;
	cout << "Comment :=>> TEST 10: Aparicio caramel ratllat horizontal en una cadena de combinacions" << endl;
	cout << "Comment :=>>          + intercanvi que elimina el caramel ratllat" << endl;
	cout << "Comment :=>> --------------------------------------------------------------------------" << endl;
	cout << "Comment :=>> " << endl;
	partida.inicialitza("./data/partida_ratllat_horizontal_cascada.txt");
	posInicial.set(2, 1);
	posFinal.set(2, 2);
	partida.fesMoviment(posInicial, posFinal);
	posInicial.set(1, 0);
	posFinal.set(1, 1);	
	partida.fesMoviment(posInicial, posFinal);
	partida.escriuTauler("./data/resultat_ratllat_horizontal_cascada.txt");
	correcte = comparaResultatPartida("./data/resultat_ratllat_horizontal_cascada.txt", "./data/resultat_ratllat_horizontal_cascada_esperat.txt");
	if (correcte)
		grade += 1.5;
	cout << "Comment :=>> " << endl;
	cout << "Grade :=>> " << grade << endl << endl;
	cout << "Comment :=>> " << endl;

	cout << "Comment :=>> ------------------------------------------" << endl;
	if (grade == 10.0)
		cout << "Comment :=>> Final del test sense errors" << endl;
	cout << "Grade :=>> " << grade << endl;


	return 0;
}
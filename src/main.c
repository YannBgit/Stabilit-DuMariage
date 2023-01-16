// LIBRAIRIES
#include "constantes.h"

// FONCTIONS
void attribuerPreferences(int **prefH, int **prefF)
{
	// Préférences Hommes
	prefH[0][0] = 1;
	prefH[0][1] = 2;
	prefH[0][2] = 3;
	prefH[0][3] = 4;

	prefH[1][0] = 1;
	prefH[1][1] = 2;
	prefH[1][2] = 3;
	prefH[1][3] = 4;

	prefH[2][0] = 3;
	prefH[2][1] = 1;
	prefH[2][2] = 2;
	prefH[2][3] = 4;

	prefH[3][0] = 2;
	prefH[3][1] = 3;
	prefH[3][2] = 1;
	prefH[3][3] = 4;

	// Préférences Femmes
	prefF[0][0] = 3;
	prefF[0][1] = 4;
	prefF[0][2] = 1;
	prefF[0][3] = 2;

	prefF[1][0] = 2;
	prefF[1][1] = 3;
	prefF[1][2] = 4;
	prefF[1][3] = 1;

	prefF[2][0] = 1;
	prefF[2][1] = 2;
	prefF[2][2] = 3;
	prefF[2][3] = 4;

	prefF[3][0] = 3;
	prefF[3][1] = 4;
	prefF[3][2] = 2;
	prefF[3][3] = 1;
}

int min(int a, int b)
{
	if(a < b)
	{
		return a;
	}

	else
	{
		return b;
	}
}

void attribuerMariages(int **prefH, int **prefF, int **nbrMariages)
{
	
}

void afficherMariages(int **mariages, int n)
{
	for(int i = 0; i < n; i++)
	{
		printf("Mariage n°%d : H%d + F%d\n", i, mariages[i][0], mariages[i][1]);
	}
}

// MAIN
int main()
{
	// Initialisation des variables
	int prefH[NBR_HOMMES][NBR_FEMMES];
	int prefF[NBR_FEMMES][NBR_HOMMES];
	int nbrMariages = min(NBR_HOMMES, NBR_FEMMES);
	int mariages[nbrMariages][COUPLE];

	attribuerPreferences(prefH, prefF);

	// Attribution des mariages
	attribuerMariages(prefH, prefF, nbrMariages);

	// Affichage
	afficherMariages(mariages, nbrMariages);

	// Fin
	exit(0);
}
// LIBRAIRIES
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "constantes.h"

// FONCTIONS
uint8_t **allouerMemoire(uint8_t n, uint8_t m)
{
	uint8_t **matrice = malloc(n * sizeof(uint8_t *));

	for(uint8_t i = 0; i < n; i++)
	{
		matrice[i] = malloc(m * sizeof(uint8_t));
	}

	return matrice;
}

void libererMemoire(uint8_t **matrice, uint8_t n, uint8_t m)
{
	for(uint8_t i = 0; i < m; i ++)
	{
		free(matrice[i]);
	}

	free(matrice);
}

void attribuerPreferences(uint8_t **prefH, uint8_t **prefF)
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

uint8_t min(uint8_t a, uint8_t b)
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

void initSelection(uint8_t **selection)
{
	for(uint8_t i = 0; i < NBR_FEMMES; i++)
	{
		for(uint8_t j = 0; j < NBR_HOMMES; j++)
		{
			selection[i][j] = NBR_HOMMES;
		}
	}
}

void attribuerMariages(uint8_t **prefH, uint8_t **prefF, uint8_t nbrMariages, uint8_t **mariages)
{
	uint8_t **selection = allouerMemoire(NBR_FEMMES, NBR_HOMMES);
	initSelection(selection);

	for(uint8_t i = 0; i < NBR_FEMMES; i++)
	{
		for(uint8_t j = 0; j < NBR_HOMMES; j++)
		{
			// Les hommes se proposent à leur femme préférée et celle-ci ne retient que celui qu'elle préfère
			if(prefH[j][i] < selection[i][j])
			{
				selection[prefH[j][i]][i] = j;
			}
		}
	}

	for(uint8_t i = 0; i < nbrMariages; i++)
	{
		mariages[i][0] = selection[i][0];
		mariages[i][1] = selection[i][0];
	}

	libererMemoire(selection, NBR_FEMMES, NBR_HOMMES);
}

void afficherMariages(uint8_t **mariages, uint8_t nbrMariages)
{
	for(uint8_t i = 0; i < nbrMariages; i++)
	{
		printf("Mariage n°%d : H%d + F%d\n", i, mariages[i][0], mariages[i][1]);
	}
}

// MAIN
int main()
{
	// Initialisation des variables
	uint8_t **prefH = allouerMemoire(NBR_HOMMES, NBR_FEMMES);
	uint8_t **prefF = allouerMemoire(NBR_FEMMES, NBR_HOMMES);
	attribuerPreferences(prefH, prefF);

	uint8_t nbrMariages = min(NBR_HOMMES, NBR_FEMMES);

	uint8_t **mariages = allouerMemoire(nbrMariages, COUPLE);

	// Attribution des mariages
	attribuerMariages(prefH, prefF, nbrMariages, mariages);

	// Affichage
	afficherMariages(mariages, nbrMariages);

	// Libération de la mémoire
	libererMemoire(mariages, nbrMariages, COUPLE);
	libererMemoire(prefF, NBR_FEMMES, NBR_HOMMES);
	libererMemoire(prefH, NBR_HOMMES, NBR_FEMMES);

	// Fin
	exit(0);
}
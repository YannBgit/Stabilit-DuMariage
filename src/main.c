// LIBRAIRIES
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include "constantes.h"

// FONCTIONS
uint8_t *allouerMemoire1D(uint8_t n)
{
	uint8_t *matrice = malloc(n * sizeof(uint8_t));

	return matrice;
}

uint8_t **allouerMemoire2D(uint8_t n, uint8_t m)
{
	uint8_t **matrice = malloc(n * sizeof(uint8_t *));

	for(uint8_t i = 0; i < n; i++)
	{
		matrice[i] = malloc(m * sizeof(uint8_t));
	}

	return matrice;
}

void libererMemoire1D(uint8_t *matrice, uint8_t n)
{
	free(matrice);
}

void libererMemoire2D(uint8_t **matrice, uint8_t n, uint8_t m)
{
	for(uint8_t i = 0; i < m; i ++)
	{
		free(matrice[i]);
	}

	free(matrice);
}

int min(int a, int b)
{
	if(a < b)
	{
		return a;
	}

	return b;
}

int max(int a, int b)
{
	if(a > b)
	{
		return a;
	}

	return b;
}

void initPreferences(uint8_t **prefH, uint8_t **prefF)
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

void initMariages(uint8_t *mariages, int nbrMariages)
{
	for(uint8_t i = 0; i < nbrMariages; i++)
	{
		mariages[i] = max(NBR_HOMMES, NBR_FEMMES);
	}
}

void attribuerMariages(uint8_t **prefH, uint8_t **prefF, uint8_t *mariages, int nbrMariages)
{
	// Les hommes se proposent aux femmes qui ne retiennt que celui qu'elles préfèrent

	while(1 != 1) // Tant que tous les individus du groupe de taille minimum n'ont pas trouvé de partenaire
	{
		// Les hommes rejetés se proposent à leur choix suivant qui les retient ou non. Si retenu, l'homme dont on a pris la place devra se proposer à son tour.
	}
}

void afficherMariages(uint8_t *mariages, int nbrMariages)
{
	for(uint8_t i = 0; i < nbrMariages; i++)
	{
		printf("Mariage n°%d : H%d + F%d\n", i, mariages[i], i);
	}
}

// MAIN
int main()
{
	// Initialisation des variables
	int nbrMariages = min(NBR_HOMMES, NBR_FEMMES);

	uint8_t **prefH = allouerMemoire2D(NBR_HOMMES, NBR_FEMMES);
	uint8_t **prefF = allouerMemoire2D(NBR_FEMMES, NBR_HOMMES);
	initPreferences(prefH, prefF);

	uint8_t *mariages = allouerMemoire1D(nbrMariages);
	initMariages(mariages, nbrMariages);

	// Attribution des mariages
	attribuerMariages(prefH, prefF, mariages, nbrMariages);

	// Affichage
	afficherMariages(mariages, nbrMariages);

	// Libération de la mémoire
	libererMemoire1D(mariages, nbrMariages);
	libererMemoire2D(prefF, NBR_FEMMES, NBR_HOMMES);
	libererMemoire2D(prefH, NBR_HOMMES, NBR_FEMMES);

	// Fin
	exit(0);
}
// LIBRAIRIES
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

// FONCTIONS
int8_t *allouerMemoire1D(int8_t n)
{
	int8_t *matrice = malloc(n * sizeof(int8_t));

	return matrice;
}

int8_t **allouerMemoire2D(int8_t n, int8_t m)
{
	int8_t **matrice = malloc(n * sizeof(int8_t *));

	for(int8_t i = 0; i < n; i++)
	{
		matrice[i] = malloc(m * sizeof(int8_t));
	}

	return matrice;
}

void libererMemoire1D(int8_t *matrice, int8_t n)
{
	free(matrice);
}

void libererMemoire2D(int8_t **matrice, int8_t n, int8_t m)
{
	for(int8_t i = 0; i < m; i ++)
	{
		free(matrice[i]);
	}

	free(matrice);
}

void initPreferences(int8_t **prefH, int8_t **prefF)
{
	// Préférences Hommes
	prefH[0][0] = 0;
	prefH[0][1] = 1;
	prefH[0][2] = 2;
	prefH[0][3] = 3;

	prefH[1][0] = 0;
	prefH[1][1] = 1;
	prefH[1][2] = 2;
	prefH[1][3] = 3;

	prefH[2][0] = 2;
	prefH[2][1] = 0;
	prefH[2][2] = 1;
	prefH[2][3] = 3;

	prefH[3][0] = 1;
	prefH[3][1] = 2;
	prefH[3][2] = 0;
	prefH[3][3] = 3;

	// Préférences Femmes
	prefF[0][0] = 2;
	prefF[0][1] = 3;
	prefF[0][2] = 0;
	prefF[0][3] = 1;

	prefF[1][0] = 1;
	prefF[1][1] = 2;
	prefF[1][2] = 3;
	prefF[1][3] = 0;

	prefF[2][0] = 0;
	prefF[2][1] = 1;
	prefF[2][2] = 2;
	prefF[2][3] = 3;

	prefF[3][0] = 2;
	prefF[3][1] = 3;
	prefF[3][2] = 1;
	prefF[3][3] = 0;
}

void initMariages(int8_t *mariages, int8_t nbrHommes, int8_t nbrFemmes)
{
	for(int8_t i = 0; i < nbrFemmes; i++)
	{
		mariages[i] = nbrHommes;
	}
}

int8_t hommePrefere(int8_t hommeActuel, int8_t hommeConcurrent, int8_t nbrHommes, int8_t indiceFemme, int8_t **prefF)
{
	for(int8_t i = 0; i < nbrHommes; i++)
	{
		if((prefF[indiceFemme][i] == hommeActuel) || (prefF[indiceFemme][i] == hommeConcurrent))
		{
			return prefF[indiceFemme][i];
		}
	}

	return nbrHommes;
}

bool ontTousPartenaire(int8_t *mariages, int8_t nbrHommes, int8_t nbrFemmes)
{
	for(int8_t i = 0; i < nbrFemmes; i++)
	{
		if(mariages[i] == nbrHommes)
		{
			return 0;
		}
	}

	return 1;
}

bool hommeSeul(int8_t *mariages, int8_t homme, int8_t nbrFemmes)
{
	for(int8_t i = 0; i < nbrFemmes; i++)
	{
		if(mariages[i] == homme)
		{
			return 0;
		}
	}

	return 1;
}

void attribuerMariages(int8_t **prefH, int8_t **prefF, int8_t *mariages, int8_t nbrHommes, int8_t nbrFemmes)
{
	// Les hommes se proposent à leur femme préférée qui ne retient que celui qu'elle préfère
	for(int8_t i = 0; i < nbrHommes; i++)
	{
		mariages[prefH[i][0]] = hommePrefere(mariages[prefH[i][0]], i, nbrHommes, prefH[i][0], prefF);
	}

	// Tant que tous les individus du groupe de taille minimum n'ont pas trouvé de partenaire
	while(!ontTousPartenaire(mariages, nbrHommes, nbrFemmes))
	{
		// Les hommes seuls se proposent à leur choix suivant qui les retient ou non
		// Si retenu, l'homme dont on a pris la place doit se proposer à son tour
		for(int8_t i = 0; i < nbrHommes; i++)
		{
			if(hommeSeul(mariages, i, nbrFemmes))
			{
				for(int8_t j = 0; j < nbrFemmes; j++)
				{
					if(hommePrefere(mariages[prefH[i][j]], i, nbrHommes, prefH[i][j], prefF) == i)
					{
						mariages[prefH[i][j]] = hommePrefere(mariages[prefH[i][j]], i, nbrHommes, prefH[i][j], prefF);
						break;
					}
				}
			}
		}
	}
}

void afficherMariages(int8_t *mariages, int8_t nbrFemmes)
{
	for(int8_t i = 0; i < nbrFemmes; i++)
	{
		printf("Mariage n°%d : Femme%d + Homme%d\n", i + 1, i + 1, mariages[i] + 1);
	}
}

// MAIN
int main()
{
	// Initialisation des variables
	int8_t nbrHommes = 4; // Groupe de taille maximum
	int8_t nbrFemmes = 4; // Groupe de taille minimum (correspond au nombre de mariages)

	int8_t **prefH = allouerMemoire2D(nbrHommes, nbrFemmes);
	int8_t **prefF = allouerMemoire2D(nbrFemmes, nbrHommes);
	initPreferences(prefH, prefF);

	int8_t *mariages = allouerMemoire1D(nbrFemmes);
	initMariages(mariages, nbrHommes, nbrFemmes);

	// Attribution des mariages
	attribuerMariages(prefH, prefF, mariages, nbrHommes, nbrFemmes);

	// Affichage
	afficherMariages(mariages, nbrFemmes);

	// Libération de la mémoire
	libererMemoire1D(mariages, nbrFemmes);
	libererMemoire2D(prefF, nbrFemmes, nbrHommes);
	libererMemoire2D(prefH, nbrHommes, nbrFemmes);

	// Fin
	exit(0);
}
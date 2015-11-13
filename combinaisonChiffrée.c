/****************************************************************/
/* Auteur : LECLER Quentin									    */
/* Groupe : 2102												*/
/* Application : combinaisonChiffr�e.c							*/
/* Description : r�alise le jeu de la combinaison chiffr�e		*/
/* Date de derni�re mise � jour : 29/11/09						*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_NBR 0
#define MAX_NBR 9
#define MIN_COMB 1
#define MAX_COMB 20

int genererNombre(int min, int max);
void genererTableau(int tableau[], int tailleTableau, int min, int max);
void initialiserTableau(int tableau[], int tailleTableau, int valeurParDefaut);
void afficherTableau(int tableau[], int tailleTableau);

int main(int argc, char *argv[])
{
	int combinaison[40];
	int tailleCombinaison;
	int chiffrePropose;
	int chiffreTrouve[40];
	int coupsTotal;
	int coupsRestants;
	int compteur;
	int i;
	char recommencer;

	recommencer = 'o';
	srand(time(NULL));

	printf("Bienvenue dans le jeu de la combinaison chiffre !\n");
	printf("_________________________________________________\n");

	do
	{
		/****************************************************/
		/* mise � z�ro du compteur � chaque nouvelle partie */
		/****************************************************/

		compteur = 0;

		/*******************************************************/
		/* g�n�ration al�atoire de la taille de la combinaison */
		/*******************************************************/

		tailleCombinaison = genererNombre(MIN_COMB, MAX_COMB);

		/*************************************************************/
		/* le tableau "chiffreTrouve" contiendra les chiffres		 */
		/* la combinaison que l'utilisateur aura trouv�				 */
		/* par d�faut on initalise toute les valeurs du tableau		 */
		/* � 42 (sa correspondance ascii correspond au caract�re '*' */
		/*************************************************************/

		initialiserTableau(&chiffreTrouve[0], tailleCombinaison, 42);

		/*****************************************************/
		/* l'utilisateur aura droit � 3 fois la taille de la */
		/* combinaison pour la trouver						 */
		/*****************************************************/

		coupsTotal = 3 * tailleCombinaison;
		coupsRestants = 3 * tailleCombinaison;

		/******************************************/
		/* g�n�ration al�atoire de la combinaison */
		/******************************************/

		genererTableau(&combinaison[0], tailleCombinaison, MIN_NBR, MAX_NBR);

		/************************************************************/
		/* on boucle tant qu'il nous reste des coups � jouer		*/
		/* et que la combinaison n'a pas �t� parcourue compl�tement */
		/************************************************************/

		while((coupsRestants > 0) && (compteur < tailleCombinaison))
		{
			do
			{
				printf("\nVeuillez entrer un chiffre compris entre %d ~ %d : ", \
					MIN_NBR, MAX_NBR);
				scanf_s("%d", &chiffrePropose);
			} while(chiffrePropose < MIN_NBR || chiffrePropose > MAX_NBR);

			/*****************************************************/
			/* si le chiffre propos� est celui de la combinaison */
			/* on l'affiche et on passe au chiffre suivant		 */
			/*****************************************************/

			if(chiffrePropose == combinaison[compteur])
			{
				chiffreTrouve[compteur] = chiffrePropose;
				printf("\n");
				for(i = 0; i < tailleCombinaison; i++)
				{
					if(chiffreTrouve[i] == 42)
					{
						/***************************************************/
						/* affiche la correspondance de 42 en ascii => '*' */
						/***************************************************/
						printf("%c ", chiffreTrouve[i]);
					}
					else
					{
						printf("%d ", chiffreTrouve[i]);
					}
				}
				compteur = compteur + 1;
			}

			/*************************************************************/
			/* sinon on donne une indication de grandeur � l'utilisateur */
			/* et on lui retire un coups								 */
			/*************************************************************/

			else
			{
				coupsRestants = coupsRestants - 1;

				if(chiffrePropose < combinaison[compteur])
				{
					printf("\nLe chiffre recherche est plus grand.");
					printf("\nIl vous reste %d essais.\n", coupsRestants);
				}
				else
				{
					printf("\nLe chiffre recherche est plus petit.");
					printf("\nIl vous reste %d essais.\n", coupsRestants);
				}
			}
		}

		/**********************************************************/
		/* si il ne nous reste plus de coups � jouer on a perdu ! */
		/**********************************************************/

		if(coupsRestants == 0)
		{
			printf("\nVous avez PERDU !");
			printf("\nLa combinaison etait : ");
			afficherTableau(&combinaison[0], tailleCombinaison);
		}

		/**********************/
		/* sinon on a gagn� ! */
		/**********************/

		else
		{
			printf("\n\nVous avez GAGNE !");
			printf("\nVous avez utilise %d coups sur %d", \
				coupsTotal-coupsRestants, coupsTotal);
		}

		do
		{
			printf("\n\nVoulez-vous recommencer (o, n) ? ");
			fflush(stdin); /* clear du buffer d'entr�e */
			recommencer = getchar();
		} while(recommencer != 'o' && recommencer != 'n');
	} while(recommencer != 'n');

	system("pause");
	return 0;
}

/****************************************************************/
/* INPUT : nombre minimum � g�n�rer (min)						*/
/*		   nombre maximum � g�n�rer (max)						*/
/* PROCESS : g�n�ration al�atoire d'un nombre compris entre		*/
/*			 min et max											*/
/* OUTPUT : nombre al�atoire compris entre min et max			*/
/****************************************************************/

int genererNombre(int min, int max)
{
	int nombreAleatoire;

	nombreAleatoire = (rand() % (max - min + 1)) + min;

	return nombreAleatoire;
}

/****************************************************************/
/* INPUT : pointeur sur le tableau � g�n�rer					*/
/*		   taille du tableau � g�n�rer							*/
/*	       nombre minimum � g�n�rer (min)						*/
/*		   nombre maximum � g�n�rer (max)						*/
/* PROCESS : g�n�ration al�atoire d'un tableau de nombres		*/
/*			 compris entre min et max							*/
/* OUTPUT : /													*/
/****************************************************************/

void genererTableau(int tableau[], int tailleTableau, int min, int max)
{
	int compteur;

	for(compteur = 0; compteur < tailleTableau; compteur++, tableau++)
	{
		*tableau = genererNombre(min, max);
	}
}

/****************************************************************/
/* INPUT : pointeur sur le tableau � initialiser	     		*/
/*		   taille du tableau � initialiser						*/
/*		   valeur � laquelle le tableau doit �tre initialise	*/
/* PROCESS : initialise le tableau � une certaine valeur		*/
/* OUTPUT : /													*/
/****************************************************************/

void initialiserTableau(int tableau[], int tailleTableau, int valeurParDefaut)
{
	int compteur;

	for(compteur = 0; compteur < tailleTableau; compteur++, tableau++)
	{
		*tableau = valeurParDefaut;
	}
}

/****************************************************************/
/* INPUT : pointeur sur le tableau � afficher		     		*/
/*		   taille du tableau � afficher							*/
/* PROCESS : affiche le contenu du tableau						*/
/* OUTPUT : /													*/
/****************************************************************/

void afficherTableau(int tableau[], int tailleTableau)
{
	int compteur;

	for(compteur = 0; compteur < tailleTableau; compteur++, tableau++)
	{
		printf("%d ", *tableau);
	}
}
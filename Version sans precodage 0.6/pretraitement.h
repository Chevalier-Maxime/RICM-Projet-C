#include <stdio.h>
#include <stdlib.h>

#ifndef PRETRAITEMENT_H
#define PRETRAITEMENT_H

void pretraiter( FILE* fichier, FILE* fichierPretraite);

void ecriture(int i, FILE* fichierPretraite, int courant);

int testerreurCaractere(int courant);

int testfinCaractere(int courant);

int sontIdentique(int courant, int suivant);

#endif

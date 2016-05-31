#include <stdio.h>
#include <stdlib.h>

#ifndef DEPRETRAITAGE_H
#define DEPRETRAITAGE_H

void depretraiter( FILE* fichier, FILE* fichierPretraite);

int testerreurCaractere(int courant);

int testfinCaractere(int courant);

int sontIdentique(int courant, int suivant);


#endif

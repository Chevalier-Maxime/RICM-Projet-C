#include <stdio.h>
#include <stdlib.h>
#include "entete.h"
#include "sdata.h"

int main(int argc, char **argv)
{

FILE* fichier = fopen("test.txt","w");

int tabI[4];
tabI[0]=2;
tabI[1]=5;
tabI[2]=7;
tabI[3]=10;

char tabS[4];
tabS[0]='A';
tabS[1]='g';
tabS[2]='7';
tabS[3]='m';


entete * ent =creerEntete(4, tabI,tabS);

ecrireentete(ent,fichier );

fclose(fichier);

return 0;
}

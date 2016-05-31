#include <stdio.h>
#include <stdlib.h>
#include "desentetage.h"
#include "sdata.h"

int main(int argc, char **argv)
{

FILE* fichier = fopen("test.txt","r");
entete * ent = decrypterentete(fichier);

int n,a;
char c;
n = ent->nbSymboles;
printf("%d\n",n);
c=ent->Symbole[0];
printf("%c\n",c);
c= ent->Symbole[n-1];
printf("%c\n",c);
a= ent->TailleS[0];
printf("%d\n",a);
a= ent->TailleS[n-1];
printf("%d\n",a);

fclose(fichier);

return 0;
}

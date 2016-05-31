#include <stdio.h>
#include <stdlib.h>
#include "entete.h"
#include "sdata.h"

void ecrireentete(entete * ent,FILE* fichieraenteter )
{
	int n,i,k,id = 1815;
	char c;
	n=ent->nbSymboles;
	fprintf(fichieraenteter,"%d",id);
	fprintf(fichieraenteter,"%d",n);
	unsigned char * symbole = ent->Symbole;
	int* profondeur = ent->TailleS;
	i=0;
	while(i!=n)
	{
		c = symbole[i];
		fprintf(fichieraenteter,"%c",c);
		k=profondeur[i];
		fprintf(fichieraenteter,"%d",k);
		fprintf(fichieraenteter,"%c",'S');
		fprintf(fichieraenteter,"%c",'S');
		i++;
	}
	return;
}
	

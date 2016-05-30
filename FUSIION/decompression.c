#include <stdio.h>
#include <stdlib.h>
#include "sdata.h"
#include "compression.h"
#include "decompression.h"

ArbreSymbole* Decompression(unsigned char TS[256], int TT[256], int nbSymboles){
	TabArb Arb;
	int i, j, Prof;

	for (j = 0; j<nbSymboles; j++) {
		Arb.a[j] = creerArbreSymboleVide(TS[j], TT[j]);
	}
	Arb.Taille = nbSymboles;
	
	Prof = TT[0];
	while (Arb.Taille>2) {

		Arb.a[0] = ajout2ArbresS(Arb.a[0], Arb.a[1]);
		for (j = 1; j<Arb.Taille; j++)
			Arb.a[j] = Arb.a[j+1];
		Arb.Taille--;

		i = 1;
		while (i<Arb.Taille-1 && 2*Prof == Arb.a[i]->occurrence + Arb.a[i+1]->occurrence) {
			Arb.a[i] = ajout2ArbresS(Arb.a[i], Arb.a[i+1]);
			i++;
			for (j = i; j<Arb.Taille; j++){
				Arb.a[j] = Arb.a[j+1];
				if(Arb.a[j]->occurrence>Prof)
					Arb.a[j]->occurrence=Prof;
			}
			Arb.Taille--;
		}
		Prof--;
	}
	if(Arb.Taille>=0){
		Arb.a[0] = ajout2ArbresS(Arb.a[0], Arb.a[1]);
		print_Abr(Arb.a[0], 0);
		return Arb.a[0];
	}
	exit(0);
}


#include <stdio.h>
#include <stdlib.h>
#include "depretraitage.h"

int main(int argc, char **argv)
{

FILE* fichierbase = fopen("pre.txt","r");
FILE* fichierPre = fopen("res.txt","w");

depretraiter(fichierbase, fichierPre);

fclose(fichierbase);
fclose(fichierPre);
return 0;
}

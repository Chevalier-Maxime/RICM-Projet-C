#include <stdio.h>
#include <stdlib.h>
#include "pretraitement.h"

int main(int argc, char **argv)
{

FILE* fichierbase = fopen("test.txt","r");
FILE* fichierPre = fopen("pre.txt","w");

pretraiter(fichierbase, fichierPre);

fclose(fichierbase);
fclose(fichierPre);
return 0;
}

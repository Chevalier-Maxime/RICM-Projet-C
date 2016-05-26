
define taille_nom_fichier 256

void lireFichier(donnees * d)
{
    FILE* fichier = NULL;

	//Demander chemin d'acces
	 printf("Quel est votre nom de fichier?  ");
		scanf("%s",nomFichier);
	//tester si il est valide
	//si non, redemander
	
    fichier = fopen("sdata.h", "r+");

    if (fichier != NULL)
    {
       // lire et écrire dans le fichier
        
        
        
        fclose(fichier); 
    }
    else
    {
        
        printf("Impossible d'ouvrir le fichier ");
    }
}




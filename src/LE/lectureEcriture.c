void lireFichier(donnees * d)
{
    FILE* fichier = NULL;

    fichier = fopen("sdata.h", "r+");

    if (fichier != NULL)
    {
       // lire et �crire dans le fichier
        
        
        
        fclose(fichier); 
    }
    else
    {
        
        printf("Impossible d'ouvrir le fichier ");
    }
}

#include "../Headers/include.h"

void menu(void)
{
printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
printf("|S|T|E|G|A|N|O|G|R|A|P|H|I|E|\n");
printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");

printf("1. Coder un texte dans une image\n");
printf("2. Decoder une image\n");
printf("3. Quitter le programme\n");

printf("Tapez le chiffre correspondant a ce que vous voulez faire: ");
}

void clean(const char *buffer, FILE *fp)//https://openclassrooms.com/courses/utiliser-les-bonnes-fonctions-d-entree
{
    char *p = strchr(buffer,'\n');
    if (p != NULL)
        *p = 0;
    else
    {
        int c;
        while ((c = fgetc(fp)) != '\n' && c != EOF);
    }
}

void saisie_chaine_dynamique(char** tab)
{
    char chaine[100];
    int i,j=0;
    
    scanf(" %s",chaine);
    
    
    while(chaine[j]!='\0')
    {
        j++;
    }
  
    (*tab)=(char*)malloc((j+1)*sizeof(char));
    
    for(i=0;i<(j+1);i++)
    {
        (*tab)[i]=chaine[i];    
    }
    
}










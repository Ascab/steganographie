#include "../Headers/include.h"

int main()
{
    int choix; 
    menu();
   
    do
    {
        scanf(" %d",&choix);
    }while((choix < 1)&&(choix > 3));
    
    
    switch (choix)
    {
    case 1:  //Codage
        choix_codage();
        break;
    
    case 2: //Decodage
        choix_decodage();
        break;
    
    case 3:
        printf("Au revoir ! \n");
        break;
    }
    
    return 0;
}
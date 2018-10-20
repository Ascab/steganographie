#include "../Headers/include.h"

void codage_message_lineaire(char* bin,int* tab_pixel, int taille_chaine)
{
    int i;
    for(i=0 ; i<=8*taille_chaine ; i++) 
    {
        if( bin[i]==0 && tab_pixel[i]%2 ==1)
        {
            (tab_pixel[i])--;
        }
        
        if(bin[i]==1 && tab_pixel[i]%2 ==0)
        {
            (tab_pixel[i])++;
        }
    }
}

void decodage_message_lineraire(int* tab_pixel, char** chaine)
{
    int i=0, k, val_test_fin,retour=0;
    char *bin;
    bin=(char*)malloc(sizeof(char)*8);
    char bin_test_fin[8];
    
    do
    {
        if ( tab_pixel[i]%2==0)
        {
            bin[i]=0;
        }
        else
        {
            bin[i]=1;
        }
        
        
        if(i%8==0 && i!=0)
        {
            for (k=0;k<8;k++)
            {
                bin_test_fin[k]=bin[i-8+k];
            }
            val_test_fin=ft_btoi(bin_test_fin,8);
        }
        if (val_test_fin=='\0')
        {
            retour=1;
        }
        else
        {
            bin=(char*)realloc(bin,sizeof(bin)+i*sizeof(char));
            i++;
        }
        
    }while(retour!=1);
    *chaine=(char*)malloc(i/8*sizeof(char));
    traduction_message(bin,i,*chaine);
}

void traduction_message(char* bin, int taille_tab_bin,char *chaine)
{
    int i,k;
    char carac,bin_btoc[8];
    for(i=0;i<taille_tab_bin;i+=8)
    {
        for (k=0;k<8;k++)
            {
                bin_btoc[k]=bin[i+k];
            }
        carac=ft_btoc(bin_btoc,8);
        chaine[i/8]=carac;
        
    }
}
void transcription_message(FILE *original, FILE *crypted, T_BMP info_image)
{
    int i;
    char* tmp;
    
    tmp = (char*)malloc(info_image.header.offset * sizeof(char));
    
    fseek(original, 0, SEEK_SET);
    fseek(crypted, 0, SEEK_SET);
    
    fread(tmp, 1, 53, original);
    fwrite(tmp, sizeof(unsigned char), 54, crypted);
    for(i = 0 ; i < info_image.header.taille_image ; i++)
    {
        fseek(crypted, info_image.header.offset + i , SEEK_SET);
        fwrite(&(info_image.image[i]), sizeof(unsigned char), 1, crypted);
    }
}

void codage_message_aleatoire(char* bin,int* tab_pixel, int taille_chaine,int cle, unsigned int taille_image)
{
    int i,k,j=0,*ordre,stock;
    ordre=(int*)malloc(sizeof(int)*taille_image);
    srand(cle);
    for(k=0;k<taille_image;k++)
    {
        ordre[k]=k;
    }
    for(k=0;k<taille_image;k++)
    {
        i=rand()%(taille_image);
        stock=ordre[k];
        ordre[k]=ordre[i];
        ordre[i]=stock;
    }
    
    for (k=0;k<8*taille_chaine;k++)
    {   
        
            if( bin[j]==0 && tab_pixel[ordre[k]]%2==1)
            {
                tab_pixel[ordre[k]]--;
            }
            
            
            if(bin[j]==1 && tab_pixel[ordre[k]]%2==0)
            {
                tab_pixel[ordre[k]]++;
            }
            j++;
        
    }
}

void decodage_message_aleatoire(int* tab_pixel, char** chaine,int cle,unsigned int taille_image)
{
    int i,j=0,k,val_test_fin=1,retour=0,*ordre,stock;
    char *bin;
    char bin_test_fin[8];
    
    srand(cle);
    ordre=(int*)malloc(sizeof(int)*taille_image);
    bin=(char*)malloc(sizeof(char)*8);
    for(k=0;k<taille_image;k++)
    {
        ordre[k]=k;
    }
    
    for(k=0;k<taille_image;k++)
    {
        i=rand()%(taille_image);
        stock=ordre[k];
        ordre[k]=ordre[i];
        ordre[i]=stock;
    }
    
    do
    {
    
    
            if ( ( tab_pixel[ordre[j]])%2==0 )
            {
                bin[j]=0;
            }
            else 
            {
                bin[j]=1;
            }
       
            
            if((j%8)==0 && j!=0)
            {   
                for(k=0;k<8;k++)
                {
                    
                    bin_test_fin[k]=bin[j-8+k]; 
                }
                val_test_fin=ft_btoi(bin_test_fin,8);
            }
           
            if (val_test_fin!='\0')
            {
                bin = (char*)realloc(bin,sizeof(bin)+j*sizeof(char));
                j++;
            }
            else
            {
                retour=1;
            }
        
    }while(retour==0);
     *chaine=(char*)malloc(j/8*sizeof(char));
    traduction_message(bin,j,*chaine);
}

void choix_codage ()
{
    int choix,cle=0;
    
    printf("Choisissez votre méthode de dissimulation\n");
    printf("1. Lineaire\n");
    printf("2. Aleatoire\n");
    //printf("3. Croisé\n");
    printf("Entrez votre choix: ");
    do 
    {
        scanf(" %d",&choix);
    }while(choix<1 || choix > 2); // a modifier pour remettre codage croisee
    
    switch (choix)
    {
        case 1: 
        codage(choix, cle);
        break;
        case 2: 
        printf("Tapez un nombre correpondant à la clé de codage ( Elle vous servira pour décoder l'image)\n");
        scanf(" %d",&cle);
        codage(choix, cle);
        break;
  /*     case 3:
        codage(choix,cle);
        break;*/
    }

}


void choix_decodage()
{

    int choix;
    int cle=0;
    
    printf("Choisissez votre méthode de decodage \n");
    printf("1. Lineaire\n");
    printf("2. Aleatoire\n");
    //printf("3. Croisé\n");
    printf("Entrez votre choix: ");
    do
    {
        scanf(" %d",&choix);
    }while(choix<1 || choix > 2); // a modifier pour remettre dissimulation croisée
    
    switch(choix)
    {
        case 1: //lineaire
        decodage(choix, cle);
        break;
      
        case 2: //Aleatoire 
        printf("Entrez la cle de decodage :\n");
        scanf(" %d",&cle);
        decodage(choix,cle);
        break;
       /* 
        case 3:
        decodage(choix,cle);
        break;*/
    }
}

void decodage (int choix, int cle )
{
       
    int taille_chaine; 
    char *bin, chaine[100], *chaine_decryptee;
    FILE *pic, *crypted_pic ;
    T_BMP image, image_cryptee;
    

    pic=NULL;
    crypted_pic=NULL;
    bin=NULL;
    chaine_decryptee=NULL;
    do
        {
            printf("Saisissez le chemin de l'image a decoder :");
            saisie_chaine_dynamique(&(image_cryptee.path));
            crypted_pic = fopen(image_cryptee.path, "rb"); 
            if(crypted_pic != NULL)
            {
                if(verif_bmp(&(image_cryptee.header), crypted_pic) == 1)
                {
                    ft_get_bmp_info(&(image_cryptee.header), crypted_pic);
                    ft_get_pixels(&image_cryptee, crypted_pic);
                    if (choix==1)
                    {
                        decodage_message_lineraire(image_cryptee.image,&chaine_decryptee);
                    }
                    else // if (choix==2)
                    {
                        decodage_message_aleatoire(image_cryptee.image,&chaine_decryptee,cle,image_cryptee.header.taille_image);
                    }
                    /*
                    else
                    {
                        printf("-1\n");
                        decodage_message_croise(&chaine_decryptee,image_cryptee.image,image_cryptee.header.taille_image);
                    }*/
                    
                    printf("Le message est: %s\n",chaine_decryptee);
                    
                }
                else
                printf("Votre image n'est pas du type bmp, veuillez recommencer\n");
            }
            else
                printf("Votre image n'existe pas, veuillez recommencer\n");
            
        }while(crypted_pic == NULL || verif_bmp(&(image_cryptee.header),crypted_pic)!=1);
        free(chaine_decryptee);
        fclose(crypted_pic);
}

void codage( int choix , int cle)
{
    int taille_chaine=0; 
    char *bin, chaine[100], *chaine_decryptee;
    FILE *pic, *crypted_pic ;
    T_BMP image, image_modifiee;
    

    pic=NULL;
    crypted_pic=NULL;
    bin=NULL;
    chaine_decryptee=NULL;
    
    do
    {
        printf("Saisissez le chemin de l'image dans laquelle coder :");
        saisie_chaine_dynamique(&(image.path));
        clean(image.path, stdin);
        pic = fopen(image.path, "rb"); //
      
    
        if(pic != NULL)
        {
            printf("Saisissez le chemin de l'image modifiee : ");
            saisie_chaine_dynamique(&(image_modifiee.path));
            clean(image_modifiee.path, stdin);
            crypted_pic = fopen(image_modifiee.path, "wb+");
            if(verif_bmp(&(image.header),pic))
            {
                ft_get_bmp_info(&(image.header), pic);
                ft_get_pixels(&image,pic);
                printf("Tapez un texte: ");
                
                do 
                {   
                    if(taille_chaine!=0) printf("Texte trop long, veuillez recommencer\n");
                    taille_chaine = 0;
                    fgets(chaine, sizeof(chaine), stdin);
                    clean(chaine, stdin);
                    
                    while(chaine[taille_chaine] != '\0')
                    {
                        taille_chaine++;
                    }
                    taille_chaine++;
                }while(8*taille_chaine>image.header.taille_image);
                
                printf("Vous allez dissumuler : %s\n",chaine); 
                bin=(char*)malloc(8*taille_chaine*sizeof(char));
                ft_stob(bin,chaine,taille_chaine);
                if (choix == 1)
                {
                    codage_message_lineaire(bin,image.image,taille_chaine);
                }
                else// if (choix == 2)
                {
                    codage_message_aleatoire(bin,image.image,taille_chaine,cle,image.header.taille_image);
                }
                /*
                else 
                {
                    codage_message_croise(bin,image.image,taille_chaine,image.header.taille_image);
                }*/
                transcription_message(pic, crypted_pic, image);
                free(bin);
            }
            else
            printf("Votre image n'est pas du type bmp, veuillez recommencer\n");
        }
        else
            printf("Votre image n'existe pas, veuillez recommencer\n");
            
    }while(((pic == NULL) || verif_bmp(&(image.header),pic)!=1) );
    fclose(pic);
    fclose(crypted_pic);
}


/*void codage_message_croise(char* bin,int* tab_pixel, int taille_chaine, unsigned int taille_image)
{
    int i;
    for(i=0 ; i<=8*taille_chaine ; i++) 
    {
        if ( i%2==0 )
        {
            if( bin[i]==0 && tab_pixel[i]%2 ==1)
            {
                (tab_pixel[i])--;
            }
            
            if(bin[i]==1 && tab_pixel[i]%2 ==0)
            {
                (tab_pixel[i])++;
            }
        }
        else
        {
            if( bin[i+1]==0 && tab_pixel[taille_image-i]%2 ==1)
            {
                (tab_pixel[i])--;
            }
            
            if(bin[i+1]==1 && tab_pixel[taille_image]%2 ==0)
            {
                (tab_pixel[i])++;
            }
        }  
        
    }   
}*/

/* void decodage_message_croise(char** chaine,int* tab_pixel, unsigned int taille_image)
{
    int i=0,k,val_test_fin,retour=0;
    char bin[1000];
    char bin_test_fin[8];
    printf("1\n");
    do
    {
        printf("%d\n", i);
        if(i%2==0)
        {
            if ( tab_pixel[i]%2==0)
            {
                bin[i]=0;
            }
            else
            {
                bin[i]=1;
            }
        }
        
        else
        {
            if ( tab_pixel[taille_image-i]%2==0)
            {
                bin[i]=0;
            }
            else
            {
                bin[i]=1;
            }
        }
        
        
        if(i%8==0 && i!=0)
        {
            for (k=0;k<8;k++)
            {
                bin_test_fin[k]=bin[i-8+k];
            }
            val_test_fin=ft_btoi(bin_test_fin,8);
        }
        if (val_test_fin=='\0')
        {
            retour=1;
        }
        else
        {
            i++;
        }
        
    }while(retour!=1);
    printf("2\n");
    *chaine=(char*)malloc(i/8*sizeof(char));
    printf("3\n");
    traduction_message(bin,i,*chaine);
    printf("4\n");
}

    */
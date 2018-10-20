#include "../Headers/include.h"

char ft_btoc(char *bin, int nb_bytes) 
{
  return (char)ft_btoi(bin, nb_bytes);
}

int ft_btoi(char *bin, int nb_bytes)
{
    int nb, power, i;
    
    nb=0;
    power = 1;
    
    for(i = nb_bytes-1 ; i >= 0 ; i--)
    {
        nb += bin[i] * power;
        power *= 2;
    }
    return nb;
}

void ft_get_bmp_info(T_BMP_Header *picture,  FILE *pic) //pic dois être ouvert en lecture binaire
{   
    fseek(pic, 10 , SEEK_SET);
    fread(&(picture->offset) , 4 * sizeof(unsigned char) , 1 , pic);
    fseek(pic, 34 , SEEK_SET);
    fread(&(picture->taille_image), 4 * sizeof(unsigned char), 1, pic);
}

void ft_get_pixels(T_BMP *picture, FILE *pic)
{
    int i;
    
    picture->image = (int*)malloc(picture->header.taille_image * sizeof(int));
    
    for(i=0 ; i<=(picture->header.taille_image) ; i++)
    {
        
            fseek(pic , i+(picture->header.offset) , SEEK_SET);
            fread(&(picture->image[i]) , sizeof(char) , 1 , pic);
    }
}



void ft_stob(char* bin, char* chaine, int taille_chaine)
{
    int i,j;
   
    for(i=0;i<taille_chaine;i++)
    {
        for(j = 0 ; j < 7 ; j++)
        {
            bin[8*(i+1)-1-j] = (chaine[i] >> j) & 1;
        }
    }
}

int verif_bmp(T_BMP_Header* header, FILE* pic)
{
    fseek(pic, 0, SEEK_SET);
    fread(&(header->type1) , sizeof(char) , 1 , pic);
    fseek(pic, 1, SEEK_SET);
    fread(&(header->type2) , sizeof(char) , 1 , pic);
    if ( (header->type1) == 'B' && (header->type2) == 'M' )
    {
        return 1;
    }
    else return 0;
}

#ifndef STRUCT_H
#define STRUCT_H

typedef struct
{
    char type1;
    char type2;
    unsigned int offset;
    unsigned int taille_image;
}T_BMP_Header;



typedef struct
{
    T_BMP_Header header;
    int *image;
    char *path; //Chemin de l'image
}T_BMP;

#endif

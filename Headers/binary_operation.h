#include "struct.h" 
#include <stdio.h>

#ifndef BINARY_OPERATION_H
#define BINARY_OPERATION_H

int ft_btoi(char *bin, int nb_bytes);
char ft_btoc(char *bin, int nb_bytes);
void ft_get_bmp_info(T_BMP_Header *picture,  FILE *pic);
void ft_get_pixels(T_BMP *picture, FILE *pic);
void ft_stob(char* bin, char* chaine, int taille_chaine);
int verif_bmp(T_BMP_Header* header, FILE* pic);

#endif

#ifndef CRYPYAGE_H
#define CRYPYAGE_H

void codage_message_lineaire(char* bin, int* tab_pixel, int taille_chaine);

void decodage_message_lineaire(int* tab_pixel, char** chaine);

void codage_message_aleatoire(char* bin,int* tab_pixel, int taille_chaine,int cle, unsigned int taille_image);

void decodage_message_aleatoire(int* tab_pixel, char** chaine,int cle, unsigned int taille_image);

void traduction_message(char* bin, int taille_tab_bin,char *chaine);

void transcription_message(FILE *original, FILE *crypted, T_BMP info_image);

void choix_codage ();

void choix_decodage();

void codage( int choix , int cle);

void decodage( int choix , int cle);



#endif
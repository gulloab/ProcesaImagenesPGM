#ifndef IMAGEN_H 
#define IMAGEN_H 

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ancho;
    int alto;
    int valor_max;
    int **pixeles;
} Imagen;

Imagen* cargarImagenPGM(char *ruta);
int guardarImagenPGM(Imagen *img, char *ruta);
void liberarImagen(Imagen *img);
void invertirColores(Imagen *img);
void rotarImagen90Grados(Imagen *img);
void aplicarFiltroCaja(Imagen *img);

#endif
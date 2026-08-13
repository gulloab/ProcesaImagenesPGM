#include "imagen.h"
#include <string.h>

Imagen* cargarImagenPGM(char *ruta) {
    // abrir archivo en modo lectura
    FILE *archivo = fopen(ruta, "r");
    if (archivo == NULL) 
    return NULL;

    // leer y validar el "magic number" del formato pgm
    char formato[3];
    fscanf(archivo, "%2s", formato);
    if (strcmp(formato, "P2") != 0) {
        fclose(archivo);
        return NULL;
    }


    int c;
    while ((c = fgetc(archivo)) != EOF) { //el fgetc extrae el caracter siguiente 
        // si encontramos un numeral
        if (c == '#') { 
            // bucle vacio para tragar los caracteres hasta el salto de linea
            while ((c = fgetc(archivo)) != '\n' && c != EOF);
        } else if (c != ' ' && c != '\n' && c != '\r' && c != '\t') {
            
            ungetc(c, archivo); //ungetc devuelve dicho caracter para que pueda ser leído nuevamente por fscanf
            break;
        }
    }
    
    
   
    Imagen img = (Imagen)malloc(sizeof(Imagen));
    
    // lee las dimensiones y el techo de color
    fscanf(archivo, "%d %d", &img->ancho, &img->alto);
    fscanf(archivo, "%d", &img->valor_max);

    //creacion de arreglo de punteros
    img->pixeles = (int*)malloc(img->alto * sizeof(int));
    for (int i = 0; i < img->alto; i++) {
        // segunda fase: crear bloques contiguos de enteros (las columnas)
        img->pixeles[i] = (int*)malloc(img->ancho * sizeof(int));
    }

    
    // recorremos las filas
    for (int i = 0; i < img->alto; i++) {
        // recorremos las columnas de izquierda a derecha
        for (int j = 0; j < img->ancho; j++) {
            // guardamos el pixel en la celda de memoria dinamica correspondiente
            fscanf(archivo, "%d", &img->pixeles[i][j]);
        }
    }


    fclose(archivo);
    return img;
}

void invertirColores(Imagen *img) {
    // iteramos sobre toda la matriz
    for (int i = 0; i < img->alto; i++) {
        for (int j = 0; j < img->ancho; j++) {
            // sobrescribimos el valor original por su inverso logico
            img->pixeles[i][j] = img->valor_max - img->pixeles[i][j];
        }
    }
}


void rotarImagen90Grados(Imagen *img) {
    // cambiamos las dimensiones (el ancho viejo ahora es el alto nuevo y viceversa)
    int nuevo_ancho = img->alto;
    int nuevo_alto = img->ancho;
    
    // pedimos memoria prestada para armar una matriz en blanco con las nuevas medidas
    int *nuevos_pixeles = (int)malloc(nuevo_alto * sizeof(int));
    for (int i = 0; i < nuevo_alto; i++) {
        nuevos_pixeles[i] = (int*)malloc(nuevo_ancho * sizeof(int));
    }

    // agarramos cada pixel y lo sentamos en su nueva silla
    for (int i = 0; i < img->alto; i++) {
        for (int j = 0; j < img->ancho; j++) {
            // el truco matematico para girar la foto a la derecha sin que quede como espejo
            nuevos_pixeles[j][nuevo_ancho - 1 - i] = img->pixeles[i][j];
        }
    }

    // destruimos la matriz vieja para no dejar basura en la ram
    for (int i = 0; i < img->alto; i++) {
        free(img->pixeles[i]);
    }
    free(img->pixeles);

    //le decimos a nuestra estructura que use la matriz nueva y sus nuevas medidas
    img->pixeles = nuevos_pixeles;
    img->ancho = nuevo_ancho;
    img->alto = nuevo_alto;
}


void aplicarFiltroCaja(Imagen *img) {
    // creamos una matriz temporal para no manchar los datos originales mientras hacemos sumas
    int *temp = (int)malloc(img->alto * sizeof(int));
    for (int i = 0; i < img->alto; i++) {
        temp[i] = (int*)malloc(img->ancho * sizeof(int));
    }

    // paseamos por cada pixel de la foto
    for (int i = 0; i < img->alto; i++) {
        for (int j = 0; j < img->ancho; j++) {
            int suma = 0, cont = 0; 
            
            // revisamos el vecindario del pixel 
            for (int mov_y = -1; mov_y <= 1; mov_y++) {
                for (int mov_x = -1; mov_x <= 1; mov_x++) {
                    int vecino_y = i + mov_y; // coordenada y del vecino
                    int vecino_x = j + mov_x; // coordenada x del vecino
                    
                    // cuidamos de no salirnos del borde para que el programa no explote
                    if (vecino_y >= 0 && vecino_y < img->alto && vecino_x >= 0 && vecino_x < img->ancho) {
                        suma += img->pixeles[vecino_y][vecino_x]; // sumamos la luz de ese vecino
                        cont++;                       // anotamos que contamos a un vecino valido
                    }
                }
            }
            // sacamos el promedio de la zona y lo guardamos seguro en la matriz temporal
            temp[i][j] = suma / cont;
        }
    }
    
    // volcamos la foto ya difuminada de vuelta a la estructura original
    for (int i = 0; i < img->alto; i++) {
        for (int j = 0; j < img->ancho; j++) {
            img->pixeles[i][j] = temp[i][j];
        }
        // aprovechamos el viaje para ir devolviendo la memoria temporal fila por fila
        free(temp[i]);
    }
    //borramos el puntero principal de la temporal y listo
    free(temp);
}


int guardarImagenPGM(Imagen *img, char *ruta) {
    // solicitamos crear o sobrescribir un archivo fisico
    FILE *archivo = fopen(ruta, "w");
    if (!archivo) return 0;


    fprintf(archivo, "P2\n# Generado por la biblioteca\n");
    fprintf(archivo, "%d %d\n%d\n", img->ancho, img->alto, img->valor_max);

    
    for (int i = 0; i < img->alto; i++) {
        for (int j = 0; j < img->ancho; j++) {
            // escribimos el numero convertido a texto y lo separamos con un espacio
            fprintf(archivo, "%d ", img->pixeles[i][j]);
        }
        // obligamos al archivo a bajar de renglon al terminar la fila completa
        fprintf(archivo, "\n");
    }
    
    
    fclose(archivo);
    return 1;
}

void liberarImagen(Imagen *img) {
    // verificamos que la direccion de memoria sea valida
    if (img) {
        // se libera cada fila de enteros
        for (int i = 0; i < img->alto; i++) free(img->pixeles[i]);
        free(img->pixeles);
        free(img);
    }
}
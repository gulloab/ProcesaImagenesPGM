#include <stdio.h>
#include "imagen.h"

int main() {
    printf("iniciando procesamiento automatico\n");

    printf("cargando la imagen para invertir...\n");
    Imagen *img1 = cargarImagenPGM("creeper.pgm");

    if (img1 != NULL) {
        printf("imagen cargada exitosamente: %dx%d\n", img1->ancho, img1->alto);
        
        invertirColores(img1);
        printf("colores invertidos.\n");
        
        guardarImagenPGM(img1, "creeper_invertido.pgm");
        printf("imagen guardada como creeper_invertido.pgm\n");
        
        liberarImagen(img1);
    } else {
        printf("error al cargar la imagen.\n");
    }

    printf("\n");

    printf("cargando la imagen para rotar...\n");
    Imagen *img2 = cargarImagenPGM("creeper.pgm");

    if (img2 != NULL) {
        printf("imagen cargada exitosamente: %dx%d\n", img2->ancho, img2->alto);
        
        rotarImagen90Grados(img2);
        printf("imagen rotada 90 grados a la derecha.\n");
        
        guardarImagenPGM(img2, "creeper_rotado.pgm");
        printf("imagen guardada como creeper_rotado.pgm\n");
        
        liberarImagen(img2);
    } else {
        printf("error al cargar la imagen.\n");
    }

    printf("cargando la imagen para filtro de caja...\n");
    Imagen *img3 = cargarImagenPGM("creeper.pgm");

    if (img3 != NULL) {
        printf("imagen cargada exitosamente: %dx%d\n", img3->ancho, img3->alto);
        
        aplicarFiltroCaja(img3);
        printf("filtro de caja fue aplicado.\n");
        
        guardarImagenPGM(img3, "creeper_caja.pgm");
        printf("imagen guardada como creeper_caja.pgm\n");
        
        liberarImagen(img3);
    } else {
        printf("error al cargar la imagen.\n");
    }
    
    printf("procesamiento finalizado correctamente");
    return 0;
}
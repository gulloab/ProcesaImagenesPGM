# Procesador de Imágenes PGM en C

Este repositorio contiene un programa implementado en C para la lectura, procesamiento y escritura de imágenes en formato PGM (Portable GrayMap) de tipo texto (`P2`). El sistema utiliza memoria dinámica para manipular matrices de píxeles y aplicar diferentes transformaciones visuales.

## Arquitectura del Proyecto

El proyecto está modularizado para separar la lógica de procesamiento de imágenes del flujo de ejecución principal:

* **`imagen.h`**: Archivo de cabecera que define la estructura `Imagen` (ancho, alto, valor máximo y matriz dinámica de píxeles) y los prototipos de las funciones.
* **`imagen.c`**: Contiene la implementación principal de la lógica. Se encarga de la gestión de memoria dinámica, la lectura/escritura de archivos (omitiendo comentarios `#`) y la aplicación de los algoritmos de transformación.
* **`main.c`**: Programa principal que actúa como un script de prueba automatizado. Carga una imagen base (`creeper.pgm`), le aplica todas las transformaciones disponibles, guarda los resultados y libera la memoria.
* **`Makefile`**: Archivo de configuración para automatizar el proceso de compilación utilizando `gcc`.

## Funcionalidades de Procesamiento

El sistema incluye las siguientes transformaciones de imagen:

* **Inversión de Colores (`invertirColores`)**: Recorre la matriz de la imagen y reemplaza cada píxel por su inverso lógico según el valor máximo (ej. `255 - pixel`), creando un efecto de negativo fotográfico.
* **Rotación de 90 Grados (`rotarImagen90Grados`)**: Gira la imagen 90 grados hacia la derecha. Implementa el intercambio de dimensiones (ancho por alto) y reasigna los píxeles en una nueva matriz dinámica mediante transformaciones geométricas.
* **Filtro de Caja (`aplicarFiltroCaja`)**: Aplica un filtro de desenfoque (blur) básico. Calcula el promedio de luz de los píxeles vecinos (en una cuadrícula de 3x3) y lo asigna al píxel central, utilizando una matriz temporal para no alterar el cálculo en cascada.

## Gestión de Memoria

Al estar desarrollado en C, el proyecto hace un uso intensivo de la memoria dinámica (`malloc` y `free`). La función `cargarImagenPGM` reserva memoria fila por fila para crear un arreglo 2D continuo, y la función `liberarImagen` se asegura de limpiar toda la memoria alojada al finalizar cada proceso, evitando fugas de memoria (memory leaks).

## Compilación y Uso

El proyecto incluye un `Makefile` para facilitar su compilación. Asegúrate de tener una imagen llamada `creeper.pgm` (formato P2) en el mismo directorio antes de ejecutarlo.

Para compilar el proyecto, abre tu terminal y ejecuta:

```bash
make
```

Esto generará un archivo ejecutable llamado `procesador`. Para ejecutarlo:

```bash
./procesador
```

### Salida Esperada
Al finalizar la ejecución, el programa generará tres nuevos archivos en tu directorio correspondientes a cada transformación:
1. `creeper_invertido.pgm`
2. `creeper_rotado.pgm`
3. `creeper_caja.pgm`

Para limpiar los archivos compilados (`.o`) y el ejecutable, puedes usar:

```bash
make clean
```
To compile the project, make sure you have `gcc` and `make` installed, then run:

```bash
make

#include "..\..\headers\mecanicas\imagenes.h"

/* FUNCIONES PÚBLICAS. */

/* Función para cargar hasta 10 sprites con igual nombre, pero numerados, en un array en memoria. */
Imagen * carga_sprites_array (int cantidadSprites, char rutaSprites[100], char caracterPermuta, int trasparencia)
{   
    /* Comprobación de la validez de la cantidad de sprites. */
    if (cantidadSprites <= 0 || cantidadSprites > 10)
    {
        printf ("%s\nProducido en la llamada con los parametros %d, %s.\nPulsa cualquier tecla para abortar.", ERROR_SPRITES_001, cantidadSprites, rutaSprites);
        scanf("%d");
        return NULL;
    };

    /* Entero usado para recorrer la cadena de la ruta. */
    int i = 0;
    /* Recorrido de la ruta para encontrar la posición del caracter de permuta. */
    while (rutaSprites[i] != '\0' && rutaSprites[i] != caracterPermuta)
    {
        i = i + 1;
    };
    /* Comprobación del valor en rutaSprites[i] por si se ha llegado al final de la cadena sin encontrar el caracter de permuta. */
    if (rutaSprites[i] == '\0')
    {
        printf ("%s\nProducido en la llamada con los parametros %d, %s.\nPulsa cualquier tecla para abortar.", ERROR_SPRITES_002, cantidadSprites, rutaSprites);
        scanf("%d");
        return NULL;
    }

    /* Reserva de memoria para el array de imágenes. */
    Imagen * arrayAux = malloc (cantidadSprites * sizeof(Imagen));

    /* Creo una cadena auxiliar de tamaño máximo de 100 caracteres en la que copio mi dirección para poder modificarla. */
    char cadenaAux[100];
    strcpy (cadenaAux, rutaSprites);

    /* Bucle de rellenado. */
    for (int j = 0; j < cantidadSprites; j = j + 1)
    {
        /* Cambio el caracter de permuta por el número correspondiente a la iteración del bucle para cargar todas las imágenes de mismo nombre numeradas en la posición del caracter de permuta. */
        cadenaAux[i] = j + PARAMETRO_CONVERSION_INT_CHAR;
        arrayAux[j] = Pantalla_ImagenLee (cadenaAux, trasparencia);
    };

    /* Devolución de la dirección del array. */
    return arrayAux;
};

/* Función para liberar un array de imágenes de memoria. */
int libera_sprites_array (Imagen * arraySprites, int cantidadSprites)
{
    /* Comprobación de errores. */
    if (arraySprites == NULL || cantidadSprites < 1 || cantidadSprites > 10)
    {
        printf("%s\nError en la llamada con parámetros %d, %d.\nPulsa cualquier tecla para continuar.", ERROR_SPRITES_003, arraySprites, cantidadSprites);
        scanf("%d");
        return 1;
    }

    /* Bucle que recorre y libera cada imagen del array. */
    for (int i = 0; i < cantidadSprites; i = i + 1)
    {
        Pantalla_ImagenLibera(arraySprites[i]);
    };

    /* Liberación de la memoria que ocupaba el array de imágenes. */
    free (arraySprites);

    return 0;
};

/* Función para cargar en memoria una imagen aleatoria de una lista de 10 imágenes ubicadas en una dirección dada. */
Imagen carga_sprite_aleatorio (int cantidadSpritesCarpeta, char rutaSprites[100], char caracterPermuta, int trasparencia)
{
    /* Comprobación de la validez de la cantidad dada. */
    if (cantidadSpritesCarpeta <= 0 || cantidadSpritesCarpeta > 10)
    {
        printf ("%s\nProducido en la llamada con los parametros %d, %s.\nPulsa cualquier tecla para abortar.", ERROR_SPRITES_001, cantidadSpritesCarpeta, rutaSprites);
        scanf("%d");
        return NULL;
    }
    
     /* Entero usado para recorrer la cadena de la ruta. */
    int i = 0;
    /* Recorrido de la ruta para encontrar la posición del caracter de permuta. */
    while (rutaSprites[i] != '\0' && rutaSprites[i] != caracterPermuta)
    {
        i = i + 1;
    };
    /* Comprobación del valor en rutaSprites[i] por si se ha llegado al final de la cadena sin encontrar el caracter de permuta. */
    if (rutaSprites[i] == '\0')
    {
        printf ("%s\nProducido en la llamada con los parametros %s.\nPulsa cualquier tecla para abortar.", ERROR_SPRITES_002, rutaSprites);
        scanf("%d");
        return NULL;
    };

    /* Creo una cadena auxiliar de tamaño máximo de 100 caracteres en la que copio mi dirección para poder modificarla. */
    char cadenaAux[100];
    strcpy (cadenaAux, rutaSprites);

    /* Genero un entero aleatorio. */
    int a = rand() % cantidadSpritesCarpeta;

    /* Modifico el caracter de permuta de mi cadena por un aleatorio entre 0 y cantidadSpritesCarpeta - 1. Después leo la imagen correspondiente.*/
    cadenaAux[i] = a + PARAMETRO_CONVERSION_INT_CHAR;
    Imagen imagenAux = Pantalla_ImagenLee (cadenaAux, trasparencia);

    return imagenAux;
};
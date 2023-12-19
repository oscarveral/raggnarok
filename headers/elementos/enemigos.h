/**
 * \file enemigos.h
 * \author Óscar Vera López
 * \brief Este módulo contiene la interfaz pública para la implementación de un ejercito de enemigos contenidos en memoria contigua. Reutilizaré la estructura del jugador para represnetar los enemigos.
 * \version 0.1
 * \date 2021-05-12
 */

#ifndef __ENEMIGOS_H__
#define __ENEMIGOS_H__

#include "jugador.h"

/**
 * \brief Constante que define la cantidad máxima recomendada de enemigos que se encuentran en pantalla.
 */
#define ENEMIGOS_MAXIMOS_RECOMENDADOS 30

/**
 * \brief Constante que define la vida base de los enemigos.
 */
#define ENEMIGOS_VIDAS_BASE 3

/**
 * \brief Definición de la estructura ejercito de enemigos.
 * 
 * \param arrayEnemigos Array de enemigos 
 * \param n_elementos Tipo entero. Cantidad de enemigos no vacios contenidos en el array.
 * \param capacidad_array Tipo entero. Cantidad máxima de enemigos que puede contener el array. 
 */
typedef struct EjercitoRep * EjercitoPtr;

/**
 * \brief Función que crea un ejercito en meoria reservando la memoria necesaria según la cantidad de elementos que tiene que almacenar.
 * 
 * \param max Tipo entero. Representa la cantidad de elementos como máximo que contendrá el array de enemigos del ejercito.
 * \return Devuelve el puntero al ejercito en memoria.
 */
EjercitoPtr crea_ejercito (int max);

/**
 * \brief Función que libera un ejercito completo de memoria.
 * 
 * \param ejercito Puntero a un dato tipo ejercito completo.
 */
void libera_ejercito (EjercitoPtr ejercito);

/**
 * \brief Función que rellena completamente el array de enemigos de un ejercito según los parámetros dados a la función. Las posiciones dadas como parámetros representan un campo en el que se generarán de forma aleatoria.
 * \pre Debe de exitir en memoria el ejercito dado como argumento.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \param xMax Tipo real. Representa la posición x máxima en la que podrá crearse el enemigo.
 * \param xMin Tipo real. Representa la posición x mínima en la que podrá crearse el enemigo.
 * \param yMax Tipo real. Representa la posición y máxima en la que podrá crearse el enemigo.
 * \param yMin Tipo real. Representa la posición y mínima en la que podrá crearse el enemigo.
 * \param radioEnemigo Tipo entero. Representa el radio de la hitbox de todos los enemigos creados en el array.
 * \param velocidadEnemigo Tipo real. Representa la velocidad de movimiento de los enemigos creados.
 * \param vidasEnemigos Tipo entero. Vidas que tienen los enemigos creados.
 */
void recluta_ejercito (EjercitoPtr ejercito, float xMax, float xMin, float yMax, float yMin, int radioEnemigos, float velocidadEnemigos, int vidasEnemigos);

/**
 * \brief Función que asigna a cada enemigo del array un ángulo en radianes respecto al punto dado.
 * 
 * \param ejercito Puntero a un ejercito en memoria. 
 * \param x Tipo real. Posición x del punto con el que se desea calcular el ángulo. 
 * \param y Tipo real. Posición y del punto con el que se desea calcular el ángulo.
 */
void orienta_ejercito (EjercitoPtr ejercito, float x, float y);

/**
 * \brief Función que dibuja cada enemigo del ejercito dado en pantalla. 
 * 
 * \param ejercito Puntero a un dato tipo ejercito en memoria.
 * \param arraySprites Puntero a un array de imágenes que usaremos para dibujar los enemigos.
 * \param cantidadImagenesArray Tipo entero. Representa la cantidad de imágenes contenidas en el array de sprites dado como parámetro.
 * \param desplazamientoSpritesMovimiento Tipo entero. Indica el índice del array donde comienzan los sprites de movimiento.
 * \param desplazamientoSpritesMuerte Tipo entero. Indica el índice del array donde comienzan los sprites de muerte.
 * 
 * \return Devuelve 0 si se ejecutó sin errores o por el contrario el número de errores encontrados en el dibujado del ejercito.
 */
int dibuja_ejercito (EjercitoPtr ejercito, Imagen * arraySprites, int cantidadImagenesArray,  int desplazamientoSpritesMovimiento, int desplazamientoSpritesMuerte);

/**
 * \brief Función que actualiza el contador de movimiento de los elementos al igual que lo hace la función de animación del módulo de jugador.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \param incrementoMovimiento Tipo real. Incrementos del contador de movimiento de los enemigos cuando se muevan.
 * \param longitudSegmento Tipo real. Longitud de los segmentos de animación de los enemigos.
 * \param multiplicadorSegmentos. Tipo real. Representa la cantidad de segmentos que tiene la animación.
 */
void animacion_ejercito (EjercitoPtr ejercito, float incrementoMovimiento, float longitudSegmento, float multiplicadorSegmentos);

/**
 * \brief Función que hace que los enemigos disparen balas de la ráfaga dada hacia donde están mirando. Los enemigos disparán 1 de cada 6 ejecucines de la función de forma aleatorio.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \param ptrCabecera Puntero a un nodo de cabecera de una ráfaga de balas.
 * \param radioBalas Tipo entero. Radio que tendrán las balas disparadas por los enemigos.
 * \param velocidadBalas Tipo entero. Velocidad que tendrán las balas disparadas pro los enemigos. 
 * \param enfriamientoDisparo Tipo entero. Representa el enfriamiento entre disparos de los enemigos.
 */
void dispara_ejercito (EjercitoPtr ejercito, NodoBalaPtr ptrCabecera, int radioBalas, int velocidadBalas, int enfriamientoDisparo);

/**
 * \brief Función que comprueba si un ejercito está vacío.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \return Devuelve 1 si no hay enemigos en el ejercito y 0 en caso contrario. 
 */
int ejercito_vacio (EjercitoPtr ejercito);

/**
 * \brief Función que calcula la colisión de todos los enemigos de un ejercito con una ráfaga de balas dada. Si ocurre en algun caso libera las balas que colisionan y restan 1 vida a la vida del enemigo con el que colisionan.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \param ptrCabecera Puntero al nodo de cabecera de una ráfaga de balas con la que se desea comprobar la colisión.
 */
void ejercito_colisiona_rafaga (EjercitoPtr ejercito, NodoBalaPtr ptrCabecera);

/**
 * \brief Función que actualiza el ejercito de enemigos eliminando aquellos que hayan muerto. Para ello aplica primero la animación de muerte y cuando acaba los libera de memoria, pone a nulo su entrada del array y decrementa el contador de enemigos del ejercito.
 * Hace uso de la función de animación de muerte del jugador.
 * 
 * \param ejercito Puntero a un ejercito en memoria.
 * \param incrementoMuerte Tipo real. Incremento del contador de muertes de cada enemigo muerto en cada llamada a la función.
 * \param longitudSegmento Tipo real. Longitud de segmento de la animación. Determinará el recorrido del contador de muerte de los enemigos.
 * \param multiplicadorSegmentos Tipo real. Cantidad de segmentos de animación. Determinará el recorrido del contador de muerte de los enemigos.
 * \param punteroPuntuación Puntero a entero. Puntero a la variable que almacena la puntuación de un programa.
 */
void muere_ejercito (EjercitoPtr ejercito, float incrementoMuerte, int longitudSegmento, int multiplicadorSegmentos, int * punteroPuntuacion);

/**
 * \brief Función que obtiene el número de enmigos vivos de un ejercito.
 * 
 * \param ejercito Puntero a un tipo ejercito en memoria.
 * \return Devuelve el campo n_elementos del ejercito.
 */
int enemigos_ejercito (EjercitoPtr ejercito);

/**
 * \brief Función que devuelve la cantidad máxima de enemigos que puede almacenar un ejercito.
 * 
 * \param ejercito Puntero a un tipo de dato ejercito en memoria.
 * \return Devuelve la cantidad máxima de enemigos que puede almacenar un ejercito.
 */
int maximos_enemigos_ejercito (EjercitoPtr ejercito);

/**
 * \brief Esta función proporciona 2 patrones de movimiento diferentes a los enemigos de un ejercito a partir de hacia donde miren y de su velocidad. 
 * Tenemos dos modos de moivmiento. Uno circular si el modo de movimiento es distinto de 0 y una más lineal si el modo de movimiento vale 0.
 * 
 * \param ejercito Puntero a un tipo de dato ejercito en memoria.
 * \param bordeSup Entero. Límite superior que no podrán sobrepasar los enemigos.
 * \param bordeInf Entero. Límite inferior que no podrán sobrepasar los enemigos.
 * \param bordeDer Entero. Límite derecho que no podrán sobrepasar los enemigos.
 * \param bordeIzq Entero. Límite izquierdo que no podrán sobrepasar los enemigos.
 * \param modoMovimiento Entero. A 0 los enemigos se moverán de forma circular y a cualquier otro valor de una fomra más "lineal". 
 */
void mueve_ejercito (EjercitoPtr ejercito, int bordeSup, int bordeInf, int bordeDer, int bordeIzq, int modoMovimiento);

#endif /* __ENEMIGOS_H__ */
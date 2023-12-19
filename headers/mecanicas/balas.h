/**
 * \file balas.h
 * \author Óscar Vera López
 * \brief Fichero de cabecera con la interfaz pública del módulo que permite la implementación de los disparos y balas en el programa. Las ráfagas de balas se implementará utilizando listas enlazadas.
 * \version 0.1
 * \date 2021-05-03
 */

#ifndef __BALAS_H__
#define __BALAS_H__

#include "hitbox.h"
#include "..\pantalla.h"
#include <stdio.h>

/**
 * \brief Constante que indica el radio base recomendado para que tengan las balas. (10 píxeles de radio).
 */
#define RADIO_BASE_BALAS 10

/**
 * \brief Constante que indica la velocidad de movimiento de las balas recomendada. (10 píxeles por fotograma).
 */
#define VELOCIDAD_BASE_BALAS 10

/**
 * \brief Constante que define los fotogramas recomendados de enfriamiento entre cada disparo de una bala. (20 fotogramas o 0.33s a 60FPS).
 */
#define ENFRIAMIENTO_BASE_BALAS 20

/**
 * \brief Mensaje de advertencia a la hora de crear e introducir balas en ráfagas ya creadas.
 */
#define WARNING_BALAS_001 "Atencion, parametros incorrectos en la creacion o insercion de balas en la lista siguiente, puede producir errores: "

/**
 * \brief Mensaje de error si se intenta acceder a una ráfaga inexistente. 
 */
#define ERROR_BALAS_001 "Error. Se está intentando acceder a una lista de balas inexistente."

/**
 * \brief Definición de las estructura nodo bala como puntero a estructura. Representa una bala con todas sus propiedades.
 * 
 * \param hitboxBala Puntero a un tipo de dato hitbox en memoria que actuará como caja de colisiones de la bala.
 * \param velocidadX Tipo real. Velocidad horizontal de la bala representada por el nodo.
 * \param velocidadY Tipo real. Velocidad vertical de la bala representada por el nodo.
 * \param sig Puntero a otro dato tipo nodoBala que sería el siguiente en la lista.
 */
typedef struct NodoBalaRep * NodoBalaPtr;

/**
 * \brief Función que crea el nodo de cabecera de una ráfaga de balas sobre la que podremos comenzar operar.
 * 
 * \return Devuelve el puntero a dicho nodo de cabecera.
 */
NodoBalaPtr crea_rafaga_balas ();

/**
 * \brief Función que crea una nueva bala y la inserta al comienzo de una ráfaga ya creada. Mostrará un mensaje de advertencia en consola si se le pasan parámetros incorrectos.
 * \pre El nodo de cabecera de la ráfaga proporcionada como parámetro debe existir en memoria.
 * 
 * \param ptrCabecera Puntero al nodo de cabecera de la ráfaga sobre la que se quiere insertar la bala.
 * \param x Tipo real. Posición x en la que se desea que esté el centro de dicha bala.
 * \param y Tipo real. Posición y en la que se desea que esté el centro de dicha bala.
 * \param radio Tipo entero. Radio de la hitbox de bala creada.
 * \param velocidad Tipo real. Módulo de la velocidad que tendría dicha bala.
 * \param anguloSalida Tipo real. Ángulo en radianes con el que la bala sería disparada en un principio. Sirve para descomponer la velocidad en sus componentes horizontal y vertical teniendo en cuenta el crecimiento descendente del eje Y.
 */
void dispara_bala_rafaga (NodoBalaPtr ptrCabecera, float x, float y, int radio, double velocidad, double anguloSalida);

/**
 * \brief Función que libera toda una lista de balas de memoria.
 * \pre Debe ser una lista existente. Si no existe devolverá un mensaje de error por consola.
 * 
 * \param ptrCabecera Puntero al nodo de cabecera de una ráfaga de balas existente.
 * \return Devuelve 0 si se liberó exitosamente la rñafaga y 1 junto a un mensaje de error si se produjo algún error en la liberación. 
 */
int libera_rafaga_balas (NodoBalaPtr ptrCabecera);

/**
 * \brief Función que devuelve el puntero a la hitbox del nodo dado.
 * 
 * \param nodoDado Puntero al nodoBala del que se desea obtener la hitbox. 
 * 
 * \return Puntero a la hitbox del nodo dado.
 */
HitboxPtr get_hitbox_nodobala (NodoBalaPtr nodoDado);

/**
 * \brief Función que devuelve el puntero al siguiente nodo bala al que apunta un nodo bala dado.
 * 
 * \param nodoDado Puntero al nodo bala del que se desea obtener el siguiente nodo.
 * 
 * \return Devuelve el puntero al nodo bala al que apunta nuestro nodo. 
 */
NodoBalaPtr get_sig_bala (NodoBalaPtr nodoDado);

/**
 * \brief Función que actualiza la posición de todas las balas de una ráfaga dada según las componentes de velocidad que tengan cada una.
 * 
 * \param ptrCabecera Puntero al nodo de cabecera de la lista de balas que se desea actualizar.
 */
void mueve_rafaga_balas (NodoBalaPtr ptrCabecera);

/**
 * \brief Función que recorre toda la lista de balas dada y libera de memoria aquellas que se encuentren fuera completamente de los límites dados sin romper la lista.
 * 
 * \param ptrCabecera Puntero al nodo de cabecera de la lista.
 * \param limiteSup Tipo entero. Límite superior.
 * \param limiteInf Tipo entero. Límite inferior.
 * \param limiteDer Tipo entero. Límite derecho.
 * \param limiteIzq Tipo entero. Límite izquierdo.
 */
void rafaga_fuera_limites (NodoBalaPtr ptrCabecera, int limiteSup,int limiteInf, int limiteDer, int limiteIzq);

/**
 * \brief Función que dibuja cada bala de una ráfaga de balas con el sprite dado como parámetro.
 * 
 * \param cabecera Puntero al nodo de cabecera de una ráfaga de balas.
 * \param spriteBala Tipo de dato imagen que se desea usar como sprite para representar las balas.
 */
void dibuja_rafaga_balas (NodoBalaPtr ptrCabecera, Imagen spriteBala);

/**
 * \brief Función que calcula la colisión de una ráfaga de balas con una hitbox dada.
 * 
 * \param ptrCabecera Puntero al nodo de cabecera de la ráfaga con la que se desea calcular la colisión.
 * \param hitbox Puntero al tipo de dato hitbox con el que se desea comprobar la colisión.
 * 
 * \return Devuelve 1 si al menos 1 de las balas que componen la ráfaga colisiona con la hitbox dada. Además si ocurre se liberan de memoria las balas que colisionen con la hitbox dada. Devuelve 0 en otro caso.
 */
int colision_rafaga_hitbox (NodoBalaPtr ptrCabecera, HitboxPtr hitbox);

#endif /* __BALAS_H__ */
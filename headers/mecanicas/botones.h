/**
 * \file botones.h
 * \author Óscar Vera López
 * \brief Módulo para la implementación de botones en el programa principal.
 * \version 0.1
 * \date 2021-05-13
 */

#ifndef __BOTONES_H__
#define __BOTONES_H__

#include "..\pantalla.h"
#include <string.h>

/**
 * \brief Constante que define los carácteres máximos de un botón. 
 */
#define BOTONES_TEXTO_MAX 100

/**
 * \brief Constante que define las cifras máximas de los números a escribir en los botones.
 */
#define BOTONES_CIFRAS_NUM_MAX 10

/**
 * \brief Cosntante que define los píxeles base de ancho de un botón recomendado.
 */
#define BOTON_ANCHO_BASE 100

/**
 * \brief Constante que define los píxeles base de alto de un botón recomendado.
 */
#define BOTON_ALTO_BASE 30

/**
 * \brief Estructura de un botón.
 * 
 * \param x Entero que representa la posición x de la esquina superior izquierda del botón.
 * \param y Entero que representa la posición y de la esquina superior izquierda del botón.
 * \param ancho Entero que representa el ancho del botón.
 * \param alto Entero que representa el alto del botón
 * \param texto Cadena de caracteres con máximo de 100 caracteres que contiene el texto del botón.
 */
typedef struct BotonRep * BotonPtr;

/**
 * \brief Función que crea en memoria un botón.
 * 
 * \param x Entero que representa la posición x de la esquina superior izquierda del botón.
 * \param y Entero que representa la posición y de la esquina superior izquierda del botón.
 * \param ancho Entero que representa el ancho del botón.
 * \param alto Entero que representa el alto del botón
 * \param texto Cadena de caracteres con máximo de 100 caracteres que contiene el texto del botón.
 * 
 * \return Devuelve el puntero al botón creado.
 */
BotonPtr crea_boton (int x, int y, int ancho, int alto, char texto[BOTONES_TEXTO_MAX]);

/**
 * \brief Fución que libera un botón de memoria.
 * 
 * \param boton Puntero a un botón en memoria.
 */
void libera_boton (BotonPtr boton);

/**
 * \brief Función que dibuja en pantalla el botón dado como un rectángulo de borde negro y fondo blanco y texto del color dado por las variables r,g,b. La variable a controla la transparencia de todo el botón. Se dibuja el texto medianamente centado con el botón.
 * 
 * \param boton Puntero a un botón en memoria.
 * \param r Entero que representa el color rojo del texto (0-255).
 * \param g Entero que representa el color verde del texto (0-255).
 * \param b Entero que representa el color azul del texto (0-255).
 * \param a Entero que representa la transparencia del botón (0-255).
 */
void dibuja_boton (BotonPtr boton, int r, int g, int b, int a);

/**
 * \brief Función que comprueba si se está pulsando con el ratón un botón. Se le proporciona las coordenadas sobre las que calcular la pulsación.
 * 
 * \param boton Puntero a un botón en memoria.
 * \param ratonX Tipo real. Posición X del ratón.
 * \param ratonY Tipo real. Posición Y del ratón.
 * 
 * \return Devuelve 1 si se ha pulsado el botón con el click izquierdo del ratón. Devuelve 0 en otro caso.
 */
int pulsa_boton (BotonPtr boton, double ratonX, double ratonY);

/**
 * \brief Función que cambia el texto de un botón dado.
 * 
 * \param boton Puntero a un botón en memoria.
 * \param nuevoTexto Cadena de caracteres de máximo 100 caracteres con el nuevo texto para el botón.
 */
void cambia_texto_boton (BotonPtr boton, char nuevoTexto[BOTONES_TEXTO_MAX]);

#endif /* __BOTONES_H__ */
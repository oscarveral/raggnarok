/**
 * \file hitbox.h
 * \author Óscar Vera López.
 * \brief Archivo que define el tratamiento de las hitbox del juego así como las funciones básicas de colisión. Al ser un juego simple usaremos solo circunferencias como hitboxes.
 * \version 0.1
 * \date 2021-04-18
 */

#ifndef __HITBOX_H__
#define __HITBOX_H__

#include <stdlib.h>

/* Por alguna razón no puedo utilizar las constantes definidas en math.h sin usar la siguiente declaración. */
#define _USE_MATH_DEFINES
#include <math.h>

/**
 * \typedef TDA Hitbox. Representa una caja de colisiones circular genérica. 
 * 
 * \param x Tipo real. Posición x en pantalla del centro de la hitbox.
 * \param y Tipo real. Posición y en pantalla del centro de la hitbox.
 * \param radio Tipo entero. Radio de la circunferencia de la hitbox a representar.
 */
typedef struct HitboxRep * HitboxPtr;

/**
 * \brief Función que reserva memoria e inicializa en ella un dato tipo hitbox.
 * 
 * \param x Tipo real. Posición x en pantalla del centro de la hitbox.
 * \param y Tipo real. Posición y en pantalla del centro de la hitbox.
 * \param radio Tipo entero. Radio de la circunferencia de la hitbox a representar.
 * 
 * \return Devuelve un puntero a la zona de la memoria en la que se aloja la hitbox creada.
 */
HitboxPtr crea_hitbox (float x, float y, int radio);

/**
 * \brief Función que libera la zona de memoria que ocupaba un dato tipo hitbox.
 * \pre El dato hitbox debe existir en memoria. No se puede liberar algo que no existe.
 * 
 * \param hitbox Puntero a un dato tipo hitbox en memoria.
 */
void libera_hitbox (HitboxPtr hitbox);

/**
 * \brief Función que obtiene el campo x de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * 
 * \return Tipo real. Devuelve dicho valor del campo x.
 */
float get_x_hitbox (HitboxPtr hitbox);

/**
 * \brief Función que obtiene el campo y de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * 
 * \return Tipo real. Devuelve dicho valor del campo y.
 */
float get_y_hitbox (HitboxPtr hitbox);

/**
 * \brief Función que obtiene el campo radio de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * 
 * \return Tipo entero. Devuelve dicho valor del campo radio.
 */
int get_radio_hitbox (HitboxPtr hitbox);

/**
 * \brief Función que modifica el valor del campo x de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param x Tipo real. Nuevo valor que se desea poner en dicho campo.
 */
void modify_x_hitbox (HitboxPtr hitbox, float x);

/**
 * \brief Función que modifica el valor del campo y de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param y Tipo real. Nuevo valor que se desea poner en dicho campo.
 */
void modify_y_hitbox (HitboxPtr hitbox, float y);

/**
 * \brief Función que modifica el valor del campo radio de un dato tipo hitbox.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param radio Tipo entero. Nuevo valor que se desea poner en dicho campo.
 */
void modify_radio_hitbox (HitboxPtr hitbox, int radio);

/**
 * \brief Función que determina si dos datos tipo hitbox se encuentran en colisión. 
 * 
 * \param hitbox1 Puntero a un tipo de dato hitbox que se encuentra en memoria.
 * \param hitbox2 Puntero a otro tipo de dato hitbox que se encientra en memoria.
 * 
 * \return Devuelve 0 si las dos hitbox no están colisionando y 1 en el caso de que si lo hagan.
 */
int colision_hibox_hitbox (HitboxPtr hitbox1, HitboxPtr hitbox2);

/**
 * \brief Función que determina si un dato tipo hitbox colisiona con, o supera por encima un borde superior establecido.
 * \pre El sistema de coordenadas con el que trabajamos tiene que tener un eje Y que crezca en dirección contraria al del plano cartesiano, es decir, hacia abajo.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria. 
 * \param limiteSup Tipo entero. Dato que representa la línea imaginaria que marcará la zona de colisión superior.
 * 
 * \return Devuelve 1 si el dato hitbox colisiona con, o supera por encima la línea horizontal imaginaria definida por limiteSup. Devuelve 0 en otro caso.
 */
int colision_hitbox_limiteSup (HitboxPtr hitbox, int limiteSup);

/**
 * \brief Función que determina si un dato tipo hitbox colisiona con, o supera por debajo un borde inferior establecido.
 * \pre El sistema de coordenadas con el que trabajamos tiene que tener un eje Y que crezca en dirección contraria al del plano cartesiano, es decir, hacia abajo.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param limiteInf Tipo entero. Dato que representa la línea imaginaria que marcará la zona de colisión inferior.
 * 
 * \return Devuelve 1 si el dato hitbox colisiona con, o supera por debajo la línea horizontal imaginaria definida por limiteInf. Devuelve 0 en otro caso.
 */
int colision_hitbox_limiteInf (HitboxPtr hitbox, int limiteInf);

/**
 * \brief Función que determina si un dato tipo hitbox colisiona con, o supera por la izquierda un borde izquierdo establecido. 
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param limiteIzq Tipo entero. Dato que representa la línea imaginaria que marcará la zona de colisión izquierda.
 * 
 * \return Devuelve 1 si el dato hitbox colisiona con, o supera por la izquierda la línea vertical imaginaria definida por limiteIzq. Devuelve 0 en otro caso.
 */
int colision_hitbox_limiteIzq (HitboxPtr hitbox, int limiteIzq);

/**
 * \brief Función que determina si un dato tipo hitbox colisiona con, o supera por la derecha un borde derecho establecido.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox en memoria.
 * \param limiteDer Tipo entero. Dato que representa la línea imaginaria que marcará la zona de colisión derecha.
 * 
 * \return Devuelve 1 si el dato hitbox colisiona con, o supera por la derecha la línea vertical imagínaria definida por limiteDer. Devuelve 0 en otro caso.
 */
int colision_hitbox_limiteDer (HitboxPtr hitbox, int limiteDer);

/**
 * \brief Función que debuelve el ángulo con el eje horizontal de un punto dado respecto al centro de una hitbox dada.
 * \pre Debemos trabajar con un sistema de coordenadas con eje Y descendente, como ocurre normalmente con las pantallas.
 * 
 * \param hitbox Puntero a un tipo de dato hitbox alojado en memoria.
 * \param x Tipo real. Coordenada en el eje x del punto dado con el que queremos calcular el ángulo.
 * \param y Tipo real. Coordenada en el eje y del punto dado con el que queremos calcular el ángulo.
 * 
 * \return Devuelve un real que representa el ángulo en radianes del punto dado respecto al centro de la hitbox dada.
 */
float angulo_hitbox_punto (HitboxPtr hitbox, float x, float y);

/**
 * \brief Función que dado un vecor con su módulo y ángulo lo descompone en sus componentes horizontal y vertical.
 * 
 * \param modulo Real de doble precision. Módulo del vector dado.
 * \param angulo Real de doble precision. Ángulo del vector en radianes.
 * \param componenteX Real de doble precisión. Puntero al real donde se almacenará la componente x.
 * \param componenteY Real de doble precisión. Puntero al real donde se almacenará la componente y.
 */
void descompon_vector (double modulo, double angulo, double * componenteX, double * componenteY);

#endif /* __HITBOX_H__ */
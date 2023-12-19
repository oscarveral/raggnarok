/**
 * \file jugador.h
 * \author Óscar Vera López
 * \brief Módulo para la implementación del tipo de dato jugador que permita al usuario interactuar con el juego.
 * \version 0.1
 * \date 2021-04-24
 */

#ifndef __JUGADOR_H__
#define __JUGADOR_H__

#include <stdio.h>
#include "..\mecanicas\hitbox.h"
#include "..\mecanicas\balas.h"
#include "..\pantalla.h"

/**
 * \brief Constante que representa la velocidad base de movimiento por pantalla de un tipo de dato jugador. Establecida en 4 píxeles por fotograma.
 */
#define JUGADOR_VELOCIDAD_BASE 4

/**
 * \brief Constante que representa el radio base de la hitbox de un tipo de dato jugador. Establecido a 35 píxeles por defecto.
 */
#define JUGADOR_RADIO_BASE 35

/**
 * \brief Constante que define el incremento base del contador de movimiento de los datos tipo jugador a la hora de utilizar funciones de animación.
*/
#define JUGADOR_INCREMENTO_MOVIMIENTO 0.05

/**
 * \brief Constante que define cuanto se recomienda que mida un segmento de la función de animación del jugador de este módulo.
 */
#define JUGADOR_LONGITUD_SEGMENTO_BASE 1

/**
 * \brief Constante que define la cantidad de segmentos que se recomienda que tenga la función de animación.
 */
#define JUGADOR_CANTIDAD_SEGMENTOS_BASE 3

/**
 * \brief Constante que representa las vidas del jugador.
 */
#define JUGADOR_VIDAS_BASE 10

/**
 * \brief Constante que define la cantidad de fotogramas de invulnerabilidad recomendados. (180 equivalen a 3 seg a 60 FPS)
 */
#define JUGADOR_DURACION_INVULNERABLE 180

/**
 * \brief Definición del mensaje de error que arrojará la consola si se dan malas coordenadas para la creación de un dato tipo jugador.
 */
#define ERROR_JUGADOR_001 "Posible error en las coordenadas, radio o velociadad dada para la creacion del jugador. Comprueba que son valores positivos."

/**
 * \brief Definición del mensaje de error en la liberación de datos tipos jugador.
 */
#define ERROR_JUGADOR_002 "Error de memoria de un dato tipo jugador. Comprueba que el parámetro dato se corresponde con dicho dato y fue alojado en memoria anteriormente"

/**
 * \brief Definición del mensaje de error arrojado por consola por la función de dibujado de un dato tipo jugador si el indice calculado a partir del contador de movimiento es mayor que el tamaño del array dado.
 */
#define ERROR_JUGADOR_003 "Error al intentar acceder al array de imágenes proporcionado, comprueba los valores de los parámetros dados."

/**
 * \typedef Tipo de dato abstracto jugador.
 * 
 * \param hitbox Tipo de dato hitbox que representa la caja de colisión del jugador.
 * \param estadoMovimiento Tipo entero. Representa el estado de movimiento del jugador. Si vale 0 es que el jugador está quieto y si vale 1 es que se encuentra en movimiento.
 * \param contadorMovimiento Tipo real. Sirve para contar la cantidad de fotogramas que el jugador se encuentra en movimiento. Se inicializa a 0 cuando se crea el dato. Puede usarse para determinar que sprites mostrar para representar al jugador.
 * \param velocidadMovimiento Tipo real. Representa la velocidad de movimiento del tipo de dato jugador.
 * \param anguloJugador Tipo real de doble precisión. Representa un ángulo en radianes que puede usarse para representar al jugador o para cualquier otra cosa que el programador quiera.
 * \param enfriamientoInteraccion Tipo entero. Representa un contador de espera para realizar una accion determinada. El programador es libre de elegir para que acción utilizar este contador, en un videojuego se podría usar para el enfriamiento de disparos. 
 * \param vidas Tipo entero. Representa las vidas que tiene el jugador.
 * \param invencible Tipo entero. Puede usarse para determinar si un dato tipo jugador puede ser dañado. Se asume que si vale 0 si puede y si vale 1 no.
 * \param contadorMuerte Tipo real. Puede utilizarse para hacer animaciones de muerte al igual que el contador de movimiento para animaciones de movimiento.
 */
typedef struct JugadorRep * JugadorPtr;

/**
 * \brief Función que crea un tipo de dato jugador y lo aloja en memoria. 
 * 
 * \param x Tipo real. Posición en el eje x del centro de la hitbox del tipo de dato jugador.
 * \param y Tipo real. Posición en el eje y del centro de la hitbox del tipo de dato jugador.
 * \param radio Tipo entero. Radio de la hitbox del tipo de dato jugador.
 * \param velocidad Tipo real. Representa el módulo del vector velocidad del dato tipo jugador creado.
 * \param vidas Tipo entero. Representa las vidas que tendrá el jugador. 
 * 
 * \return Devuelve un puntero a la zona de memoria en la que está almacenado el tipo de dato jugador.
 */
JugadorPtr crea_jugador (float x, float y, int radio, float velocidad, int vidas);

/**
 * \brief Función que libera un tipo de dato jugador de memoria.
 * \pre El dato tipo jugador debe existir y estar alojado en memoria para poder invocar a esta función.
 * 
 * \param jugador Puntero a un tipo de dato jugador alojado en memoria.
 * 
 * \return Devuelve 0 si la liberación se efectuó con éxito o 1 si ocurrión algún error debido al mal paso de parámetros.
 */
int libera_jugador (JugadorPtr jugador);

/**
 * \brief Permute recuperar la dirección de memoria en la que se ubica el puntero al tipo de dato hitbox que posee el jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador ubicado en memoria.
 * 
 * \return Devuelve el puntero a dicha hitbox.
 */
HitboxPtr get_hitbox_jugador (JugadorPtr jugador);

/**
 * \brief Función que devuelve el entero almacenado en el campo estadoMovimiento de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador ubicado en memoria.
 * 
 * \return Devuelve el valor de dicho campo del dato jugador dado.
 */
int get_estadoMovimiento_jugador (JugadorPtr jugador);

/**
 * \brief Funciónq que cambia el valor del campo estadoMovimiento de un dato tipo jugador.
 * 
 * \param jugador Puntero a un dato tipo jugador ubicado en memoria.
 * \param nuevoValor Tipo entero. Representa el nuevo valor que se desea almacenar en dicho campo.
 */
void modify_estadoMovimiento_jugador (JugadorPtr jugador, int nuevoValor);

/**
 * \brief Función que recupera el valor del campo contadorMovimiento del dato tipo jugador dado.
 * 
 * \param jugador Puntero a un tipo de dato jugador alojado en memoria.
 * 
 * \return Devuelve el real que almacenaba dicho campo.
 */
float get_contadorMovimiento_jugador (JugadorPtr jugador);

/**
 * \brief Función que modifica el valor del campo contadorMovimiento de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador alojado en memoria.
 * \param nuevoValor Tipo real. Nuevo dato que se desea almacenar en dicho campo.
 */
void modify_contadorMovimiento_jugador (JugadorPtr jugador, float nuevoValor);

/**
 * \brief Función que mueve por la pantalla hacia arriba el dato jugador según la velocidad que tenga. Además pone a 1 el estado de movimiento del jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 */
void mueve_arriba_jugador (JugadorPtr jugador);

/**
 * \brief Función que mueve por la pantalla hacia abajo el dato jugador según la velocidad que tenga. Además pone a 1 el estado de movimiento del jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 */
void mueve_abajo_jugador (JugadorPtr jugador);

/**
 * \brief Función que mueve por la pantalla hacia la derecha el dato jugador según la velocidad que tenga. Además pone a 1 el estado de movimiento del jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 */
void mueve_derecha_jugador (JugadorPtr jugador);

/**
 * \brief Función que mueve por la pantalla hacia la izquierda el dato jugador según la velocidad que tenga. Además pone a 1 el estado de movimiento del jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 */
void mueve_izquierda_jugador (JugadorPtr jugador);

/**
 * \brief Función que permite establecer una animación de movimiento a partir de la variación en cada llamada a esta función del contador de movimiento de un dato tipo jugador.
 * Para que la animación se ejecute el estado de movimiento debe valer 1, si deja de valer 1 el contador se reinicia y por tanto la animación.
 * Esta función establece 3 zonas o segmentos de animación según el valor que toma el contador de movimiento. La primera, cuando el jugador está quieto, en la que el contador vale 0.
 * La segunda es cuando se está comenzando a mover, y ocurre cuando el contador toma valores entre 0 y longitudSegmento. La 3ª zona es la de movimiento completo que ocurre entre los valores de
 * longitudSegmento y longitudSegmento * multiplicadorSegmentos. Si pasa el suficiente tiempo el contador de movimiento oscilará en esta 3ª zona hasta que el jugador se vuelva a quedar quieto. 
 * Esto me permite jugar con los valores en los que oscila el contador para obtener enteros que pueda usar para seleccionar las imágenes que dibujar en cada momento de las que hay en un array de imágenes dado.
 * Destacar que el rango de oscilación debería ser entre longitudSegmento y longitudSegmento * multiplicadorSegmentos, pero para evitar problemas cuando se use esta función para obtener 
 * enteros por aproximación superior del contador se ha determinddo que el rango de oscilación sea un poco más pequeño, en concreto 2*incrementoMovimiento más pequeño. Es decir en realidad
 * el contador oscila entre longitudSegmento + incrementoMovimiento y longitudSegmento * multiplicadorSegmentos - incrementoMovimiento.
 * 
 * \param jugador Puntero a un tipo de dato jugador alojado en memoria.
 * \param parametroMovimiento Tipo real. Establece el incremento del contador de movimiento por cada vez que se ejecuta la función.
 * \param longitudSegmento Tipo real. Valor máximo que alcanzará un segmento del contador de movimiento.
 * \param multiplicadorSegmentos Tipo real. Establece la cantidad de segmentos que recorrerá el contador, y por tanto el valor máximo que alcanzará el contador de movimiento.
 */
void animacion_movimiento_jugador (JugadorPtr jugador, float incrementoMovimiento, float longitudSegmento, float multiplicadorSegmentos);

/**
 * \brief Función que devuelve el valor contenido en el campo anguloJugador de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \return Devuelve un real de doble precisión contenido en dicho campo del dato.
 */
double get_angulo_jugador (JugadorPtr jugador);

/**
 * \brief Función que modifica el valor del campo anguloJugador del dato jugador dado como parámetro.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param nuevoAngulo Real de doble precisión. Valor del nuevo ángulo en radianes que se desea almacenar en el campo anguloJugador del dato dado.
 */
void modify_angulo_jugador (JugadorPtr jugador, double nuevoAngulo);

/**
 * \brief Función que recupera el valor del campo enfriamientoInteracción de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \return Devuelve el entero almacenado en dicho campo. 
 */
int get_enfriamientoInteraccion_jugador (JugadorPtr jugador);

/**
 * \brief Función que modifica el campo de enfriamiento de interacción de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param nuevoEnfriamiento Entero que representa el nuevo valor a almacenar en dicho campo.
 */
void modify_enfriamientoInteraccion_jugador (JugadorPtr jugador, int nuevoEnfriamiento);

/**
 * \brief Función que dibuja al jugador en pantalla utilizando el array de imágenes proporcionado y el contador de movimiento y muerte del jugador. La función aproxima los contadores para establecer el índice de la imagen del array que se utilizará.
 * Dependerá de si las vidas valen 0 usar los sprites de muerte o movimiento. Por razones de diseño y uso de los sprites disponibles aproximo el contador de movimiento con ceil y el contador de muerte con floor.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param punteroArray Puntero al primer elemento de un array de imágenes con las que se dibujará al jugador.
 * \param cantidadImagenesArray Cantidad de imágenes contenidas en el array dado, sirve para evitar accesos indevidos a memoria.
 * \param desplazamientoSpritesMovimiento Tipo entero. Indica el índice del array donde comienzan los sprites de movimiento.
 * \param desplazamientoSpritesMuerte Tipo entero. Indica el índice del array donde comienzan los sprites de muerte.
 * 
 * \return La función dibuja la imagen correspondiente en cada momento para el jugador así como devuelve 0 si todo va bien y 1 junto a un mensaje en consola si ocurre un error.
 */
int dibuja_jugador (JugadorPtr jugador, Imagen * punteroArray,int cantidadImagenesArray, int desplazamientoSpritesMovimiento, int desplazamientosSpritesMuerte);

/**
 * \brief Función que premite a un dato tipo jugador disparar una bala en una ráfaga dada como argumento. Actualiza el enfriamiento de interacción del jugador para evitar disparos muy rápidos.
 * 
 * \param jugador Puntero a un dato tipo jugador en memoria.
 * \param ptrCabecera Puntero a un nodo de cabecera de una ráfaga en memoria.
 * \param radioBalas Tipo entero. Radio que se desea que tengan las balas disparadas.
 * \param velocidadBalas Tipo entero. Velocidad que se desea que tengan las balas disparadas.
 * \param enfriamientoDisparo Tipo entero. Fotogramas de enfriamiento mínimo entre disparos.
 */
void dispara_jugador (JugadorPtr jugador, NodoBalaPtr ptrCabecera, int radioBalas, int velocidadBalas, int enfriamientoDisparo);

/**
 * \brief Función que devuelve las vidas de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * 
 * \return Devuelve la cantidad de vidas del jugador.
 */
int get_jugador_vidas (JugadorPtr jugador);

/**
 * \brief Función que modifica el campo de vidas de un dato tipo jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param nuevaVidas Tipo enterno. Nuevo valor que almacenar en dicho campo.
 */
void modify_jugador_vidas (JugadorPtr jugador, int nuevaVidas);

/**
 * \brief Función que comrpueba si un dato tipo jugador ha muerto.
 * 
 * \param jugador Puntero a un tipo de dato jugador.
 * 
 * \return Devuelve 1 si el dato tipo jugador tiene 0 vidas y 0 en otro caso.
 */
int jugador_muerto (JugadorPtr jugador);

/**
 * \brief Función que calcula si una ráfaga de balas colisiona con un jugador y elimina las balas de la ráfaga que colisionen.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param ptrCabecera Puntero a la cabecera de una ráfaga de balas.
 * 
 * \return Devuelve 1 si alguna bala de la ráfaga colisiona con el jugador y 0 en el caso contrario. Las balas quee colisionen son liberadas de memoria.
 */
int jugador_colisiona_rafaga (JugadorPtr jugador, NodoBalaPtr ptrCabecera);

/**
 * \brief Función que describe la animación de muerte de un dato tipo jugador a través de la actualización de su contador de muerte en sucesivas llamadas.
 * A partir de este contador se pueden establecer los índices que permitan dibujar la muerte a través de un array de imágenes. Se describe un simple recorrido desde el valor inicial hasta longitudSegmento * multiplicadorSegmento - incrementoMuerte del contador de muerte del jugador.
 * El contador de muerte se inicializa a 0 para todos los nuevos dato tipo jugador. Incremento el contador hasta un poco menos de la multiplicación de la cantidad de segmentos por su longitud para evitar problemas de aproximación con la función floor para obtener enteros.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param incrementoMuerte Tipo real. Incremento en cada llamada del contador de muerte.
 * \param longitudSegmento Tipo real. Representa la longitud de un segmento de la animación a realizar y por tanto determina el máximo del contador de muerte.
 * \param multiplicadorSegmentos Tipo real. Representa la cantidad de segmentos de la animación y por tanto determina el tamaño máximo del contador de muerte.
 * 
 * \return Además de actualizar el contador de muerte devuelve 1 cuando la animación esté acabada y 0 en otro caso. Puede usarse para determinar cuando liberar un jugador de memoria.
 */
int animacion_muerte_jugador (JugadorPtr jugador, float incrementoMuerte, float longitudSegmento, float multiplicadorSegmentos);

/**
 * \brief Función que obtiene la velocidad de un dato tipo jugador dado.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * 
 * \return Devuelve el real de simple precisión almacenado en el campo de velocidad de movimiento del jugador.
 */
float get_velocidad_jugador (JugadorPtr jugador);

/**
 * \brief Función que cambia las coordenadas en las que se encuentra un jugador.
 * 
 * \param jugador Puntero a un tipo de dato jugador en memoria.
 * \param x Real que representa la nueva posición x deseada.
 * \param y Real que representa la nueva y deseada.
 */
void modify_pos_jugador (JugadorPtr jugador, float x, float y);

/**
 * \brief Función que modifica el valor del campo invencible de un dato tipo jugador.
 * 
 * \param jugador Puntero al tipo de dato jugador cuyo campo queremos modificar.
 * \param nuevoValor Entero. Nueva cantidad a almacenar en dicho campo.
 */
void modify_invencible_jugador (JugadorPtr jugador, int nuevoValor);

/**
 * \brief Función que recupera el valor del campo invencible de un dato tipo jugador.
 * 
 * \param jugador Puntero a un dato tipo jugador en memoria.
 * \return Devuelve el entero almacenado en dicho campo.
 */
int get_invencible_jugador (JugadorPtr jugador);

#endif /* __JUGADOR_H__ */
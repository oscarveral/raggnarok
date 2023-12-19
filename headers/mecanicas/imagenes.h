/**
 * \file imagenes.h
 * \author Óscar Vera López
 * \brief Módulo para la gestión, carga y descarga de memoria de las imágenes utilizadas por el programa.
 * \version 0.1
 * \date 2021-04-21
 */

#ifndef __IMAGENES_H__
#define __IMAGENES_H__

#include "..\pantalla.h"
#include <string.h>

/**
 * \brief Constante que define la cantidad de sprites disponibles para el jugador. Se corresponde directamente con el número de sprites en el directorio de imágenes del jugador.
 * La correspondencia de las imágenes en carpeta con su número en el nombre es la siguiente:
 *      
 *      - 0. Imagen del jugador cuando está quieto
 *      - 1. Imagen del jugador cuando se comienza a mover.
 *      - 2. Imagen del jugador cuando se está moviendo 1.
 *      - 3. Imagen del jugador cuando se está moviendo 2.
 *      - 4. Imagen del jugador cuando es destruido 1.
 *      - 5. Imagen del jugador cuando es destruido 2.
 *      - 6. Imagen del jugador cuando es destruido 3.
 * 
 * La misma estructura de sprites se emplea también para las imágenes del enemigo.
 */
#define N_SPRITES_JUGADOR 7

/**
 * \brief Constante que define el índice según el orden de los sprites en carpeta donde comienzan los sprites de movimiento.
 */
#define ORIGEN_SPRITES_MOVIMIENTO 0

/**
 * \brief Constante que define el índice según el orden de los sprites en carpeta donde comienzan los sprites de muerte.
 */
#define ORIGEN_SPRITES_MUERTE 4

/**
 * \brief Definición de la cantidad de fondos ubicados en el directorio de fondos del programa. En concreto podremos elegir de entre 10 fondos disponibles.
 */
#define N_SPRITES_FONDO 10

/**
 * \brief Constante que define el parámetro de conversión de numero entero a su representación ASCII.
 */
#define PARAMETRO_CONVERSION_INT_CHAR 48

/**
 * \brief Constante que define el mensaje de error que arrojará la consola si se produce un error en la carga de sprites.
 */
#define ERROR_SPRITES_001 "Error al cargar sprites, comprueba que la cantidad introducida es un valor 0 <= x <= 10."

/**
 * \brief Constante que define el mensaje de rror que arrojará la consola si no se encuentra el caracter de permuta en la ruta de las imágenes.
 */
#define ERROR_SPRITES_002 "Error en la ruta de acceso a las imagenes. Comprueba que esta bien introducida y que contiene el caracter de permuta dado y que este esta utilizado unicamente para la permuta."

/**
 * \brief Definición del mensaje de error mostrado cuando ocurre un error al liberar la memoria de un array de imágenes.
 */
#define ERROR_SPRITES_003 "Error en la liberación de las imágenes contenidas en un array. Comprueba que el array pasado a la función se encuentra en memoria y la cantidad es positiva con un valor entre 1 y 10"

/**
 * \brief Función que carga en un array en memoria un máximo de 10 imágenes de una ruta especificada.
 * \pre Se debe tener una ruta válida a los archivos y comprobar que estos exxisten con el nombre dado.
 * 
 * \param cantidadSprites Tipo entero. Indica la cantidad de imágenes a cargar en el array. Debe ser un número entre 1 y 10, es decir, el array contendrá un máximo de 10 imágenes. Si su valor se encuentra fuera de este rango la función devuelve NULL y se imprime un código de error.
 * \param rutaSprites Cadena de caractéres de un máximo de 100 caracteres que indica la ruta genérica (desde el ejecutable del programa si se usan rutas relativas) a las imágenes que se desean cargar en el array.
 * \param caracterPermuta Tipo caracter. Caracter que se utilizará para sustituirlo en la cadena de la ruta por un número desde 0 hasta cantidadSprites - 1 para acceder y leer las imágenes númeradas en dicha ruta. Si dicho caracter no aparece en la ruta la función devuelve NULL y se imprime un código de error.
 * \param trasparencia Tipo entero. Si vale 0 entonces se cargará el fondo de las imágenes. Para cualquier otro valor tomará el color del pixel superior izquierdo de la imagen y lo asumirá como trasparente en la carga.
 * 
 * \return Devuelve un puntero al comienzo del array donde se han almacenado las imágenes. En caso de dar error se devolverá NULL y se imprimirá el código de error correspondiente si el error es sobre la cantidad de sprites o el caracter de permuta. Si se intentan leer imágenes de una ruta que no existe también dará error y se cerrará el programa automáticamente aunque no devuelva ningún código de error definido.
 * 
 * Ejemplo de uso. Se le pasan de parámetros un 10 en cantidad, "images\\jugador\\jugador_k.bmp" como ruta relativa estando el ejecutable en el mismo directorio que el directorio images, y 'k' como caracter de permuta. La función cargará entonces las imágenes llamadas de jugador_0.bmp a jugador_9.bmp ubicadas en la ruta "images\\jugador e un array"
 */
Imagen * carga_sprites_array (int cantidadSprites, char rutaSprites[100], char caracterPermuta, int trasparencia);

/**
 * \brief Función que libera de memoria un array de imágenes previamente cargado.
 * \pre El array debe de existir en memoria y se debe conocer su tamaño para poder liberarlo.
 * 
 * \param arraySprites Puntero a un array de imágenes en memoria que se desea liberar.
 * \param cantidadSprites Cantidad de elementos que contiene dicho array de imágenes. Dar un valor distinto al tamaño real puede dejar imágenes sin liberar si es menor o puede causar una excepción y abortar la ejecución del programa si es mayor, dejando entonces memoria sin liberar. Debe ser un valor positivo entre 1 y 10.
 * 
 * \return Devuelve 0 si la liberación de imágenes finalizó de forma correcta y 1 si ocurrió algun error al pasarle mal los parámetros a la función.
 */
int libera_sprites_array (Imagen * arraySprites, int cantidadSprites);

/**
 * \brief Función que carga en memoria una de las 10 imágenes numeradas ubicadas en la ruta genérica dada como parámetro.
 * \pre Se debe tener una ruta válida a los archivos y comprobar que estos exxisten con el nombre dado.
 * 
 * \param cantidadSpritesCarpeta. Tipo entero. Se corresponde con la cantidad de sprites uibicados en la ruta genérica dada. Va de 1 a 10, es decir, solopodemos cargar imágenes de igual nombre numeradas del 0 al 9 en la ruta especificada. 
 * \param rutaSprites Cadena de caracteres de un tamaño máximo de 100 caracteres. Indica la ruta genérica (desde el ejecutable del programa si se usan rutas relativas) a las imágenes de las que se quiere seleccionar y cargar una aleatoria.
 * \param caracterPermuta Tipo caracter. Se utilizará para buscarlo en la ruta especificada y sustituirlo por el número de imagen correspondiente entre 0 y cantidadSpritesCarpeta - 1 y así poder cargar después la imagen correspondiente.
 * \param trasparencia Tipo entero. Si vale 0 entonces se cargará el fondo de las imágenes. Para cualquier otro valor tomará el color del pixel superior izquierdo de la imagen y lo asumirá como trasparente en la carga.
 * 
 * \return Devuelve el puntero a la imagen cargada si se finalizó satisfactoriamente y NULL junto a un mensaje de error si se produjo algún error con los parámetros dados.  
 * 
 * Ejemplo de funcionamiento. Si de ruta se le pasa "images\\fondo\\fondo_z.bmp", de caracter de permuta 'z', de cantidad de sprites en carpeta 10 y transparencia 1 la funcion delvolverá el puntero a una imagen aleatoria de las que hay en carpeta llamadas de fondo_0.bmp a fondo_9.bmp.
 */
Imagen carga_sprite_aleatorio (int cantidadSpritesCarpeta, char rutaSprites[100], char caracterPermuta, int trasparencia);

#endif /* __IMAGENES_H__ */
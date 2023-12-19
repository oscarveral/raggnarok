
/**
   \file Pantalla.h
   \brief  Fichero de cabecera para poder usar las funciones del wrapper Pantalla
   \author FIUM
*/

#ifndef __Pantalla_H__
#define __Pantalla_H__

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <math.h>

/**
    \brief TDA Imagen
 */
typedef struct ImagenRep *Imagen;

/**
  \brief Crea, configura y activa una ventana gráfica en donde aparecer el resultado de las distintas primitivas gráficas que se vayan aplicando.

  Debe ser ejecutada antes que ninguna otra primitiva gráfica, especialmente las que se encargan de leer imágenes de disco.

  \param titulo Título de la ventana.
  \param w Anchura de la ventana en puntos.
  \param h Altura de la vantana en puntos.
 */
void Pantalla_Crea(char *titulo, int w, int h);

/**
  \brief Libera la memoria reservada para la pantalla y sus recursos asociados.

  Debe ser ejecutada en último lugar. Si se ejecuta alguna primitiva gráfica después de esta se producir un error en tiempo de ejecución.
 */
void Pantalla_Libera();

/**
  \brief Recupera la anchura de la pantalla.
  \return La anchura de la pantalla.
*/
int Pantalla_Anchura();

/**
  \brief Recupera la altura de la pantalla.
  \return La altura de la pantalla.
*/
int Pantalla_Altura();

/**
  \brief Indica si la pantalla está activa o no. La pantalla deja de estar activa cuando el usuario la cierra.
  \return 1 si la pantalla está activa.
  \return 0 si la pantalla no esta activa.
 */
int Pantalla_Activa();

/**
 \brief Detiene la ejecución un número de milisegundos determinado.
 \param ms Número de milisegundos a detener la ejecución.
*/
void Pantalla_Espera(int ms);

/**
 * \brief Actualiza la ventana mostrando el resultado de las funciones de dibujo que se hayan ejecutado hasta el momento.
*/
void Pantalla_Actualiza();

/**
  \brief Indica si una tecla en concreto está pulsada.
  \param scancode Código de la tecla de la que se desea conocer su estado. Los valores correspondientes a cada tecla se pueden encontrar en la documentación de SDL 2.0 (https://wiki.libsdl.org/SDL_Scancode)
  \return 1 si la tecla está pulsada.
  \return 0 si la tecla no está pulsada.
*/
int Pantalla_TeclaPulsada(SDL_Scancode scancode);

/**
  \brief Asigna el color de trazo que se usar al dibujar los bordes de las primitivas de dibujo.
  \param r Componente roja del color (Formato RGB) como un valor entero entre 0 a 255.
  \param g Componente verde del color (Formato RGB) como un valor entero entre 0 a 255.
  \param b Componente azul del color (Formato RGB) como un valor entero entre 0 a 255.
  \param a Componente de transparencia del color como un valor entero entre 0 y 255 siendo 0 totalmente transparente y 255 totalmente opaco.
*/
void Pantalla_ColorTrazo(int r, int g, int b, int a);

/**
  \brief Asigna el color de relleno que se usar al dibujar los bordes de las demás primitivas gráficas
  \param r Componente roja del color (Formato RGB) como un valor entero entre 0 a 255.
  \param g Componente verde del color (Formato RGB) como un valor entero entre 0 a 255.
  \param b Componente azul del color (Formato RGB) como un valor entero entre 0 a 255.
  \param a Componente de transparencia del color como un valor entero entre 0 y 255 siendo 0 totalmente transparente y 255 totalmente opaco.
*/
void Pantalla_ColorRelleno(int r, int g, int b, int a);

/**
  \brief Rellena la ventana con el color indicado borrando todo lo que haya en ese momento.
  \param r Componente roja del color (Formato RGB) como un valor entero entre 0 a 255.
  \param g Componente verde del color (Formato RGB) como un valor entero entre 0 a 255.
  \param b Componente azul del color (Formato RGB) como un valor entero entre 0 a 255.
  \param a Componente de transparencia del color como un valor entero entre 0 y 255 siendo 0 totalmente transparente y 255 totalmente opaco.
*/
void Pantalla_DibujaRellenoFondo(int r, int g, int b, int a);

/**
  \brief Dibuja un punto utilizando el color de trazo.
  \param x Coordenada horizontal del punto.
  \param y Coordenada vertical del punto.
*/
void Pantalla_DibujaPunto(double x, double y);

/**
  \brief Dibuja una línea utilizando el color de trazo.
  \param x1 Coordenada horizontal de uno de los extremos de la línea.
  \param y1 Coordenada vertical de uno de los extremos de la línea.
  \param x2 Coordenada horizontal del otro extremo de la línea.
  \param y2 Coordenada vertical del otro extremo de la línea.
*/
void Pantalla_DibujaLinea(double x1, double y1, double x2, double y2);

/**
  \brief Dibuja un triangulo utilizando el color de relleno y el color de trazo para el borde.
  \param x1 Coordenada horizontal de uno de los puntos del triángulo.
  \param y1 Coordenada vertical de uno de los puntos del triángulo.
  \param x2 Coordenada horizontal del segundo de los puntos del triángulo.
  \param y2 Coordenada vertical del segundo de los puntos del triángulo.
  \param x3 Coordenada horizontal del último punto del triángulo.
  \param y3 Coordenada vertical del último punto del triangulo.
*/
void Pantalla_DibujaTriangulo(double x1, double y1, double x2, double y2, double x3, double y3);

/**
  \brief Dibuja un rectángulo utilizando el color de relleno y el color de trazo para el borde.
  \param x Coordenada horizontal de la esquina superior izquierda del rectángulo.
  \param y Coordenada vertical de la esquina superior izquierda del rectángulo.
  \param w Anchura del rectángulo.
  \param h Altura del rectángulo.
*/
void Pantalla_DibujaRectangulo(double x, double y, double w, double h);

/**x
  \brief Dibuja un círculo utilizando el color de relleno y el color de trazo para el borde.
  \param x Coordenada horizontal del centro del círculo.
  \param y Coordenada vertical del centro del círculo.
  \param r Radio del círculo.
*/
void Pantalla_DibujaCirculo(double x, double y, double r);

/**
  \brief Dibuja una cadena de texto en la ventana gráfica. El texto mostrado usa una fuente de paso fijo de 8 puntos de ancho por 13 de alto.
  \param st Cadena de caracteres terminada en '\0' que será mostrada.
  \param x Coordenada horizontal de la esquina superior izquierda del rectángulo que enmarca el texto.
  \param y Coordenada vertical de la esquina superior izquierda del rectángulo que enmarca el texto.
*/
void Pantalla_DibujaTexto(char *st, double x, double y);

/**
  \brief Muestra un rectángulo en el que se puede introducir texto. La introducción termina al pulsar ENTER y se cancela pulsando ESC.
  \param x Coordenada horizontal de la esquina superior izquierda del recuadro de texto
  \param y Coordenada vertical de la esquina superior izquierda del recuadro de texto
  \param max Número máximo de caracteres que se debe permitir introducir
  \param titulo Mensaje que se mostrará sobre el recuadro de texto
  \return Puntero a la zona de memoria donde se ha reservado espacio para la cadena o NULL si se cancela la entrada.
*/
char * Pantalla_LeeTexto(int x, int y, int max, char * titulo);

/**
  \pre El fichero debe existir y estar en formato Windows BMP 24 bits sin compresión
  \brief Carga en memoria una imagen guardada en un fichero. La imagen debe estar en formato Windows BMP 24 bits sin compresión y se debe especificar el path completo incluido el nombre del fichero.
  \param fichero Nombre del fichero de donde leer la imagen.
  \param transparencia Parámetro que indica si la imagen debe considerarse transparente o no. Cualquier valor distinto de 0 indicará a la función que asuma
  que el color del pixel situado en las coordenadas (0,0) se debe considerar transparente en toda la imagen.
  \return La imagen cargada.
*/
Imagen Pantalla_ImagenLee(char * fichero, int transparencia);

/**
  \brief Dibuja una imagen previamente cargada en memoria con la función Pantalla_ImagenLee().
  \param imagen La imagen que se dibuja.
  \param x Coordenada horizontal de la esquina superior izquierda del rectángulo que contiene la imagen.
  \param y Coordenada vertical de la esquina superior izquierda del rectángulo que contiene la imagen.
  \param w Anchura de la imagen a dibujar (si no coincide con el tamaño original se hace un reescalado).
  \param h Altura de la imagen a dibujar (si no coincide con el tamaño original se hace un reescalado).
*/
void Pantalla_DibujaImagen(Imagen imagen, double x, double y, double w, double h);

/**
  \brief Dibuja una imagen en unas coordedenadas rotandola o volteandola a elección.
  \author Alejandro Martínez Castillo (Curso 2018-19)
  \param imagen La imagen que se quiere dibujar.
  \param x Coordenada horizontal de la esquina superior izquierda del rectángulo que contiene la imagen.
  \param y Coordenada vertical de la esquina superior izquierda del rectángulo que contiene la imagen.
  \param w Anchura de la imagen a dibujar (si no coincide con el tamaño original se hace un reescalado).
  \param h Altura de la imagen a dibujar (si no coincide con el tamaño original se hace un reescalado).
  \param angulo Angulo a rotar la imagen en el sentido de las agujas del reloj expresado en grados.
  \param volteo Parámetro para idicar el tipo de trasformación: SDL_FLIP_NONE si no se hace nada, SDL_FLIP_HORIZONTAL si se voltea horizontalmente, SDL_FLIP_VERTICAL si se voltea verticalmente.
*/
void Pantalla_DibujaImagenTransformada(Imagen imagen, double x, double y, double w, double h, double angulo, SDL_RendererFlip volteo);

/**
 * \brief Recupera la anchura de una imagen.
 * \param imagen La imagen de la que se desea conocer su anchura.
 * \return La anchura de la imagen.
 */
double Pantalla_ImagenAnchura(Imagen imagen);

/**
 * \brief Recupera la altura de una imagen.
 * \param imagen La imagen de la que se desea conocer su altura.
 * \return La altura de la imagen.
 */
double Pantalla_ImagenAltura(Imagen imagen);

/**
 * \brief Libera la memoria reservada para la imagen.
 * \param imagen La imagen que se libera.
 */
void Pantalla_ImagenLibera(Imagen imagen);

/**
  \brief Indica si alguno de los botones del ratón está pulsado.
  \param boton El botón del que se desea conocer su estado. Los valores corresponden a una de las tres constantes predefinidas por SDL: SDL_BUTTON_LEFT, SDL_BUTTON_MIDDLE o SDL_BUTTON_RIGHT
  \return 1 si el botón está pulsado.
  \return 0 si el botón no está pulsado.
 */
int Pantalla_RatonBotonPulsado(int boton);

/**
  \brief Obtiene las coordenadas del ratón en el momento actual.
  \param x Dirección de la variable de tipo double donde se dejará el valor de la coordenada horizontal del ratón o NULL si no se desea obtener esa coordenada.
  \param y Dirección de la variable de tipo double donde se dejará el valor de la coordenada vertical del ratón o NULL si no se desea obtener esa coordenada.
*/
void Pantalla_RatonCoordenadas(double * x, double * y);

#endif

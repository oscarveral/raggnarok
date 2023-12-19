#include "..\..\headers\mecanicas\botones.h"

/* TIPOS PÚBLICOS. */

/* Estructura de un botón. */
struct BotonRep
{
    int x;
    int y;
    int ancho;
    int alto;
    char texto[BOTONES_TEXTO_MAX];
};

/* FUNCIONES PÚBLICAS. */

/* Función que crea un botón en memoria. */
BotonPtr crea_boton (int x, int y, int ancho, int alto, char texto[BOTONES_TEXTO_MAX])
{
    BotonPtr nuevoBoton = malloc (sizeof(struct BotonRep));

    nuevoBoton -> x = x;
    nuevoBoton -> y = y;
    nuevoBoton -> ancho = ancho;
    nuevoBoton -> alto = alto;

    /* Copio la cadena de argumento a la estructura. */
    strcpy( nuevoBoton-> texto, texto);

    return nuevoBoton;
};

/* Función que libera un botón de memoria. */
void libera_boton (BotonPtr boton)
{
    free (boton);
};

/* Función para dibujar un botón en pantalla. */
void dibuja_boton (BotonPtr boton, int r, int g, int b, int a)
{
    /* Dibujado del rectángulo. */
    Pantalla_ColorRelleno(255, 255,255,a);
    Pantalla_ColorTrazo(0,0,0,a);
    Pantalla_DibujaRectangulo(boton -> x, boton -> y, boton -> ancho, boton -> alto);

    Pantalla_ColorTrazo(r,g,b,a);
    Pantalla_DibujaTexto (boton -> texto, boton -> x + boton -> ancho/15 , boton -> y + boton -> alto/15);
}; 

/* Función que devuelve 1 si se pulsa sobre un botón. */
int pulsa_boton (BotonPtr boton, double ratonX, double ratonY)
{
    /* Variable de pulsación. */
    int pulsado = 0;

    /* Comprobación de pulsación. */
    if (Pantalla_RatonBotonPulsado (SDL_BUTTON_LEFT) && ratonX >= boton -> x && ratonX <= boton -> x + boton -> ancho && ratonY >= boton -> y && ratonY <= boton -> y + boton -> alto)
    {
        pulsado = 1;
    }

    return pulsado;
};

/* Función que cambia el texto del botón por el dado. */
void cambia_texto_boton (BotonPtr boton, char nuevoTexto[BOTONES_TEXTO_MAX])
{
    strcpy (boton -> texto, nuevoTexto);
};
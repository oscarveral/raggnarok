#include "..\..\headers\mecanicas\hitbox.h"

/* TIPOS PÚBLICOS. */

/* TDA Hitbox. Caja de colisiones genérica. */
struct HitboxRep
{
    float x;
    float y;
    int radio;
};

/* FUNCIONES PÚBLICAS. */

/* Función para la inicialización de un dato tipo hitbox y su alojamiento en memoria. */
HitboxPtr crea_hitbox (float x, float y, int radio)
{
    HitboxPtr auxPtr = malloc(sizeof(struct HitboxRep));

    auxPtr -> x = x;
    auxPtr -> y = y;
    auxPtr -> radio = radio;

    return auxPtr;
};

/* Función para liberar de memoria un dato tipo hitbox. */
void libera_hitbox (HitboxPtr hitbox)
{
    free (hitbox);
};

/* Función para obtener la posición x de un dato tipo hitbox. */
float get_x_hitbox (HitboxPtr hitbox)
{
    return hitbox -> x;
};

/* Función para obtener la posición y de un dato tipo hitbox. */
float get_y_hitbox (HitboxPtr hitbox)
{
    return hitbox -> y;
};

/* Función para obtener el radio de un dato tipo hitbox. */
int get_radio_hitbox (HitboxPtr hitbox)
{
    return hitbox -> radio;
};

/* Función para modificar la posición x de un dato tipo hitbox. */
void modify_x_hitbox (HitboxPtr hitbox, float x)
{
    hitbox -> x = x;
};

/* Función para modificar la posición y de un dato tipo hitbox. */
void modify_y_hitbox (HitboxPtr hitbox, float y)
{
    hitbox -> y = y;
};

/* Función para modificar el radio de un dato tipo hitbox. */
void modify_radio_hitbox (HitboxPtr hitbox, int radio)
{
    hitbox -> radio = radio;
};

/* Función que determina si dos datos tipo hitbox se encuentran en colisión. */
int colision_hibox_hitbox (HitboxPtr hitbox1, HitboxPtr hitbox2)
{
    /* Cálculo de la distancia entre los dos centros de la hitbox. */
    double distancia = sqrt(pow(hitbox1 -> x - hitbox2 ->x,2) + pow(hitbox1 -> y - hitbox2 -> y, 2));

    /* Para ver si colisionan necesitamos calcular si la distancia entre sus centros es menor que la suma de sus radios. */
    return (distancia < hitbox1 -> radio + hitbox2 -> radio);
}

/* Función para determinar si un dato tipo hitbox se encuentra en colisión con un limite superior dado. */
int colision_hitbox_limiteSup (HitboxPtr hitbox, int limiteSup)
{
    return (hitbox -> y - hitbox -> radio <= limiteSup);
};

/* Función para determinar si un dato tipo hitbox se encuentra en colisión con un límite inferior dado. */
int colision_hitbox_limiteInf (HitboxPtr hitbox, int limiteInf)
{
    return (hitbox -> y + hitbox -> radio >= limiteInf);
};

/* Función para determinar si un dato tipo hitbox se encuentra en colisión con un límite izquierdo dado. */
int colision_hitbox_limiteIzq (HitboxPtr hitbox, int limiteIzq)
{
    return (hitbox -> x - hitbox -> radio <= limiteIzq);
};

/* Función para determinar si un dato tipo hitbox se encuentra en colisión con un límite derecho dado. */
int colision_hitbox_limiteDer (HitboxPtr hitbox, int limiteDer)
{
    return (hitbox -> x + hitbox -> radio >= limiteDer);
};

/* Función que obtiene el ángulo relativo de un punto dado respecto a un dato tipo hitbox. */
float angulo_hitbox_punto (HitboxPtr hitbox, float x, float y)
{
    /* Primero calculo la posición relativa entre el centro de la hitbox y el punto dado.*/
    float newx = hitbox -> x - x;
    float newy = hitbox -> y - y;
    /* Devuelvo el ángulo calculado en radianes. */
    return atan2(newy, newx) - M_PI_2;
}

/* Función que dado el módulo de un vector y su ángulo lo descompone en sus componentes fundamentales. */
void descompon_vector (double modulo, double angulo, double * componenteX, double * componenteY)
{
    /* Descomposición de componentes. */
    *componenteX = modulo * cos(angulo);
    *componenteY = modulo * sin(angulo);
};
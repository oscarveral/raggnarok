#include "..\..\headers\elementos\jugador.h"

/* TIPOS PÚBLICOS. */

/* Tipo de dato jugador. */
struct JugadorRep
{
    HitboxPtr hitbox;

    int estadoMovimiento;
    float contadorMovimiento;

    float velocidadMovimiento;
    double anguloJugador;
    int enfriamientoInteraccion;

    int vidas;
    int invencible;
    float contadorMuerte;
};

/* FUNCIONES PÚBLICAS. */

/* Función para crear un dato tipo jugador en memoria. */
JugadorPtr crea_jugador (float x, float y, int radio, float velocidad, int vidas)
{
    /* Reserva de memoria para el dato jugador. */
    JugadorPtr ptrAux = malloc (sizeof(struct JugadorRep));

    /* Comprobación de error en las coordenadas dadas. */
    if (x < 0 || y < 0 || radio < 0 || velocidad < 0) 
    {
        printf ("%s\nError en la llamada con parametros %d, %d, %d, %d.\nPulsa cualquier tecla para abortar.", ERROR_JUGADOR_001, x, y, radio, velocidad);
        scanf("%d");
        return NULL;
    };

    /* Creo la hitbox que tendrá el jugador. */
    ptrAux -> hitbox = crea_hitbox (x, y, radio);

    /* Establezco el estado de movimiento por defecto a 0 (equivale a que está quieto) y el parámetro de contador de movimiento a 0 también */
    ptrAux -> estadoMovimiento = 0;
    ptrAux -> contadorMovimiento = 0;

    /* Establezco el ángulo a 0 y el enfriamiento de interacción a 0 también. */
    ptrAux -> anguloJugador = 0;
    ptrAux -> enfriamientoInteraccion = 0;

    /* Establezco el parámetro de velocidad de movimiento. */
    ptrAux -> velocidadMovimiento = velocidad;

    /* Establezco las vidas que tiene y el contador de muerte e invencible a 0.*/
    ptrAux -> vidas = vidas;
    ptrAux -> invencible = 0;
    ptrAux -> contadorMuerte = 0;

    /* Devuelve el puntero al dato tipo jugador en memoria. */
    return ptrAux;
};

/* Función para liberar de memoria un dato tipo jugador. */
int libera_jugador (JugadorPtr jugador)
{
    /* Comprobación de error. */
    if (jugador == NULL)
    {
        printf("%s\nPulsa cualquier tecla para continuar. ", ERROR_JUGADOR_002);
        scanf("%d");
        return 1;
    };

    /* Libero la hitbox del jugador. */
    libera_hitbox (jugador -> hitbox);

    /* Libero el dato tipo jugador completo de memoria. */
    free (jugador);

    return 0;
};

/* Función que devuelve el puntero al dato tipo hitbox que representa la caja de colisiones del jugador. */
HitboxPtr get_hitbox_jugador (JugadorPtr jugador)
{
    return jugador -> hitbox;
};

/* Función que devuelve el valor del campo estadoMovimiento de un dato tipo jugador. */
int get_estadoMovimiento_jugador (JugadorPtr jugador)
{
    return jugador -> estadoMovimiento;
};

/* Función para modificar el campo estadoMovimiento de un dato tipo jugador. */
void modify_estadoMovimiento_jugador (JugadorPtr jugador, int nuevoValor)
{
    jugador -> estadoMovimiento = nuevoValor;
};

/* Función que devuelve el valor del campo contadorMovimiento. */
float get_contadorMovimiento_jugador (JugadorPtr jugador)
{
    return jugador -> contadorMovimiento;
};

/* Función para modificar el valor del campo paramteroImagen. */
void modify_contadorMovimiento_jugador (JugadorPtr jugador, float nuevoValor)
{
    jugador -> contadorMovimiento = nuevoValor;
};

/* Función para mover a un dato tipo jugador hacia arriba por pantalla. */
void mueve_arriba_jugador (JugadorPtr jugador)
{
    modify_y_hitbox (jugador -> hitbox, get_y_hitbox (jugador -> hitbox) - jugador -> velocidadMovimiento);
    jugador -> estadoMovimiento = 1;
};

/* Función para mover a un dato tipo jugador hacia abajo por pantalla. */
void mueve_abajo_jugador (JugadorPtr jugador)
{
    modify_y_hitbox (jugador -> hitbox, get_y_hitbox (jugador -> hitbox) + jugador -> velocidadMovimiento);
    jugador -> estadoMovimiento = 1;
};

/* Función para mover a un dato tipo jugador hacia la derecha por pantalla. */
void mueve_derecha_jugador (JugadorPtr jugador)
{
    modify_x_hitbox (jugador -> hitbox, get_x_hitbox (jugador -> hitbox) + jugador -> velocidadMovimiento);
    jugador -> estadoMovimiento = 1;
};

/* Función para mover a un dato tipo jugador hacia la izquierda por pantalla. */
void mueve_izquierda_jugador (JugadorPtr jugador)
{
    modify_x_hitbox (jugador -> hitbox, get_x_hitbox (jugador -> hitbox) - jugador -> velocidadMovimiento);
    jugador -> estadoMovimiento = 1;
};

/* Función que describe una animación de movimiento genérico de un jugador a través de la variación de su contador de movimiento. */
void animacion_movimiento_jugador (JugadorPtr jugador, float incrementoMovimiento, float longitudSegmento, float multiplicadorSegmentos)
{
    /* Si el jugador está quieto. */
    if (jugador -> estadoMovimiento == 0)
    {
        /* El contador de movimiento se queda en 0. */
        jugador -> contadorMovimiento = 0;
    }
    /* Si el jugador está en movimiento. */
    else
    {
        /* Realizo 1 incremento cada llamada hasta que sepa que se va a alcanzar en la siguiente operación el valor máximo permitido para el contador.*/
        if (jugador -> contadorMovimiento + incrementoMovimiento < longitudSegmento * multiplicadorSegmentos)
        {
            /* Incremento del contador. */
            jugador -> contadorMovimiento = jugador -> contadorMovimiento + incrementoMovimiento;
        }
        /* Cuando pase lo anterior restablezco el contador al valor del tamaño de segmento dado mas un incremento. Después volverá a contar a partir de ahí hasta alcanzar el máximo de nuevo. Ad infinitum*/
        else jugador -> contadorMovimiento = longitudSegmento + incrementoMovimiento;

    };
};

/* Función para obtener el parámetro del ángulo del jugador. */
double get_angulo_jugador (JugadorPtr jugador)
{
    return jugador -> anguloJugador;
};

/* Función para modificar el valor del parámetro anguloJugador de un dato tipo jugador. */
void modify_angulo_jugador (JugadorPtr jugador, double nuevoAngulo)
{
    jugador -> anguloJugador = nuevoAngulo;
};

/* Función que recupera el valor del campo enfriamientoInteracción de un dato tipo jugador. */
int get_enfriamientoInteraccion_jugador (JugadorPtr jugador)
{
    return jugador -> enfriamientoInteraccion;
};

/* Función que modifica el valor del campo enfriamientoInteracción de un dato tipo jugador. */
void modify_enfriamientoInteraccion_jugador (JugadorPtr jugador, int nuevoEnfriamiento)
{
    jugador -> enfriamientoInteraccion = nuevoEnfriamiento;
}

/* Función que dibuja al jugador en pantalla dado un array de imágenes según el valor de su contador de movimiento. */
int dibuja_jugador (JugadorPtr jugador, Imagen * punteroArray, int cantidadImagenesArray, int desplazamientoSpritesMovimiento, int desplazamientosSpritesMuerte)
{
    /* Indice de la imagen del array a utilizar. */
    int indice = 0;

    /* Comprobamos si el jugador ha muerto o no para saber como calcular el índice. */
    if (jugador -> vidas > 0)
    {
        /* Establezco el índice del array a partir del cual se seleccionará la imagen a dibujar según el contador de movimiento. */
        indice = ceil (jugador -> contadorMovimiento) + desplazamientoSpritesMovimiento;
    }
    /* Si el jugador ha muerto establezco el índice según el contador de muerte más un desplazamiento para localizar los sprites en el array. */
    else indice = floor(jugador -> contadorMuerte) + desplazamientosSpritesMuerte;

    /* Si el índice es mayor a la cantidad de imágenes en el array menos 1 se devuelve un error junto a la devolución de 1 por parte de la función. */
    if (indice > cantidadImagenesArray - 1)
    {
        printf ("%s\nPulse cualquier tecla para abortar.\n", ERROR_JUGADOR_003);
        scanf ("%d");
        return 1;
    };

    /* Dibujado del jugador. */
    Pantalla_DibujaImagenTransformada(punteroArray[indice], get_x_hitbox(get_hitbox_jugador(jugador)) - get_radio_hitbox(get_hitbox_jugador(jugador)), get_y_hitbox(get_hitbox_jugador(jugador)) - get_radio_hitbox(get_hitbox_jugador(jugador)), 2 * get_radio_hitbox(get_hitbox_jugador(jugador)),  2 * get_radio_hitbox(get_hitbox_jugador(jugador)), get_angulo_jugador(jugador) * (180/M_PI), SDL_FLIP_NONE);

    /* Si todo sale bien se devuelve 0. */
    return 0;
}

/* Función que hace que el jugador dispare una bala usando el módulo de balas y actualizando su contador de enfriamiento. */
void dispara_jugador (JugadorPtr jugador, NodoBalaPtr ptrCabecera, int radioBalas, int velocidadBalas, int enfriamientoDisparo)
{
    /* Disparo si no hay enfriamiento. */
    if (jugador -> enfriamientoInteraccion <= 0)
    {
        dispara_bala_rafaga (ptrCabecera, get_x_hitbox(jugador -> hitbox), get_y_hitbox(jugador -> hitbox), radioBalas, velocidadBalas, jugador -> anguloJugador);
        jugador -> enfriamientoInteraccion = enfriamientoDisparo;
    }
    /* Actualizo el enfriamiento. (Lo hago solo si es positivo para evitar desbordamiento de memoria). */
    if (jugador -> enfriamientoInteraccion > 0)
    {
        jugador -> enfriamientoInteraccion = jugador -> enfriamientoInteraccion - 1;
    }
};

/* Función que devuelve la cantidad de vidas que tiene un dato tipo jugador. */
int get_jugador_vidas (JugadorPtr jugador)
{
    return jugador -> vidas;
};

/* Función que modifica la cantidad de vidas de un dato tipo jugador. */
void modify_jugador_vidas (JugadorPtr jugador, int nuevaVidas)
{
    jugador -> vidas = nuevaVidas;
};  

/* Función que devuelve verdader si el jugador ha muerto, es decir, si tiene 0 vidas. */
int jugador_muerto (JugadorPtr jugador)
{
    return (jugador -> vidas == 0);
}

/* Función que calcula si una ráfaga de balas colisiona con el jugador. Enmascara una llamada a la función de rafaga colisiona con hitbox, en este caso la del jugador. */
int jugador_colisiona_rafaga (JugadorPtr jugador, NodoBalaPtr ptrCabecera)
{
    return colision_rafaga_hitbox (ptrCabecera, jugador -> hitbox);
};

/* Función que describe una animación de muerte a través del contador de movimiento del jugador. Devolverá 1 cuando finalize la animación. */
int animacion_muerte_jugador (JugadorPtr jugador, float incrementoMuerte, float longitudSegmento, float multiplicadorSegmentos)
{  
    /* Si acaba la animación devuelve 1. */
    if (jugador -> contadorMuerte >= longitudSegmento * multiplicadorSegmentos - incrementoMuerte) return 1;
    /* Incremento de animación. */
    else 
    {
        jugador -> contadorMuerte = jugador -> contadorMuerte + incrementoMuerte;
        /* Devuelve 0 por defecto. */
        return 0;
    };
};

/* Función que devuelve el campo velocidad de un jugador dado. */
float get_velocidad_jugador (JugadorPtr jugador)
{
    return jugador -> velocidadMovimiento;
};

/* Función que modifica la posición del jugador a las nuevas coordenadas dadas. */
void modify_pos_jugador (JugadorPtr jugador, float x, float y)
{
    modify_x_hitbox(jugador -> hitbox, x);
    modify_y_hitbox(jugador -> hitbox, y);
};

/* Función que modifica el campo invencible de un dato tipo jugador. */
void modify_invencible_jugador (JugadorPtr jugador, int nuevoValor)
{
    jugador -> invencible = nuevoValor;
};

/* Función que recupera el valor del campo invencible de un dato tipo jugador. */
int get_invencible_jugador (JugadorPtr jugador)
{
    return jugador -> invencible;
};
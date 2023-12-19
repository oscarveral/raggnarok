#include "..\..\headers\elementos\enemigos.h"

/* TIPOS PÚBLICOS. */

/* Estructura del ejercito de enemigos. */
struct EjercitoRep 
{
    JugadorPtr * arrayEnemigos;
    int n_elementos;
    int capacidad_array;
};


/* FUNCIONES PÚBLICAS. */

/* Función para crear un ejercito en memoria dado su tamaño máximo. */
EjercitoPtr crea_ejercito (int max)
{
    /* Reserva de memoria para la estructura. */
    EjercitoPtr nuevo = malloc (sizeof (struct EjercitoRep));
    
    /* Reserva de memoria para el array. */
    nuevo -> arrayEnemigos = malloc (sizeof(JugadorPtr) * max);

    nuevo -> n_elementos = 0;
    nuevo -> capacidad_array = max;

    /* Por seguridad pondré todos los punteros del array de enemigos a NULL. */
    for (int i = 0; i < max; i = i + 1)
    {
        nuevo -> arrayEnemigos[i] = NULL;
    };

    return nuevo;
};

/* Función que libera un ejercito de memoria. */
void libera_ejercito (EjercitoPtr ejercito)
{
    /* Libero todos los enemigos del array. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i +1)
    {
        /* Compruebo si el enemigo a liberar no ha sido liberado antes. */
        if(ejercito -> arrayEnemigos[i] != NULL) libera_jugador(ejercito -> arrayEnemigos[i]);
    };

    /* Libero el array primero y después el ejercito completo. */
    free(ejercito -> arrayEnemigos);
    free(ejercito);
};

/* Función que llena completamente un ejercito con parámetros aleatorios. */
void recluta_ejercito (EjercitoPtr ejercito, float xMax, float xMin, float yMax, float yMin, int radioEnemigos, float velocidadEnemigos, int vidasEnemigos)
{
    /* Recorrido de llenado del array de enemigos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i +1)
    {
        ejercito -> arrayEnemigos[i] = crea_jugador (rand() % (int)((xMax-xMin+1)) + xMin, rand() % (int)((yMax-yMin+1)) + yMin, radioEnemigos, velocidadEnemigos, vidasEnemigos);
    };

    /* Establezco el contador de enemigos al máximo de la capacidad. */
    ejercito -> n_elementos = ejercito -> capacidad_array;
};

/* Función que orienta todos los elementos del ejercito al punto dado. */
void orienta_ejercito (EjercitoPtr ejercito, float x, float y)
{
    /* Recorrido del array excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i +1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL)
        {
            /* Asigno el nuevo ángulo en radianes a cada elemento del array de enemigos. */
            modify_angulo_jugador(ejercito -> arrayEnemigos[i], angulo_hitbox_punto(get_hitbox_jugador(ejercito -> arrayEnemigos[i]), x, y));
        };
    };
};

/* Función para dibujar los enemigos en pantalla. */
int dibuja_ejercito (EjercitoPtr ejercito, Imagen * arraySprites, int cantidadImagenesArray, int desplazamientoSpritesMovimiento, int desplazamientoSpritesMuerte)
{
    /* Variable de error. */
    int error = 0;

    /* Recorro el array excluyendo los elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i +1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL)
        {
            error = dibuja_jugador(ejercito -> arrayEnemigos[i], arraySprites,cantidadImagenesArray, desplazamientoSpritesMovimiento, desplazamientoSpritesMuerte);
        };
    };

    return error;
};

/* Función para actualizar el contador de movimiento de los enemigos del array. */
void animacion_ejercito (EjercitoPtr ejercito, float incrementoMovimiento, float longitudSegmento, float multiplicadorSegmentos)
{
    /* Recorrido del array excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i + 1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL)
        {
            animacion_movimiento_jugador(ejercito -> arrayEnemigos[i], incrementoMovimiento, longitudSegmento, multiplicadorSegmentos);
        };
    };
};

/* Función que hace que los enemigos disparen al jugador. */
void dispara_ejercito (EjercitoPtr ejercito, NodoBalaPtr ptrCabecera, int radioBalas, int velocidadBalas, int enfriamientoDisparo)
{
    /* Recorrido del array excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i= i +1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL)
        {
            /* Aleatorio para que se desincronicen los disparos de todos los enemigos. */
            int disparo_aleatorio = rand() % 6;

            /* Disparo si disparo_aleatorio = 0. */
            if (disparo_aleatorio == 0) dispara_jugador(ejercito -> arrayEnemigos[i], ptrCabecera, radioBalas, velocidadBalas, enfriamientoDisparo);
        };
    };
};

/* Función que devuelve 1 si todos los enemigos de un ejercito han muerto o no existen. */
int ejercito_vacio (EjercitoPtr ejercito)
{
    return (ejercito -> n_elementos == 0);
};

/* Función que calcula la colisión de todos los enemigos del ejercito con una ráfaga de balas. */
void ejercito_colisiona_rafaga (EjercitoPtr ejercito, NodoBalaPtr ptrCabecera)
{
    /* Recorrido del array excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i + 1)
    {
        /* Compruebo que las vidas sean positivas para evitar errores. */
        if (ejercito -> arrayEnemigos[i] != NULL && get_jugador_vidas(ejercito -> arrayEnemigos[i]))
        {
            modify_jugador_vidas (ejercito -> arrayEnemigos[i], get_jugador_vidas(ejercito -> arrayEnemigos[i]) - jugador_colisiona_rafaga(ejercito -> arrayEnemigos[i], ptrCabecera));
        };
    }
};

/* Función que actualiza el ejercito según los enemigos que mueran y aplica la animación de muerte a aquellos enemigos que mueran. Cuando se completa estos se liberan de memoria y su valor en el array pasa a ser nulo. */
void muere_ejercito (EjercitoPtr ejercito, float incrementoMuerte, int longitudSegmento, int multiplicadorSegmentos, int * punteroPuntuacion)
{
    /* Recorrido del ejercito excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i + 1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL && jugador_muerto(ejercito -> arrayEnemigos[i]))
        {
            /* Ejecuto la aniación de muerte del enemigo y cuando se complete lo elimino de memoria. */
            if (animacion_muerte_jugador(ejercito -> arrayEnemigos[i], incrementoMuerte, longitudSegmento, multiplicadorSegmentos))
            {
                /* Incremento la la puntuación de la variable dada. */
                *punteroPuntuacion = *punteroPuntuacion + 1;

                libera_jugador(ejercito -> arrayEnemigos[i]);
                ejercito -> arrayEnemigos[i] = NULL;

                /* Decremento el contador de enemigos del ejercito. */
                ejercito -> n_elementos = ejercito -> n_elementos - 1;
            };
        };
    };
};

/* Función que obtiene la cantidad de enemigos vivos en un ejercito. */
int enemigos_ejercito (EjercitoPtr ejercito)
{
    return ejercito -> n_elementos;
}

/* Función que devuelve el máximo de capacidad del array de enemigos. */
int maximos_enemigos_ejercito (EjercitoPtr ejercito)
{
    return ejercito -> capacidad_array;
};

/* Fución que mueve un los enemigos del ejercito. */
void mueve_ejercito (EjercitoPtr ejercito, int bordeSup, int bordeInf, int bordeDer, int bordeIzq, int modoMovimiento)
{
    /* Recorrido del ejercito excluyendo elementos nulos. */
    for (int i = 0; i < ejercito -> capacidad_array; i = i + 1)
    {
        if (ejercito -> arrayEnemigos[i] != NULL)
        {
            double velocidadXEnemigo = 0;
            double velocidadYEnemigo = 0;

            /* Obtengo las componentes de la velocidad de los enemigos. */
            descompon_vector (get_velocidad_jugador(ejercito -> arrayEnemigos[i]), get_angulo_jugador(ejercito -> arrayEnemigos[i]), &velocidadXEnemigo, &velocidadYEnemigo);

            /* Según el signo de esas componentes muevo cada enemigo en una dirección determinada. */
            if (velocidadXEnemigo > 0 && !colision_hitbox_limiteDer(get_hitbox_jugador(ejercito ->arrayEnemigos[i]), bordeDer))
            {
                mueve_derecha_jugador(ejercito -> arrayEnemigos[i]);
                if (modoMovimiento == 0) modify_pos_jugador(ejercito ->arrayEnemigos[i], get_x_hitbox(get_hitbox_jugador(ejercito->arrayEnemigos[i])) - velocidadXEnemigo, get_y_hitbox(get_hitbox_jugador(ejercito-> arrayEnemigos[i])));
            }
            else if (velocidadXEnemigo < 0 && !colision_hitbox_limiteIzq(get_hitbox_jugador(ejercito -> arrayEnemigos[i]), bordeIzq))
            {
                mueve_izquierda_jugador(ejercito -> arrayEnemigos[i]);
                if (modoMovimiento == 0) modify_pos_jugador(ejercito ->arrayEnemigos[i], get_x_hitbox(get_hitbox_jugador(ejercito->arrayEnemigos[i])) - velocidadXEnemigo, get_y_hitbox(get_hitbox_jugador(ejercito-> arrayEnemigos[i])));

            };
            if (velocidadYEnemigo > 0 && !colision_hitbox_limiteInf(get_hitbox_jugador(ejercito ->arrayEnemigos[i]), bordeInf))
            {
                mueve_abajo_jugador (ejercito -> arrayEnemigos[i]);
                if (modoMovimiento == 0) modify_pos_jugador(ejercito ->arrayEnemigos[i], get_x_hitbox(get_hitbox_jugador(ejercito->arrayEnemigos[i])), get_y_hitbox(get_hitbox_jugador(ejercito-> arrayEnemigos[i])) - velocidadYEnemigo);
            }
            else if (velocidadYEnemigo < 0 && !colision_hitbox_limiteSup(get_hitbox_jugador(ejercito ->arrayEnemigos[i]), bordeSup))
            {
                mueve_arriba_jugador (ejercito -> arrayEnemigos[i]);
                if (modoMovimiento == 0) modify_pos_jugador(ejercito ->arrayEnemigos[i], get_x_hitbox(get_hitbox_jugador(ejercito->arrayEnemigos[i])), get_y_hitbox(get_hitbox_jugador(ejercito-> arrayEnemigos[i])) - velocidadYEnemigo);
            };
        };
    };
};
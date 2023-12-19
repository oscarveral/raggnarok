#include "..\..\headers\mecanicas\balas.h"

/* TIPOS PÚBLICOS. */

/* Estructura del dato NodoBala. Representa una bala cualquiera con todas sus propiedades. */
struct NodoBalaRep
{
    HitboxPtr hitboxBala;
    double velocidadX;
    double velocidadY;

    NodoBalaPtr sig;
};

/* FUNCIONES PÚBLICAS. */

/* Función que crea una ráfaga de balas lista para comenzar a operar sobre ella. */
NodoBalaPtr crea_rafaga_balas ()
{
    /* Reservo memoria para mi nodo de ptrCabecera. */
    NodoBalaPtr ptrptrCabecera = malloc (sizeof (struct NodoBalaRep));
    
    /* Inicializo los datos de la ptrCabecera nulos. */
    ptrptrCabecera -> hitboxBala = NULL;
    ptrptrCabecera -> velocidadX = 0.0;
    ptrptrCabecera -> velocidadY = 0.0;

    ptrptrCabecera -> sig = NULL;

    return ptrptrCabecera;
}

/* Función que inserta una nueva bala al principio de una lista de balas ya creada. */
void dispara_bala_rafaga (NodoBalaPtr ptrptrCabecera, float x, float y, int radio, double velocidad, double anguloSalida)
{
    if (ptrptrCabecera ==  NULL || x < 0 || y < 0 || radio < 0 || velocidad < 0)
    {
        printf("%s%d. Introduce cualquier input para continuar.", WARNING_BALAS_001, ptrptrCabecera);
        scanf("%d");
    }

    /* Reservo memoria para la nueva bala. */
    NodoBalaPtr nuevaBala = malloc (sizeof (struct NodoBalaRep));
    
    /* Reservo memoria para la hitbox de la bala. */
    nuevaBala -> hitboxBala = crea_hitbox (x,  y, radio);

    /* Transformación para que salgan en la dirección correcta, teniendo en cuenta que el eje Y crece hacia abajo. */
    double anguloSalida2 = anguloSalida - M_PI_2;

    /* Descomposición de la velocidad según el ángulo de salida. */
    nuevaBala -> velocidadX = velocidad*(cos(anguloSalida2));
    nuevaBala -> velocidadY = velocidad*(sin(anguloSalida2));

    /* Inserción de la bala en la lista reconectando los campos sig de la ptrCabecera y de la nueva bala. */
    nuevaBala -> sig = ptrptrCabecera -> sig;
    ptrptrCabecera -> sig = nuevaBala;
};

/* Función que libera una lista completa de balas de la memoria. */
int libera_rafaga_balas (NodoBalaPtr ptrptrCabecera)
{
    /* Control de errores. */
    if (ptrptrCabecera == NULL)
    {
        printf ("%sIntroduzca cualquier input para abortar.", ERROR_BALAS_001);
        scanf("%d");
        return 1;
    };

    /* Puntero que usaremos para saber la dirección del nodo que queremos borrar en cada momento. */
    NodoBalaPtr nodoActual = NULL;

    while (ptrptrCabecera -> sig != NULL)
    {
        /* Me guardo el nodo a borrar y reconecto la lista qutandolo. */
        nodoActual = ptrptrCabecera -> sig;
        ptrptrCabecera -> sig = nodoActual -> sig;

        /* Liberación del nodo. */
        libera_hitbox (nodoActual -> hitboxBala);
        free (nodoActual);
    }

    /* Liberación de la ptrCabecera. */
    free (ptrptrCabecera);
    return 0;
};

/* Función que devuelve el puntero al dato tipo hitbox de un nodoBalaPtr dado. */
HitboxPtr get_hitbox_nodobala (NodoBalaPtr nodoDado)
{
    return nodoDado -> hitboxBala;
};

/* Función que devuelve el puntero al campo sig de un nodoBala dado. */
NodoBalaPtr get_sig_bala (NodoBalaPtr nodoDado)
{
    return nodoDado -> sig;
};

/* Función que mueve todas las balas en función de los valores de su campo velocidad. */
void mueve_rafaga_balas (NodoBalaPtr ptrptrCabecera)
{
    /* Nodo auxiliar para recorrer la lista de balas. */
    NodoBalaPtr ptrAux = ptrptrCabecera;

    /* Recorrido de la lista. */
    while (ptrAux -> sig != NULL)
    {
        /* Avanza. */
        ptrAux = ptrAux -> sig;

        /* Actualiza posición. */
        modify_x_hitbox(ptrAux -> hitboxBala, get_x_hitbox(ptrAux -> hitboxBala) + ptrAux -> velocidadX);
        modify_y_hitbox(ptrAux -> hitboxBala, get_y_hitbox(ptrAux -> hitboxBala) + ptrAux -> velocidadY);
    };
};

/* Función que libera las balas que se encuentran fuera de los límites dados. */
void rafaga_fuera_limites (NodoBalaPtr ptrptrCabecera, int limiteSup,int limiteInf, int limiteDer, int limiteIzq)
{
    /* Nodo auxiliar para recorrer la lista. */
    NodoBalaPtr nodoAux = ptrptrCabecera;
    /* Recorrido de la lista. */
    while (nodoAux -> sig != NULL)
    {
        /* Compruebo si la bala siguiente se encuentra fuera de los límites. */
        if (colision_hitbox_limiteDer (nodoAux -> sig -> hitboxBala, limiteDer + get_radio_hitbox(nodoAux -> sig -> hitboxBala)) || 
            colision_hitbox_limiteIzq (nodoAux -> sig -> hitboxBala, limiteIzq - get_radio_hitbox(nodoAux -> sig -> hitboxBala)) ||
            colision_hitbox_limiteSup (nodoAux -> sig -> hitboxBala, limiteSup - get_radio_hitbox(nodoAux -> sig -> hitboxBala)) ||
            colision_hitbox_limiteInf (nodoAux -> sig -> hitboxBala, limiteInf + get_radio_hitbox(nodoAux -> sig -> hitboxBala)) )
        {
            /* Si colisiona reconecto la lista sin esa bala y después la libero. */
            NodoBalaPtr nodoBorrar = nodoAux -> sig;
            /*Nos da igual que el siguente del siguiente sea nulo ya que no vamos a avanzar en la lista durante la misma iteración en la que se reconecta.  Si fuese nulo después no entraríamos de nuevo al bucle.*/
            nodoAux -> sig = nodoAux -> sig -> sig;

            libera_hitbox (nodoBorrar -> hitboxBala);
            free (nodoBorrar);
        }
        /* Si no colisiona avanzo en la lista. */
        else nodoAux = nodoAux -> sig;
    };
};

/* Función para dibujar una ráfaga de balas completa en pantalla. */
void dibuja_rafaga_balas (NodoBalaPtr ptrCabecera, Imagen spriteBala)
{
    NodoBalaPtr ptrAux = ptrCabecera;
    while (ptrAux -> sig != NULL)
    {
        ptrAux = ptrAux -> sig;
        int radio = get_radio_hitbox(ptrAux -> hitboxBala);
        Pantalla_DibujaImagen(spriteBala, get_x_hitbox(ptrAux -> hitboxBala) - radio, get_y_hitbox(ptrAux->hitboxBala) - radio, 2*radio, 2*radio);
    };
};

/* Función que determina si alguna bala de la ráfaga dada colisiona con la hitbox dada como parámetro. Aquellas que lo hagan serán liberadas. */
int colision_rafaga_hitbox (NodoBalaPtr ptrCabecera, HitboxPtr hitbox)
{
    NodoBalaPtr ptrAux = ptrCabecera;
    int colisiona = 0;
    while (ptrAux -> sig != NULL)
    {
        if (colision_hibox_hitbox(ptrAux -> sig -> hitboxBala, hitbox) == 1)
        {
            /* Liberación del nodo. Guardo el nodo que colisiona con la hitbox y reconecto la lista. Despúes no se avanza para evitar saltarnos el nodo siguiente al reconectado y para evitar el tratamiento de un puntero nulo en el caso de que estuviesemos borrando el último nodo de la lista. */
            NodoBalaPtr nodoABorrar = ptrAux -> sig;
            ptrAux -> sig = nodoABorrar -> sig;

            /* Establezco colisiona a 1 cuando se detecte colisión. */
            colisiona = 1;
        }
        /* Si no se colisiona si que avanzo en la lista a la siguiente bala. */
        else ptrAux = ptrAux -> sig;
    };
    return colisiona;
};
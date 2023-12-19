#include "..\headers\mecanicas\imagenes.h"
#include "..\headers\mecanicas\balas.h"
#include "..\headers\elementos\jugador.h"
#include "..\headers\elementos\enemigos.h"
#include "..\headers\mecanicas\botones.h"

/* Constantes generales para la pantalla. */
#define MARGEN_JUEGO 30
#define ANCHURA_PANTALLA 1920
#define ALTURA_PANTALLA 1080
#define ORIGEN_COORDENADAS 0
#define NOMBRE_VENTANA "Raggnarok"

/* Constantes rutas archivos. */
#define RUTA_FONDO_UI "images\\fondos\\fondo_ui.bmp"
#define RUTA_FONDO_AYUDA "images\\fondos\\fondo_ayuda.bmp"
#define RUTA_LOGO "images\\fondos\\logo.bmp"
#define RUTA_BALA_AMIGA "images\\proyectiles\\bala_amiga.bmp"
#define RUTA_BALA_ENEMIGA "images\\proyectiles\\bala_enemiga.bmp"
#define RUTA_FONDO_GENERICA "images\\fondos\\fondo_z.bmp"
#define RUTA_JUGADOR_GENERICA  "images\\jugador\\jugador_z.bmp"
#define RUTA_ENEMIGO_GENERICA "images\\enemigo\\enemigo_z.bmp"
#define CARACTER_PERMUTA_GENERICO 'z'
#define RUTA_RECORDS "records.txt"

/* Constantes para el cálculo de milisegundos de espera de la pantalla. */
#define MS_ESPERA_MAX 16
#define MS_ESPERA_MIN 2

/* Constantes de texto informativo. */
#define MSG_VIDAS_RESTANTES "Vidas restantes: "
#define MSG_ENEMIGOS_RESTANTES "Enemigos restantes: "
#define MSG_RONDAS_ACTUALES "Ronda: "
#define MSG_PUNTOS_ACTUALES "Puntos: "
#define MSG_FIN_PARTIDA_1 "Puntos obtenidos en esta partida: "
#define MSG_FIN_PARIDA_2 "Pulsa cualquier boton del raton para continuar."
#define MSG_VOLVER "Volver"
#define MSG_CERRAR "X"
#define MSG_JUGAR "Jugar"
#define MSG_AYUDA "Ayuda"
#define MSG_SALIR "Salir"
#define MSG_NUEVO_RECORD "NUEVO RECORD. ENHORABUENA!"
#define MSG_ERROR_LEER_ARCHIVO "El fichero al que desea acceder no existe o no está en la ruta especificada.\nIntroduce cualquier tecla para continuar.\n"

/* Definición de la función del menú del juego. */
int menu ()
{
    /* Carga de la imagen de fondo y logo. */
    Imagen fondoUI = Pantalla_ImagenLee (RUTA_FONDO_UI, 0);
    Imagen logo = Pantalla_ImagenLee(RUTA_LOGO, 1);

    /* Variables de posición de los botones. */
    int botonX = Pantalla_Anchura()/10;
    int botonY = Pantalla_Altura()/5;

    /* Variables de posición del ratón. */
    double ratonX = 0;
    double ratonY = 0;

    /* Creación de botones. */
    BotonPtr jugar = crea_boton(botonX, botonY, BOTON_ANCHO_BASE, BOTON_ALTO_BASE, MSG_JUGAR);
    BotonPtr ayuda = crea_boton(botonX, botonY + 2* BOTON_ALTO_BASE, BOTON_ANCHO_BASE, BOTON_ALTO_BASE, MSG_AYUDA);
    BotonPtr exit = crea_boton (botonX, botonY + 4* BOTON_ALTO_BASE, BOTON_ANCHO_BASE, BOTON_ALTO_BASE, MSG_SALIR);

    /* Variable fin de bucle. */
    int fin_bucle = 0;

    /* Bucle que romperemos cuando cerremos la ventana o seleccionemos una opción. */
    while (Pantalla_Activa() && fin_bucle == 0)
    {
        /* Dibujado del fondo y logo. */
        Pantalla_DibujaImagen(fondoUI, ORIGEN_COORDENADAS, ORIGEN_COORDENADAS, Pantalla_Anchura(), Pantalla_Altura());
        Pantalla_DibujaImagen(logo, Pantalla_Anchura() /5, Pantalla_Altura()/5, 40*MARGEN_JUEGO, 20*MARGEN_JUEGO);

        /* Dibujado de los botones. */
        dibuja_boton(jugar, 255, 0, 0, 255);
        dibuja_boton(ayuda, 255, 0, 0, 255);
        dibuja_boton(exit, 255, 0, 0, 255);

        /* Obtención de las coordenadas del ratón. */
        Pantalla_RatonCoordenadas(&ratonX, &ratonY);
        
        if (pulsa_boton (jugar, ratonX, ratonY))
        {
            fin_bucle = 1;
        };

        if (pulsa_boton(ayuda, ratonX, ratonY))
        {
            fin_bucle = 2;
        };

        if (pulsa_boton(exit, ratonX, ratonY))
        {
            fin_bucle = 3;
        };

        /* Actualización de pantalla. */
        Pantalla_Actualiza();
        Pantalla_Espera(MS_ESPERA_MAX);
    };

    libera_boton(jugar);
    libera_boton(ayuda);
    libera_boton(exit);

    Pantalla_ImagenLibera (fondoUI);

    return fin_bucle;
};

/* Definición de la función de la ayuda del juego. */
int ayuda ()
{
     /* Carga de la imagen de fondo. */
    Imagen fondoUI = Pantalla_ImagenLee (RUTA_FONDO_AYUDA, 0);

    /* Variables de posición del ratón. */
    double ratonX = 0;
    double ratonY = 0;

    /* Botón y variable de salida y vuelta. */
    BotonPtr exit = crea_boton(Pantalla_Anchura() - 2* MARGEN_JUEGO, MARGEN_JUEGO, MARGEN_JUEGO, MARGEN_JUEGO, MSG_CERRAR);
    BotonPtr volver = crea_boton(Pantalla_Anchura() - 6* MARGEN_JUEGO, MARGEN_JUEGO, 3*MARGEN_JUEGO, MARGEN_JUEGO, MSG_VOLVER);

    /* Variable de fin de bucle. */
    int salida = -1;

    /* Bucle principal. */
    while (Pantalla_Activa() && salida == -1)
    {
        /* Dibujado del fondo. */
        Pantalla_DibujaImagen(fondoUI, ORIGEN_COORDENADAS, ORIGEN_COORDENADAS, Pantalla_Anchura(), Pantalla_Altura());

        /* Dibujado de los botones. */
        dibuja_boton(exit, 255, 0, 0, 255);
        dibuja_boton(volver, 255 ,0 ,0 ,255);

        /* Actualización de las coordenadas del ratón. */
        Pantalla_RatonCoordenadas(&ratonX, &ratonY);

        /* Comrpobación de pulsación de los botones. */
        if (pulsa_boton(exit, ratonX, ratonY)) salida = 1; 
        if (pulsa_boton(volver, ratonX, ratonY)) salida = 0;

        /* Actuazlización de pantalla. */
        Pantalla_Actualiza();
        Pantalla_Espera(MS_ESPERA_MAX);
    };

    /* Liberación de memoria dinámica. */
    Pantalla_ImagenLibera(fondoUI);
    libera_boton(exit);
    libera_boton(volver);

    return salida;

};

/* Definición de la función del juego principal. */
int juego ()
{
    /* Variables utilizadas para medir el tiempo de ejecución. */
    Uint32 t1 = 0;
    Uint32 t0 = 0;
    int delta = 0;

    /* Variable de puntuación en el juego. */
    int puntos = 0;

    /* Variable de ronda, se iniciará a 1 cuando empieze el bucle principal del juego y va aumentando. */
    int ronda = 0;

    /* Variable que determina si se ha acabado una ronda. Empieza a 1 para inicializar por primera vez el ejercito al comenzar el juego. */
    int ronda_acabada = 1;

    /* Variable que sirve de contador para los fotogramas de invulnerabilidad del ugador. */
    int contadorInvulnerable = 0;

    /* Variables de limitación de la zona del juego. Dejo un espacio arriba para poder poner texto con información relevante para el juego. */
    int bordeSup = 3 * MARGEN_JUEGO;
    int bordeInf = Pantalla_Altura() - MARGEN_JUEGO;
    int bordeIzq = MARGEN_JUEGO;
    int bordeDer = Pantalla_Anchura() - MARGEN_JUEGO;

    /* Variables de almacenamiento de la posición del ratón. */
    double ratonX = 0;
    double ratonY = 0;

    /* Botón y variable de salida y vuelta. */
    BotonPtr exit = crea_boton(Pantalla_Anchura() - 2* MARGEN_JUEGO, MARGEN_JUEGO, MARGEN_JUEGO, MARGEN_JUEGO, MSG_CERRAR);
    BotonPtr volver = crea_boton(Pantalla_Anchura() - 6* MARGEN_JUEGO, MARGEN_JUEGO, 3*MARGEN_JUEGO, MARGEN_JUEGO, MSG_VOLVER);
    /* Poner la variable de salida a -1 me permite usarla para determinar el retorno de la función al menú o el cierre de la ventana. */
    int salida = -1;  

    /* Botones y variables extra para representar otros datos. */
    BotonPtr vidasRestantes = crea_boton (MARGEN_JUEGO, MARGEN_JUEGO,  7* MARGEN_JUEGO, MARGEN_JUEGO, MSG_VIDAS_RESTANTES);
    char vidasRestantesTexto[BOTONES_TEXTO_MAX];
    char vidasRestantesChar[BOTONES_CIFRAS_NUM_MAX];
    BotonPtr enemigosRestantes = crea_boton (9*MARGEN_JUEGO, MARGEN_JUEGO, 8*MARGEN_JUEGO, MARGEN_JUEGO, MSG_ENEMIGOS_RESTANTES);
    char enemigosRestantesTexto[BOTONES_TEXTO_MAX];
    char enemigosRestantesChar [BOTONES_CIFRAS_NUM_MAX];
    BotonPtr rondasActuales = crea_boton(18*MARGEN_JUEGO, MARGEN_JUEGO, 7*MARGEN_JUEGO, MARGEN_JUEGO, MSG_RONDAS_ACTUALES);
    char rondasActualesTexto[BOTONES_TEXTO_MAX];
    char rondasActualesChar [BOTONES_CIFRAS_NUM_MAX];
    BotonPtr puntosActuales = crea_boton(26*MARGEN_JUEGO, MARGEN_JUEGO, 6*MARGEN_JUEGO, MARGEN_JUEGO, MSG_PUNTOS_ACTUALES);
    char puntosTexto [BOTONES_TEXTO_MAX];
    char puntosChar [BOTONES_CIFRAS_NUM_MAX];

    /* Variable para las ráfagas de disparos. */
    NodoBalaPtr rafagaJugador = crea_rafaga_balas ();
    NodoBalaPtr rafagaEnemiga = crea_rafaga_balas ();

    /* Variable para ver si se ha producido algún error y gestionar la pantalla si ocurre. */
    int error = 0;

    /* Variables para el uso de imágenes. */
    Imagen * arraySpritesJugador = carga_sprites_array(N_SPRITES_JUGADOR, RUTA_JUGADOR_GENERICA, CARACTER_PERMUTA_GENERICO, 1); 
    Imagen * arraySpritesEnemigo = carga_sprites_array(N_SPRITES_JUGADOR, RUTA_ENEMIGO_GENERICA, CARACTER_PERMUTA_GENERICO, 1);
    Imagen spriteFondoJuego = carga_sprite_aleatorio(N_SPRITES_FONDO, RUTA_FONDO_GENERICA, CARACTER_PERMUTA_GENERICO, 0);
    Imagen balaAmiga = Pantalla_ImagenLee (RUTA_BALA_AMIGA, 1);
    Imagen balaEnemiga = Pantalla_ImagenLee (RUTA_BALA_ENEMIGA, 1);
    Imagen fondoUI = Pantalla_ImagenLee (RUTA_FONDO_UI, 0);
    
    /* Comprobación de error en la carga de sprites. */
    if (arraySpritesJugador == NULL) error = error + 1;
    if (spriteFondoJuego == NULL) error = error + 1;

    /* Creación del dato tipo jugador en memoria. Lo ubico justo en el centro de la pantalla. */
    JugadorPtr player = crea_jugador (ANCHURA_PANTALLA / 2, ALTURA_PANTALLA / 2, JUGADOR_RADIO_BASE, 1.5*JUGADOR_VELOCIDAD_BASE, JUGADOR_VIDAS_BASE);

    /* Declaración del ejercito de enemigos. */
    EjercitoPtr enemigos = NULL;

    /* Comprobación de error en la creación del dato tipo jugador. */
    if (player == NULL) error = error + 1;

    /* Bucle principal de la aplicación. */
    while (Pantalla_Activa() && error == 0 && salida == -1)
    {
        /* Medición del tiempo inicial cuando comienza una iteración. Se mide el tiempo desde la inicialización de la libreria SDL. */
        t0 = SDL_GetTicks();     

        /* Obtención de las coordenadas del ratón. */
        Pantalla_RatonCoordenadas (&ratonX, &ratonY);

        /* Dibujado del fondo del juego y fondo de interfaz. */
        Pantalla_DibujaImagen(fondoUI, ORIGEN_COORDENADAS, ORIGEN_COORDENADAS, Pantalla_Anchura(), Pantalla_Altura());
        Pantalla_DibujaImagen(spriteFondoJuego, bordeIzq,bordeSup, bordeDer - MARGEN_JUEGO, bordeInf - 3* MARGEN_JUEGO);

        /* Dibujado del botón de salida y de vuelta. */
        dibuja_boton(exit, 255, 0, 0, 255);
        dibuja_boton(volver, 255, 0, 0, 255);

         /* Comprobación de pulsación del botón de salida. Al devolver un valor distinto de 0 saladría al menu y cerraría la ventana. */
        if (pulsa_boton(exit, ratonX, ratonY)) salida = 1;

        /* Se rompe el bucle principal y devuelve 0 haciendo que no se cierre el menú. */
        if (pulsa_boton(volver, ratonX, ratonY)) salida = 0;

        /* Movimiento del jugador con las comprobaciones de colisión con los límites de la pantalla. */
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_W) && !colision_hitbox_limiteSup(get_hitbox_jugador(player), bordeSup))
        {
            mueve_arriba_jugador(player);
        };
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_S) && !colision_hitbox_limiteInf(get_hitbox_jugador(player), bordeInf))
        {
            mueve_abajo_jugador(player);
        };
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_D) && !colision_hitbox_limiteDer(get_hitbox_jugador(player), bordeDer))
        {
            mueve_derecha_jugador(player);
        };
        if (Pantalla_TeclaPulsada(SDL_SCANCODE_A) && !colision_hitbox_limiteIzq(get_hitbox_jugador(player), bordeIzq))
        {
           mueve_izquierda_jugador(player);
        };

        /* Acutualización del estado de movimiento del jugador en el caso de que no se mueva en un fotograma. */
        if (!(Pantalla_TeclaPulsada(SDL_SCANCODE_A) || Pantalla_TeclaPulsada(SDL_SCANCODE_D) || Pantalla_TeclaPulsada(SDL_SCANCODE_S) || Pantalla_TeclaPulsada(SDL_SCANCODE_W)))
        {
            modify_estadoMovimiento_jugador (player, 0);
        };

        /* Iteración de la animación del movimiento del jugador. */
        animacion_movimiento_jugador(player, JUGADOR_INCREMENTO_MOVIMIENTO, JUGADOR_LONGITUD_SEGMENTO_BASE, JUGADOR_CANTIDAD_SEGMENTOS_BASE);

        /* Calculo el ángulo relativo del punto donde se ubica el ratón con la hitbox del jugador para poder orientar su imagen. */
        modify_angulo_jugador(player, angulo_hitbox_punto (get_hitbox_jugador(player), ratonX, ratonY)); 

        /* Disparo del jugador con la actualización de su enfriamiento de disparo a través de su campo de enfriamiento de interacción. */
        if (Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT))
        {
            dispara_jugador (player, rafagaJugador, RADIO_BASE_BALAS, VELOCIDAD_BASE_BALAS, ENFRIAMIENTO_BASE_BALAS);
        };

        /* Dividimos las llamadas de funciones de los enemigos en dos partes, una si la ronda ha acabado y otra si no lo ha hecho. */
        if (ronda_acabada == 0)
        {
            /* Orientado de los enemigos del ejercito hacia el jugador. */
            orienta_ejercito (enemigos, get_x_hitbox(get_hitbox_jugador(player)), get_y_hitbox(get_hitbox_jugador(player)));

            /* Animación del ejercito de enemigos. */
            animacion_ejercito (enemigos, JUGADOR_INCREMENTO_MOVIMIENTO, JUGADOR_LONGITUD_SEGMENTO_BASE, JUGADOR_CANTIDAD_SEGMENTOS_BASE);

            /* Disparo de los enemigos. */
            dispara_ejercito (enemigos, rafagaEnemiga, RADIO_BASE_BALAS, VELOCIDAD_BASE_BALAS, ENFRIAMIENTO_BASE_BALAS);

            /* Muevo el ejercito. El modo de movimiento dependerá de la ronda en la que estemos.*/
            mueve_ejercito(enemigos, bordeSup, bordeInf, bordeDer, bordeIzq, ronda % 2);

            /* Comprobación de colisión de la ráfaga del jugador con los enemigos, actualizando de las vidas de los enemigos si ocurre. */
            ejercito_colisiona_rafaga (enemigos, rafagaJugador);

            /* Actualización de los enemigos muertos y la puntuación. */
            muere_ejercito(enemigos, JUGADOR_INCREMENTO_MOVIMIENTO, JUGADOR_LONGITUD_SEGMENTO_BASE, JUGADOR_CANTIDAD_SEGMENTOS_BASE, &puntos);

            /* Dibujado del ejercito. */
            error = error + dibuja_ejercito(enemigos, arraySpritesEnemigo, N_SPRITES_JUGADOR, ORIGEN_SPRITES_MOVIMIENTO, ORIGEN_SPRITES_MUERTE);

            /* Comprobación de muerte de los enemigos. */
            if (ejercito_vacio(enemigos)) ronda_acabada = 1;
        
        };
        if (ronda_acabada == 1)
        {
            /* Incremento el contador de puntos si acaba la ronda. */
            if (enemigos != NULL) puntos = puntos + ronda;

            /* Aumento el contador de rondas. */
            ronda = ronda + 1;

            /* Libero el ejercito de enemigos. */
            if (enemigos != NULL) libera_ejercito (enemigos);
            enemigos = NULL;

            /* Creo un nuevo ejercito con enemigos equivalente a las rondas que llevemos hasta llegar al máximo definido. */
            if (ronda <= ENEMIGOS_MAXIMOS_RECOMENDADOS) enemigos = crea_ejercito (ronda);
            else enemigos = crea_ejercito (ENEMIGOS_MAXIMOS_RECOMENDADOS);

            /* Rellenado del ejercito de enemigos, que se crearán dentro del los márgenes del juego. */
            recluta_ejercito (enemigos, bordeDer - MARGEN_JUEGO, bordeIzq + MARGEN_JUEGO, bordeInf - MARGEN_JUEGO, bordeSup + MARGEN_JUEGO, JUGADOR_RADIO_BASE, JUGADOR_VELOCIDAD_BASE, ENEMIGOS_VIDAS_BASE);
 
            /* Establezco que empieza una nueva ronda. */
            ronda_acabada = 0;
        };

        /* Movimiento de las balas y liberación si se encuentran fuera de los límites. */
        mueve_rafaga_balas(rafagaJugador);
        rafaga_fuera_limites(rafagaJugador, bordeSup, bordeInf, bordeDer, bordeIzq);

        mueve_rafaga_balas(rafagaEnemiga);
        rafaga_fuera_limites(rafagaEnemiga, bordeSup, bordeInf, bordeDer, bordeIzq);

        /* Dibujado de las balas. Recorreré las listas de balas hasta que no exista una bala siguiente a la que ir e iré dibujando cada una de las balas. */
        dibuja_rafaga_balas(rafagaJugador, balaAmiga);
        dibuja_rafaga_balas(rafagaEnemiga, balaEnemiga);

        /* Decremento el contador de invulnerabilidad hasta 0 y cuando llegue establezco la invulnerabilidad del jugador a 0. */
        if (contadorInvulnerable > 0)
        {
            /* Si está invulnerable dibujo debajo del jugador un aura. (la imagen de la bala aimga reutilizada) */
            Pantalla_DibujaImagen(balaAmiga, get_x_hitbox(get_hitbox_jugador(player)) - 1.5 * get_radio_hitbox(get_hitbox_jugador(player)), get_y_hitbox(get_hitbox_jugador(player)) - 1.5 * get_radio_hitbox(get_hitbox_jugador(player)), 3*get_radio_hitbox(get_hitbox_jugador(player)), 3*get_radio_hitbox(get_hitbox_jugador(player)));

            contadorInvulnerable = contadorInvulnerable - 1;
            if (contadorInvulnerable == 0)
            {
                modify_invencible_jugador(player, 0);
            };
        };

        /* Comprobación de colisión de la ráfaga enemiga con el jugador y actualización de sus vidas si son positivas y si no es invulnerable. */
        if (jugador_colisiona_rafaga(player, rafagaEnemiga) && (get_jugador_vidas(player) > 0) && (get_invencible_jugador(player) == 0))
        {
            modify_jugador_vidas(player, get_jugador_vidas(player) - 1);
            
            /* Si el jugador es dañado lo pongo invulnerable y establezco el contador de invulnerabilidad. */
            modify_invencible_jugador(player, 1);
            contadorInvulnerable = JUGADOR_DURACION_INVULNERABLE;
        };

        /* Dibujado del jugador. */
        error = error + dibuja_jugador(player, arraySpritesJugador, N_SPRITES_JUGADOR, ORIGEN_SPRITES_MOVIMIENTO, ORIGEN_SPRITES_MUERTE);       

        /* Paso a texto las vidas actuales y lo concateno con el mensaje del botón copiado a una variable para luego actualizar el texto del botón con dicha variable. */
        sprintf(vidasRestantesChar, "%d", get_jugador_vidas(player));
        strcat(strcpy(vidasRestantesTexto, MSG_VIDAS_RESTANTES), vidasRestantesChar);
        cambia_texto_boton(vidasRestantes, vidasRestantesTexto);
        dibuja_boton(vidasRestantes, 255, 0, 0, 255);

        /* Paso a texto los enemigos restantes y lo concateno con la copia del mesaje de enemigos restantes para actualizar el texto del botón. */
        sprintf(enemigosRestantesChar, "%d", enemigos_ejercito(enemigos));
        strcat(strcpy(enemigosRestantesTexto, MSG_ENEMIGOS_RESTANTES), enemigosRestantesChar);
        cambia_texto_boton(enemigosRestantes, enemigosRestantesTexto);
        dibuja_boton(enemigosRestantes, 255, 0 ,0 ,255);

        /* Paso a texto la ronda actual y la concateno con la copia del mensaje de rondas actuales para actualizar el texto del botón. */
        sprintf(rondasActualesChar, "%d", ronda);
        strcat(strcpy(rondasActualesTexto, MSG_RONDAS_ACTUALES), rondasActualesChar);
        cambia_texto_boton(rondasActuales, rondasActualesTexto);
        dibuja_boton(rondasActuales, 255, 0, 0, 255);

        /* Paso a texto la puntuación actual y la concateno con el mensaje de puntos actuales para actualizar el texto del botón. */
        sprintf(puntosChar, "%d", puntos);
        strcat(strcpy(puntosTexto, MSG_PUNTOS_ACTUALES), puntosChar);
        cambia_texto_boton(puntosActuales, puntosTexto);
        dibuja_boton(puntosActuales, 255, 0 ,0, 255);

        /* Comprobación de muerte del jugador y salida al menu si muere.  */
        if (jugador_muerto(player))
        {
            /* Una vez muere se realiza la animación de muerte hasta que acabe y entonces se vuelve al menú. */
            if(animacion_muerte_jugador(player, JUGADOR_INCREMENTO_MOVIMIENTO, JUGADOR_LONGITUD_SEGMENTO_BASE, JUGADOR_CANTIDAD_SEGMENTOS_BASE))
            {
                salida = 0;
            };
        }; 

        /* Actualización de la pantalla. */
        Pantalla_Actualiza();

        /* Medición del timepo final después de calcular el bucle. */
        t1 = SDL_GetTicks();

        /* Cálculo de delta, que representa lo que se ha tardado desde t0 hata t1, en milisegundos. */
        delta = (t1 - t0);

        /* En caso de que t0 > t1 se asigna por defecto delta = 2 (solo courrirá cuando la medición de tiempo deborde los 32 bits de capacidad, que ocurriría en intervalos de días, pero mejor prevenir que curar.) */
        if (delta < 0)
        {
            delta = MS_ESPERA_MIN;
        }
    
        /* Si el tiempo de ejecución superase o igualase los 16 ms asignariamos a delta 15 ms para evitar que la pantalla esperase 0 o un número negativo de tiempo. */
        if (delta >= MS_ESPERA_MAX)
        {
            delta = MS_ESPERA_MAX - 1;
        }

        /* Se hace esperar a la pantalla 16 milisegúndos (unos 62 FPS) menos el tiempo de ejecución del bucle para mantener los FPS constantes. Al realizar ciertas operaciones después de cerrar la medición de tiempo los FPS reales van a ser menores a los esperados pero no lo suficiente como para considerar el impacto en el rendimiento.*/
        Pantalla_Espera(MS_ESPERA_MAX - delta); 
    }

    /* Almacenamiento de la puntuación conseguida en un fichero. */
    FILE * archivo = NULL;
    archivo = fopen (RUTA_RECORDS, "r");
    /* Variable que dirá si se ha superado el record anterior. */
    int superaRecord = 0;

    /* Compruebo si hay un error al leer archivo. */
    if (archivo == NULL)
    {
        error = error + 1;
        printf(MSG_ERROR_LEER_ARCHIVO);
        scanf("%d");
    }
    /* Si no hay error accedo aquí. */
    else if (archivo != NULL)
    {
        /* Guardo el recor anterior. */
        int recordAnterior = 0;
        int res = fscanf(archivo, "%d", &recordAnterior);

        /* Vuelvo a abrir el archivo en modo escritura. No podía usar ni r+ ni w+ para abrir origialmente ya que con r+ escribia al final y con w+ eliminaba el contenido original*/
        FILE * archivoW = fopen (RUTA_RECORDS, "w");

        /* Si no había record anterior simplemente se guarda la puntuación actual. */
        if (res < 1)
        {
            fprintf(archivoW, "%d", puntos);
            superaRecord = 1;
        }
        /* Si hay archivo anterior se comparará con la puntuación actual, si es mayor se reescribe y si es peor se deja como está. */
        else if (res == 1)
        {
            if(recordAnterior < puntos)
            {
                /* Establezco que he superado el record y escribo el nuevo record. */
                superaRecord = 1;
                fprintf(archivoW, "%d", puntos);
            }
            else if (recordAnterior >= puntos)
            {
                fprintf(archivoW, "%d", recordAnterior);
            };
        }
        /* Cierro el archivo de escritura. */
        fclose(archivoW);
    };  
    /* Cierro el archivo de lectura. */
    fclose(archivo);

    /* Condición del bucle de impresión de la puntuación. */
    int condicionante = 0;

    /* Creación de la cadena de impresión de la puntuación. Los puntos ya están calculados y en su cadena al salir de bucle principal*/
    strcat  (strcpy (puntosTexto, MSG_FIN_PARTIDA_1), puntosChar);

    /* Creación de la cadena de mensaje de fin de juego. */
    char msg_fin [BOTONES_TEXTO_MAX];
    strcpy(msg_fin, MSG_FIN_PARIDA_2);

    /* Dibujado del fondo. */
    Pantalla_DibujaImagen (fondoUI, ORIGEN_COORDENADAS, ORIGEN_COORDENADAS, Pantalla_Anchura(), Pantalla_Altura());

    /* Dibujado del texto con la puntuación y los mensajes de fin de juego. */
    Pantalla_DibujaTexto (puntosTexto, Pantalla_Anchura()/2 - 10*MARGEN_JUEGO, Pantalla_Altura()/2 - 3*MARGEN_JUEGO);
    Pantalla_DibujaTexto(msg_fin, Pantalla_Anchura()/2 - 10*MARGEN_JUEGO, Pantalla_Altura()/2);

    if (superaRecord == 1)
    {
        /* Si se llega aquí se dibujará en pantalla un mensaje de nuevo record. */
        char msg_record [BOTONES_TEXTO_MAX];
        strcpy(msg_record, MSG_NUEVO_RECORD);
        Pantalla_DibujaTexto(msg_record, Pantalla_Anchura()/2 -10*MARGEN_JUEGO, Pantalla_Altura()/2 - 1.5*MARGEN_JUEGO);
    };

    /* Actualizo la pantalla. */
    Pantalla_Actualiza();

    /* Hago esperar la pantalla 2 segundos para que se vea la vetana de puntuación y no se salga accidentalmente de ella si se pulsa el ratón por inercia. */
    Pantalla_Espera(2000);

    /* Bucle de salida de la puntuación. */
    while (Pantalla_Activa() && condicionante == 0)
    {
        
        /* Actualización de la condición de ruptura. */
         if (Pantalla_RatonBotonPulsado(SDL_BUTTON_LEFT) || Pantalla_RatonBotonPulsado(SDL_BUTTON_MIDDLE) || Pantalla_RatonBotonPulsado(SDL_BUTTON_RIGHT))
        {
            condicionante = 1;
        }

        /* Actualización de pantalla. */
        Pantalla_Espera (16);
    }

    /* Liberación del jugador de memoria con actualización de contador de errores */
    error = error + libera_jugador (player);

    /* Liberación de las imágenes utilizadas en el juego con actualización de contador de errores. */
    error = error + libera_sprites_array (arraySpritesJugador, N_SPRITES_JUGADOR);

    error = error + libera_sprites_array (arraySpritesEnemigo, N_SPRITES_JUGADOR);
    
    if (spriteFondoJuego != NULL) Pantalla_ImagenLibera (spriteFondoJuego);
    else error = error + 1;

    if (balaAmiga != NULL) Pantalla_ImagenLibera(balaAmiga);
    else error = error + 1;

    if (balaEnemiga != NULL) Pantalla_ImagenLibera(balaEnemiga);
    else error = error + 1;

    if (fondoUI != NULL) Pantalla_ImagenLibera(fondoUI);
    else error = error + 1;

    /* Liberación de las ráfagas de balas. */
    error = error + libera_rafaga_balas(rafagaJugador);
    error = error + libera_rafaga_balas(rafagaEnemiga);

    /* Liberación de los enemigos. */
    libera_ejercito (enemigos);

    /* Liberación de botones. */
    libera_boton(exit);
    libera_boton(volver);
    libera_boton(vidasRestantes);
    libera_boton(enemigosRestantes);

    /* Comprobación de errores en la ejecución del programa. Si ocurrieron se mostrará por consola su cantidad. */
    if (error != 0)
    {
        printf ("Durante la ejecución del programa se han producido %d errores.\nIntroduce cualquier tecla para finalizar. ", error);
        scanf("%d");
    };

    /* Devuelvo la variable de salida. */
    return salida;
};

int main(int argc, char* argv[])
{
    /* Creación de la pantalla del juego. */
    Pantalla_Crea (NOMBRE_VENTANA, ANCHURA_PANTALLA, ALTURA_PANTALLA);
    
    /* Variable de selección del menu. */
    int seleccion = 0;

    do
    {
        /* Actualizo la selección del menú. */
        seleccion = menu();

        /* Selección de la subrutina según el menú. */
        switch (seleccion)
        {
        case 1:
            /* Rutina principal del juego. */
            seleccion = juego();           
            break;
        case 2:
            /* Menú de ayuda del juego. */
            seleccion = ayuda();
            break;
        }
    } while (seleccion == 0);
    
    /* Liberación de la pantalla del juego. */
    Pantalla_Libera();
}
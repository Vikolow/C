#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Declaracion de constantes
#define FILAS 3
#define COLUMNAS 3
//Declaracion de variables
char tablero[FILAS][COLUMNAS];
int turno = 1; 
int desactivar_foot=0; //variable para desactivar el footer al mostrar resultado fin
int posicion_ocupada = 0; //variable para manejar el mensaje de error de pos ocupada
char jugador1[50];
char jugador2[50];
char ganador =0;
//Funcion para pedir el nombre del jugador
void pedir_jugador(char *mensaje, char *nombre) {
    printf("%s : ", mensaje);
    fgets(nombre, 50, stdin);
    nombre[strlen(nombre) - 1] = '\0'; //elimina caracter de la nueva linea
    fflush(stdin);// limpia buffer de entrada
}
//Funcion para pedir los nombres
void pedir_nombres() {
    int error;
    char mensaje[100];
    error = 1;
    while (error) {
        printf("\nIntroduce el nombre del primer jugador, que juega con X: ");
        pedir_jugador(mensaje, jugador1);
        if (strlen(jugador1) == 0) {
            error = 1;
            printf("\n\nEl nombre del jugador no puede estar vacio.\n\n");
        } else {
            error = 0;
        }
    }
    error = 1;
    while (error) {
        printf("\nIntroduce el nombre del segundo jugador, que juega con O: ");
        pedir_jugador(mensaje, jugador2);
        if (strlen(jugador2) == 0) {
            error = 1;
            printf("\n\nEl nombre del jugador no puede estar vacio.\n\n");
        } else {
            error = 0;
        }
    }
}
// Funcion para comprobar si hay un ganador 
char ComprobarGanador() {
    char ganador = 0;  // Variable para almacenar al ganador

    // Comprobar filas
    for (int i = 0; i < FILAS; ++i) {
        if (tablero[i][0] == tablero[i][1] && tablero[i][1] == tablero[i][2]) {
            return tablero[i][0];
        }
    }
    // Comprobar columnas
    for (int j = 0; j < COLUMNAS; ++j) {
        if (tablero[0][j] == tablero[1][j] && tablero[1][j] == tablero[2][j]) {
            return tablero[0][j];
        }
    }

    // Comprobar diagonales
    if (tablero[0][0] == tablero[1][1] && tablero[1][1] == tablero[2][2]) {
        return tablero[0][0];
    }
    if (tablero[0][2] == tablero[1][1] && tablero[1][1] == tablero[2][0]) {
        return tablero[0][2];
    }

    return 0;  // Devolvemos el ganador ,o, 0 si no hay ganador
}

// Funcion para inicializar el tablero 
void RellenarTablero() {
    char posicion = '1';
    for(int i = 0; i < FILAS; i++) {
        for(int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = posicion++;
        }
    }
}

// Funcion para pedir la posicion
int pedirposi() {
    char entrada[10];
    int posicion;
    printf("Introduce la posicion del tablero a rellenar (1-9, o '0' para salir): ");
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &posicion) != 1) {
        // Limpiar buffer de entrada
        while (getchar() != '\n'); // Leer y descartar caracteres hasta encontrar un salto 
        // Indicar posicion no valida
        return -1;
    }
    return posicion;
}

//Funcion para dibujar el tablero
void DibujarTablero() {
    //Formato del tablero
    printf("           +---+---+---+\n");
    for (int i = 0; i < FILAS; i++) {
        printf("           ");
        for (int j = 0; j < COLUMNAS; j++) {
            printf("| %c ", tablero[i][j]);
        }
        printf("|\n");
        printf("           +---+---+---+\n");
    }
    printf("\n");
    // Si el footer no esta desactivado , muestra turno del jugador
    if(desactivar_foot ==0){
    printf("Turno del Jugador %d :", turno);
    if (turno == 1) {
        printf("%s(X)\n",jugador1);
    } else {
        printf("%s(O)\n",jugador2);
    }
    }

}
//Funcion que comprueba si el tablero esta lleno
int TableroLLeno() {
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            if (tablero[i][j] != 'X' && tablero[i][j] != 'O') {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    const char *arteASCI =
        "                                             \n"
        " _______  _____   ______   _____   ______   _     _       _____    _____    _     _    _____  \n"
        "(__ _ __)(_____) (______) (_____) (______) (_)   (_)     (_____)  (______) (_)   (_)  (_____) \n"
        "  (_)   (_)__(_)(_)__    (_)__    (_)__    (__)_ (_)     (_)__(_) (_)___(_) (_)_(_)  (_)___(_)\n"
        "  (_)   (_____) (____)  (___)_    (____)   (_)(_)(_)     (______) (_______)   (_)    (_______)\n"
        "  (_)   ( ) ( ) (_)___   ____(_)   (_)____ (_)  (__)     ( ) ( )  (_)   (_)   (_)    (_)   (_)\n"
        "  (_)   (_) (_)(______) (_____)   (______) (_)   (_)     (_)  (_) (_)   (_)   (_)    (_)   (_)  \n";

    printf("\n%s", arteASCI);
    printf("\n\n");
    RellenarTablero();//inicializar tablero
    pedir_nombres(); //Pedir nombres
    char posicion[10];
    int hay_error = 0;

    do {
        system("cls");
        printf("\n\n\n*** TRES EN RAYA (FASE 3) ***\n3_en_raya_v3.c \nRealizado por:Victor Gonzalez\n\n");
        int pos;
        //Control de caracter no valido
        if (hay_error == 2) {
            printf("Error: no es un valor valido. Por favor, introduce un valor entre '1' y '9' o '0' para salir.\n");
            printf("Posibles valores: '1','2','3','4','5','6','7','8','9'.\n");
            printf("\n\n");
        }
        //Control de posicion ocupada
        if (hay_error == 1) {
            printf("Posicion %d ya ocupada.\n", posicion_ocupada);
            printf("Elige otra posicion diferente.\n");
        }

        printf("\n\n");
        DibujarTablero(); //Dibujar tablero
        pos = pedirposi(); //pedir posicion

        //Control de interrupcion del juego
        if (pos == 0) {
            printf("\nJuego finalizado prematuramente.\n");
            break;
        }
        // validar entrada
        if (pos < 1 || pos > 9) {
            hay_error = 2; // error de caracter fuera del rango
        } else {
            hay_error = 0;

            int fila = (pos - 1) / FILAS;
            int columna = (pos - 1) % COLUMNAS;
            //Control de posicion ocupada
            if (tablero[fila][columna] == 'X' || tablero[fila][columna] == 'O') {
                hay_error = 1;
                posicion_ocupada = pos;
                continue;
            } else {
                hay_error = 0;
                //Colocar ficha y pasar el turno
                if (turno == 1) {
                    tablero[fila][columna] = 'X';
                    turno = 2;
                } else {
                    tablero[fila][columna] = 'O';
                    turno = 1;
                }
                //Comprueba si hay ganador en cada iteracion
                ganador = ComprobarGanador();
                if (ganador != 0) {
                    if (ganador == 'X') {
                        printf("\nEl jugador %s (X) ha ganado!\n", jugador1);
                    } else {
                        printf("\nEl jugador %s (O) ha ganado!\n", jugador2);
                    }
                    break; //Si encuentra ganador sal del bucle
                }
            }
        }

    } while (!TableroLLeno()); 
    //Mensaje de victoria 
    if (ganador != 0) {
    if (ganador == 'X') {
        printf("\nEnhorabuena jugador: %s por la victoria magistral\n\n", jugador1);
         } else {
                printf("\nEnhorabuena jugador: %s por la victoria magistral\n\n", jugador2);
                }}
    //Desactivar mensaje de turno antes de llamar el tablero de fin partida
    desactivar_foot=1;
    DibujarTablero();

    printf("          +------------------+\n");
    printf("          |  BUENA PARTIDA   |\n");
    printf("          |     JUGADORES    |\n");
    printf("          +------------------+\n");

    return 0;
}

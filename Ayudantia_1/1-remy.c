/* Ejercicio 1: Ratón en el laberinto (Backtracking puro)
   Objetivo didáctico: Introducir recursión + retroceso (backtracking) y la idea de marcar/desmarcar estados.
   Contexto: Un ratón quiere salir del laberinto desde (0,0) hasta (N-1,N-1).
*/
#include <stdio.h>

#define N 4

static int laberinto[N][N] = {
    {0, 1, 0, 0},
    {0, 0, 0, 1},
    {1, 1, 0, 0},
    {1, 1, 1, 0}
};

static int sol[N][N] = {0};

/* Prototipo */
int mover(int x, int y);

/* Intenta mover el ratón; retorna 1 si se llegó a la meta */
int mover(int x, int y) {
    // Pregunta: ¿Qué chequea esta condición inicial?
    if (x == N-1 && y == N-1) { // RESP: Ver si alcanzamos la meta.
        sol[x][y] = 1;
        return 1;
    }
    // Pregunta: ¿Por qué verificamos límites, paredes y si ya se visitó?
    if (x >= 0 && y >= 0 && x < N && y < N && laberinto[x][y] == 0 && sol[x][y] == 0) {
        sol[x][y] = 1; // Marcamos la celda como parte del camino actual.
        // Pregunta: ¿Qué pasará si la llamada recursiva de abajo retorna 1?
        if (mover(x+1, y) || mover(x, y+1)) return 1; // RESP: Se propaga el éxito.
        // Pregunta: ¿Por qué es necesario desmarcar (backtracking) aquí?
        sol[x][y] = 0; // RESP: Para intentar otros caminos sin esta marca.
    }
    return 0; // No se pudo avanzar desde (x,y)
}

int main(void) {
    int i, j;  /* Declarar variables al inicio de la función */
    if (mover(0,0)) {
        printf("Camino encontrado (1 = camino):\n");
        for (i=0; i<N; i++) {
            for (j=0; j<N; j++) printf("%d ", sol[i][j]);
            printf("\n");
        }
    } else {
        printf("No hay camino posible.\n");
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10  // Máximo tamaño permitido para la matriz

// Prototipos de funciones
int validar_entero();
float validar_flotante();
void Sol_Sis_Ec();
int es_dominante_diagonal(float matriz[MAX][MAX], int n);
void mostrar_matriz(float matriz[MAX][MAX], float vector[MAX], int n);
float determinante(float matriz[MAX][MAX], int n);
void corregir_coeficiente(float matriz[MAX][MAX], int n, float vector[MAX]);

int main() {
    while (1) {
        Sol_Sis_Ec();
        printf("\n¿Desea capturar otra matriz? (1 = Sí, otro = No): ");
        if (validar_entero() != 1) {
            exit(0);
        }
    }
}

// Valida que el usuario ingrese un número entero
int validar_entero() {
    int valor;
    while (scanf("%d", &valor) != 1) {
        printf("Entrada inválida. Ingrese un número entero: ");
        while (getchar() != '\n'); // Limpia el buffer de entrada
    }
    return valor;
}

// Valida que el usuario ingrese un número flotante
float validar_flotante() {
    float valor;
    while (scanf("%f", &valor) != 1) {
        printf("Entrada inválida. Ingrese un número flotante: ");
        while (getchar() != '\n'); // Limpia el buffer de entrada
    }
    return valor;
}

// Muestra la matriz y el vector independiente
void mostrar_matriz(float matriz[MAX][MAX], float vector[MAX], int n) {
    int i,j;
	printf("Matriz ingresada:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%8.2f ", matriz[i][j]);
        }
        printf("| %8.2f\n", vector[i]);
    }
}

// Verifica si la matriz es dominante diagonalmente
int es_dominante_diagonal(float matriz[MAX][MAX], int n) {
	int i,j;
    for (i = 0; i < n; i++) {
        float suma = 0;
        for (j = 0; j < n; j++) {
            if (i != j) suma += fabs(matriz[i][j]);
        }
        if (fabs(matriz[i][i]) <= suma) return 0;  // No es dominante diagonal
    }
    return 1;
}

// Calcula el determinante por triangulación (Método de Gauss)
float determinante(float matriz[MAX][MAX], int n) {
	int i,j,k;
    float det = 1.0, temp;
    for (i = 0; i < n; i++) {
        if (matriz[i][i] == 0) return 0;  // No se puede triangular

        for (j = i + 1; j < n; j++) {
            temp = matriz[j][i] / matriz[i][i];
            for (k = 0; k < n; k++) {
                matriz[j][k] -= temp * matriz[i][k];
            }
        }
        det *= matriz[i][i];
    }
    return det;
}

// Permite corregir un coeficiente específico en la matriz o vector
void corregir_coeficiente(float matriz[MAX][MAX], int n, float vector[MAX]) {
    int fila, columna;
    printf("Ingrese el número de fila (0 a %d): ", n - 1);
    fila = validar_entero();
    printf("Ingrese el número de columna (0 a %d) o -1 para el vector: ", n - 1);
    columna = validar_entero();

    if (columna == -1) {
        printf("Ingrese el nuevo valor para el vector independiente en la fila %d: ", fila);
        vector[fila] = validar_flotante();
    } else {
        printf("Ingrese el nuevo valor para la posición [%d][%d]: ", fila, columna);
        matriz[fila][columna] = validar_flotante();
    }
}

// Función principal para resolver el sistema de ecuaciones
void Sol_Sis_Ec() {
    int n;
    int i,j;
    float matriz[MAX][MAX], vector[MAX];

    printf("Ingrese la dimensión de la matriz (n x n): ");
    n = validar_entero();

    printf("Ingrese los coeficientes de la matriz por renglón:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("Elemento [%d][%d]: ", i, j);
            matriz[i][j] = validar_flotante();
        }
        printf("Valor del vector independiente para la fila %d: ", i);
        vector[i] = validar_flotante();
    }

    mostrar_matriz(matriz, vector, n);

    printf("\n¿Los datos ingresados son correctos? (1 = Sí, otro = No): ");
    if (validar_entero() != 1) {
        corregir_coeficiente(matriz, n, vector);
        mostrar_matriz(matriz, vector, n);
    }

    float det = determinante(matriz, n);
    printf("\nDeterminante de la matriz: %.2f\n", det);

    if (es_dominante_diagonal(matriz, n)) {
        printf("La matriz es dominante diagonalmente.\n");
    } else {
        printf("La matriz NO es dominante diagonalmente.\n");
    }

    if (det != 0) {
        printf("El sistema tiene solución.\n");
        // Aquí podrías implementar la solución del sistema si lo necesitas
    } else {
        printf("El sistema asociado no tiene solución.\n");
    }
}


#include <stdio.h>

// Define una estructura para almacenar pares de número y conteo
struct NumeroAparicion {
  int numero;
  int apariciones;
};

void contarRepeticiones(int *arreglo, int longitud) {
  int i, j;
  
  // Crea un arreglo de estructuras para almacenar pares de número y conteo
  struct NumeroAparicion pares[longitud];
  int numPares = 0;

  for (i = 0; i < longitud; i++) {
    int encontrado = 0;
    for (j = 0; j < numPares; j++) {
      if (arreglo[i] == pares[j].numero) {
        pares[j].apariciones++;
        encontrado = 1;
        break;
      }
    }

    if (!encontrado) {
      pares[numPares].numero = arreglo[i];
      pares[numPares].apariciones = 1;
      numPares++;
    }
  }

  // Ordena la estructura de pares en función del conteo (apariciones) de forma descendente
  for (i = 0; i < numPares - 1; i++) {
    for (j = i + 1; j < numPares; j++) {
      if (pares[i].apariciones < pares[j].apariciones) {
        struct NumeroAparicion temp = pares[i];
        pares[i] = pares[j];
        pares[j] = temp;
      }
    }
  }

  // Imprime los resultados ordenados
  for (i = 0; i < numPares; i++) {
    printf("%d: %d\n", pares[i].numero, pares[i].apariciones);
  }
}

int main() {
  int arreglo[] = {5,5,5,5,1, 2, 3, 2, 1, 4, 5, 2};
  int longitud = sizeof(arreglo) / sizeof(arreglo[0]);

  contarRepeticiones(arreglo, longitud);

  return 0;
}

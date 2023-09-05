#include "auxiliares.h"
#include "manejoJson.h"
#include <stdio.h>

//top 3 usuarios con mas prestamos
void top3usuarios(listaPrestamos* l) {
    int longitud = l->tam;  
    NumeroAparicion* pares[longitud];
    int numPares = 0;

    int arreglo[longitud];
    Prestamo* aux = l->inicio;
    for (int i = 0; i < longitud; i++) {
        arreglo[i] = aux->id;
        aux = aux->sig;
    }

    for (int i = 0; i < longitud; i++) {
        int encontrado = 0;
        for (int j = 0; j < numPares; j++) {
            if (arreglo[i] == pares[j]->numero) {
                pares[j]->apariciones++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            pares[numPares]->numero = arreglo[i];
            pares[numPares]->apariciones = 1;
            numPares++;
        }
    }

    // Ordena la estructura de pares en función del conteo (apariciones) de forma descendente
    for (int i = 0; i < numPares - 1; i++) {
        for (int j = i + 1; j < numPares; j++) {
            if (pares[i]->apariciones < pares[j]->apariciones) {
                NumeroAparicion* temp = pares[i];
                pares[i] = pares[j];
                pares[j] = temp;
            }
        }
    }

    // Imprime los resultados ordenados
    for (int i = 0; i < 3; i++) {
        Prestamo* prestamo = buscarPrestamo(l, pares[i]->numero);
        printf("Top 3 usuarios con mas prestamos: \n\t%s: %d\n", prestamo->usuario, pares[i]->apariciones);
    }
}

void top3libros(listaPrestamos* l){
    int longitud = l->tam;  
    NumeroAparicion* pares[longitud];
    int numPares = 0;

    int arreglo[longitud];
    Prestamo* aux = l->inicio;
    for (int i = 0; i < longitud; i++) {
        arreglo[i] = aux->id;
        aux = aux->sig;
    }

    for (int i = 0; i < longitud; i++) {
        int encontrado = 0;
        for (int j = 0; j < numPares; j++) {
            if (arreglo[i] == pares[j]->numero) {
                pares[j]->apariciones++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            pares[numPares]->numero = arreglo[i];
            pares[numPares]->apariciones = 1;
            numPares++;
        }
    }

    // Ordena la estructura de pares en función del conteo (apariciones) de forma descendente
    for (int i = 0; i < numPares - 1; i++) {
        for (int j = i + 1; j < numPares; j++) {
            if (pares[i]->apariciones < pares[j]->apariciones) {
                NumeroAparicion* temp = pares[i];
                pares[i] = pares[j];
                pares[j] = temp;
            }
        }
    }

    // Imprime los resultados ordenados
    for (int i = 0; i < 3; i++) {
        printf("%d\n", pares[i]->numero);
        Prestamo* prestamo = buscarPrestamo(l, pares[i]->numero);
        printf("Top 3 ejemplares con mas prestamos: \n\t%s: %d\n", prestamo->nombreEjemplar, pares[i]->apariciones);
    }
}

void mostrarPrestamosRango(listaPrestamos* l)
{

    char* fechaInicio;
    char* fechaFin;

    while(true){
        printf("Ingrese la fecha de inicio: ");
        scanf(" %[^\n]s", fechaInicio);
        
        printf("Ingrese la fecha de fin: ");
        scanf(" %[^\n]s", fechaFin);
        
        //validar que las fechas sean validas
        if (esFechaValida(fechaInicio) && esFechaValida(fechaFin) && compararFechas(fechaInicio, fechaFin) == 1){
            break; 
        }
        else{
            printf("Ingrese una fecha valida\n");
        }
    }

    Prestamo* aux = l->inicio;
    while (aux != NULL)
    {
        if (compararFechas(aux->fechaInicio, fechaInicio) >= 0 && compararFechas(aux->fechaFin, fechaFin) <= 0)
        {
            printf("\nDetalles del Prestamo:\n");
            printf("\tId: %d\n", aux->id);
            printf("\tUsuario:  %s\n", aux->usuario);
            printf("\tEstado: %d\n", aux->estado);
            printf("\tNombre:  %s\n", aux->nombreEjemplar);
            printf("\tFecha de inicio:  %s\n", aux->fechaInicio);
            printf("\tFecha de fin:  %s\n\n", aux->fechaFin);
        }
    }

}

void recuperarLibrosTxt(listaLibros* l) 
{
    FILE *archivo = fopen("datos/doc.txt", "r");
    char linea[1024];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        
        Libro* libro = calloc(1, sizeof(Libro));
        libro->id = l->tam + 1;
        
        char *palabra = strtok(linea, "|");
        libro->nombre = strdup (palabra);
        
        palabra = strtok(NULL, "|");
        libro->autor = strdup(palabra);
        
        palabra = strtok(NULL, "|");
        libro->anio = strtol(palabra, NULL, 10);
        
        palabra = strtok(NULL, "|");
        libro->genero = strdup(palabra);
        
        palabra = strtok(NULL, "|");
        libro->resumen = strdup(palabra);
        
        palabra = strtok(NULL, "|");
        libro->cantidad = strtol(palabra, NULL, 10);
        
        printf("Título:  %s\n", libro->nombre);
        printf("Autor:  %s\n", libro->autor);
        printf("Año: %d\n", libro->anio);
        printf("Género:  %s\n", libro->genero);
        printf("Descripción:  %s\n", libro->resumen);
        printf("Disponibles: %d\n", libro->cantidad);
        addLibro(l, libro);
        
        printf("\n");
    }
    
    fclose(archivo);
}

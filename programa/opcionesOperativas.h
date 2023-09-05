#include "auxiliares.h"
#include "manejoJson.h"
#include <stdio.h>

void top5recaudaciones(listaPrestamos* l){
    int longitud = l->tam;
    Consulta* consultas[longitud];
    for (int i = 0; i < longitud; i++) {
        consultas[i] = calloc(1, sizeof(Consulta));
        
    }
    int numConsultas = 0;

    //arreglo que guarda las fechas de inicio de los prestamos
    char* fechas[longitud];
    int montos[longitud];
    Prestamo* aux = l->inicio;
    for (int i = 0; i < longitud; i++) {
        fechas[i] = strdup(aux->fechaInicio);
        montos[i] = aux->monto;
        aux = aux->sig;
    }

    for (int i = 0; i < longitud; i++) {
        int encontrado = 0;
        for (int j = 0; j < numConsultas; j++) {
            if (strcmp(fechas[i], consultas[j]->fecha)==0) {
                consultas[j]->monto += montos[i];
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            consultas[numConsultas]->fecha = strdup(fechas[i]);
            consultas[numConsultas]->monto = montos[i];
            numConsultas++;
        }
    }

    // Ordena la estructura de consultas en función del monto de forma descendente
    for (int i = 0; i < numConsultas - 1; i++) {
        for (int j = i + 1; j < numConsultas; j++) {
            if (consultas[i]->monto < consultas[j]->monto) {
                Consulta* temp = consultas[i];
                consultas[i] = consultas[j];
                consultas[j] = temp;
            }
        }
    }

    // Imprime los resultados ordenados
    printf("Top 5 recaudaciones: \n");
    for (int i = 0; i < numConsultas; i++) {
        if (i == 5) {break;}
        printf("\t%s: %d\n", consultas[i]->fecha, consultas[i]->monto);
    }
}

//top 3 usuarios con mas prestamos
void top3usuarios(listaPrestamos* l, listaUsuarios* lu) {
    int longitud = l->tam;  
    NumeroAparicion* pares[longitud];
    for (int i = 0; i < longitud; i++) {
        pares[i] = calloc(1, sizeof(NumeroAparicion));
    }
    int numPares = 0;

    //el arreglo guarda los id de los usuarios
    int arreglo[longitud];
    Prestamo* aux = l->inicio;
    for (int i = 0; i < longitud; i++) {
        arreglo[i] = aux->idUsuario;
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
    printf("Top 3 usuarios con mas prestamos: \n");
    for (int i = 0; i < numPares; i++) {
        if (i == 3) {break;}
        Usuario* u = buscarUsuarioXid(lu, pares[i]->numero);
        printf("\t%s: %d\n", u->nombre, pares[i]->apariciones);
    }
}

void top3libros(listaPrestamos* l, listaLibros* ll) {
    int longitud = l->tam;  
    NumeroAparicion* pares[longitud];
    //inicializar memoria
    for (int i = 0; i < longitud; i++) {
        pares[i] = calloc(1, sizeof(NumeroAparicion));
    }

    int numPares = 0;

    int arreglo[longitud];
    Prestamo* aux = l->inicio;
    for (int i = 0; i < longitud; i++) {
        arreglo[i] = aux->idEjemplar;
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
    printf("Top 3 libros con mas prestamos: \n");
    printf("numPares: %d\n", numPares);
    for (int i = 0; i < numPares; i++) {
        if (i == 3) {break;}
        Libro* lib = buscarLibroXid(ll, pares[i]->numero);
        printf("\t%s: %d\n", lib->nombre, pares[i]->apariciones);
    }
}

void mostrarPrestamosVencidos(listaPrestamos* l)
{
    Prestamo* aux = l->inicio;
    while (aux != NULL)
    {
        int diferenciaEnDias = calcularDiferenciaEnDias(fechaActual(), aux->fechaFin); //prestamos proximos a vencer
        int prestamoVencido = compararFechas(fechaActual(), aux->fechaFin); //prestamos vencidos
        if ((diferenciaEnDias <= 3 && aux->estado == 1) || (prestamoVencido == 1 && aux->estado == 1)) //estado 1: sin entregar
        {
            printf("\nDetalles del Prestamo:\n");
            printf("\tPrestamo N°: %d\n", aux->id);
            printf("\tUsuario:  %s\n", aux->usuario);
            printf("\tFecha de inicio:  %s\n", aux->fechaInicio);
            printf("\tEjemplar:  %s\n", aux->nombreEjemplar);
            printf("\tID ejemplar:  %d\n", aux->idEjemplar);
        }
        
        aux = aux->sig;
    }
}

void mostrarPrestamosRango(listaPrestamos* l)
{
    char* fechaInicio = calloc(10, sizeof(char));
    char* fechaFin = calloc(10, sizeof(char));

    while(true){
        printf("Ingrese la fecha de inicio: ");
        scanf(" %[^\n]s", fechaInicio);
        
        printf("Ingrese la fecha de fin: ");
        scanf(" %[^\n]s", fechaFin);
        
        //imprimir fechas
        printf("Fecha de inicio: %s\n", fechaInicio);
        printf("Fecha de fin: %s\n", fechaFin);
        //validar que las fechas sean validas
        if (esFechaValida(fechaInicio) && esFechaValida(fechaFin) && compararFechas(fechaInicio, fechaFin) == -1){
            break; 
        }
        else{
            printf("Ingrese una fecha valida\n");
        }
    }

    printf("\nResultados:\n");
    Prestamo* aux = l->inicio;
    while (aux != NULL)
    {
        if (compararFechas(aux->fechaInicio, fechaInicio) >= 0 && compararFechas(aux->fechaFin, fechaFin) <= 0)
        {
            printf("\nDetalles del Prestamo:\n");
            printf("\tId: %d\n", aux->id);
            printf("\tUsuario:  %s\n", aux->usuario);
            printf("\tEstado: %s\n", aux->estado > 0 ? "Activo" : "Finalizado");
            printf("\tNombre:  %s\n", aux->nombreEjemplar);
            printf("\tID ejemplar:  %d\n", aux->idEjemplar);
            
            //imprimir si se entrego con tardia o no
            if(aux->estado == 0){
                if(compararFechas(aux->fechaFin, aux->fechaDevolucion) == 1){
                    printf("\tEntrega tardia: si\n");
                }
                else{
                    printf("\tEntrega tardia: no\n");
                }
            }
        }
        aux = aux->sig;
    }

}

void recuperarLibrosTxt(listaLibros* l) 
{
    char* nombreArchivo = calloc(100, sizeof(char));
    printf("Ingrese la ruta del archivo: ");
    scanf(" %[^\n]s", nombreArchivo);

    FILE *archivo = fopen(nombreArchivo, "r");
    char linea[1024];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        if(buscarCoincidencias((char*)linea, "|") != 6 ){
            printf("\nLibro no valido\n");
            continue;
        }

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
        
        //validar que el libro no exista
        if(buscarLibro(l, libro->nombre) == NULL){
            printf("Detalles del Libro:\nTítulo:  %s\n", libro->nombre);
            printf("Autor:  %s\n", libro->autor);
            printf("Año: %d\n", libro->anio);
            printf("Género:  %s\n", libro->genero);
            printf("Descripción:  %s\n", libro->resumen);
            printf("Disponibles: %d\n\n", libro->cantidad);

            addLibro(l, libro);        
        }
    }
    
    fclose(archivo);
}
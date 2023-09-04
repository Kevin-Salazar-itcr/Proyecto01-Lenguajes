#include "auxiliares.h"
#include "manejoJson.h"

void top3prestados(listaPrestamos* l) {
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
                struct NumeroAparicion temp = pares[i];
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


void top3LibrosPrestados(listaPrestamos* l) {
    struct {
        char* titulo;
        int conteo;
    } conteosLibros[l->tam];

    for (int i = 0; i < l->tam; i++) {
        conteosLibros[i].titulo = NULL;
        conteosLibros[i].conteo = 0;
    }

    Prestamo* aux = l->inicio;
    while (aux != NULL) {
        char* titulo = aux->nombreEjemplar;

        int encontrado = 0;
        for (int i = 0; i < l->tam; i++) {
            if (conteosLibros[i].titulo != NULL && strcmp(conteosLibros[i].titulo, titulo) == 0) {
                conteosLibros[i].conteo++;
                encontrado = 1;
                break;
            }
        }

        if (!encontrado) {
            for (int i = 0; i < l->tam; i++) {
                if (conteosLibros[i].titulo == NULL) {
                    conteosLibros[i].titulo = strdup(titulo);
                    conteosLibros[i].conteo = 1;
                    break;
                }
            }
        }

        aux = aux->sig;
    }

    for (int i = 0; i < l->tam - 1; i++) {
        for (int j = i + 1; j < l->tam; j++) {
            if (conteosLibros[i].conteo < conteosLibros[j].conteo) {
                // Intercambiar entradas
                int tempConteo = conteosLibros[i].conteo;
                char* tempTitulo = conteosLibros[i].titulo;
                conteosLibros[i].conteo = conteosLibros[j].conteo;
                conteosLibros[i].titulo = conteosLibros[j].titulo;
                conteosLibros[j].conteo = tempConteo;
                conteosLibros[j].titulo = tempTitulo;
            }
        }
    }

    printf("Top 3 Libros Más Prestados:\n");
    for (int i = 0; i < 3 && conteosLibros[i].titulo != NULL; i++) {
        printf("%d. %s (%d veces prestado)\n", i + 1, conteosLibros[i].titulo, conteosLibros[i].conteo);
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

void incluir_Prestamo(listaPrestamos* l)
{
    Prestamo* prestamo = calloc(1, sizeof(Prestamo));
    
    prestamo->id = l->tam + 1;
    printf("Ingrese el nombre del usuario: ");
    scanf(" %[^\n]s", prestamo->usuario);
    printf("Ingrese el estado del prestamo: ");
    scanf("%d", &prestamo->estado);
    printf("Ingrese el nombre del libro: ");
    scanf(" %[^\n]s", prestamo->nombreEjemplar);
    while(true){
        printf("Ingrese la fecha de inicio del prestamo: ");
        scanf(" %[^\n]s", prestamo->fechaInicio);
        
        printf("Ingrese la fecha de fin del prestamo: ");
        scanf(" %[^\n]s", prestamo->fechaFin);
        
        if (esFechaValida(prestamo->fechaInicio) && esFechaValida(prestamo->fechaFin)){
            if(compararFechas(prestamo->fechaInicio, prestamo->fechaFin) == 1){
                break;
            }
            else{
                printf("La fecha de inicio debe ser menor a la fecha de fin\n");
            }
        }
        else{
            printf("Ingrese una fecha valida\n");
        }
    }
    addPrestamo(l, prestamo);
}

void incluir_Usuario(listaUsuarios* l)
{
    Usuario* usuario = calloc(1, sizeof(Usuario));
    printf("Ingrese la identificacion del usuario: ");
    scanf("%d", &usuario->id);

    printf("Ingrese el nombre del usuario: ");
    scanf("  %[^\n]s", usuario->nombre);
    printf("Ingrese la direccion del usuario: ");
    scanf("  %[^\n]s", usuario->direccion);
    
    addUsuario(l, usuario);
}

void recuperarLibrosTxt(listaLibros* l) 
{
    FILE *archivo = fopen("doc.txt", "r");
    char linea[200];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        
        Libro* libro = calloc(1, sizeof(Libro));
        
        char *palabra = strtok(linea, "|");
        strcpy(libro->nombre, palabra);
        
        palabra = strtok(NULL, "|");
        strcpy(libro->autor, palabra);
        
        palabra = strtok(NULL, "|");
        libro->anio = strtol(palabra, NULL, 10);
        
        palabra = strtok(NULL, "|");
        strcpy(libro->genero, palabra);
        
        palabra = strtok(NULL, "|");
        strcpy(libro->resumen, palabra);
        
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

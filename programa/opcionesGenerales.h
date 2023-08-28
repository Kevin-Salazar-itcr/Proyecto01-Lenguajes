#include "auxiliares.h"
#include "structs.h"

/**
 * @brief funcion que solicita un texto al usuario para buscar en los libros
 * muestra todos los id nombre y resumen de los libros que contengan el texto solicitado
 */ 
void busquedaSimple(listaLibros* l){
    char* texto = calloc(100, sizeof(char));
    printf("Ingrese el texto a buscar: ");
    scanf(" %[^\n]s", texto);

    int n = 0;
    Libro* aux = l->inicio;
    while (aux != NULL)
    {
        if (buscarCoincidencias(aux->nombre, texto) > 0 || buscarCoincidencias(aux->resumen, texto) > 0 || buscarCoincidencias(aux->autor, texto) > 0)
        {
            printf("\nDetalles del Libro:\n");
            printf("\tId: %d\n", aux->id);
            printf("\tNombre:  %s\n", aux->nombre);
            printf("\tAutor:  %s\n", aux->autor);
            printf("\tAnio:  %d\n", aux->anio);
            printf("\tGenero:  %s\n", aux->genero);
            printf("\tResumen:  %s\n", aux->resumen);
            printf("\tDisponibilidad: %s\n\n", aux->cantidad > 0 ? "Si" : "No");
            n++;
        }
        aux = aux->sig;
    }

    printf("Se encontraron %d ejemplares con coincidencias\n", n);
    free(texto);
}

/**
 * @brief funcion que solicita datos especificos al usuario para buscar en los archivos
 * muestra todos los id nombre y resumen de los archivos que contengan los datos solicitados por aparte o juntos a la vez
 */ 
void busquedaAvanzada(){
    char** datos = calloc(6, sizeof(char*));
    for (int i = 0; i < 6; i++){
        datos[i] = calloc(100, sizeof(char));

    }
    printf("Ingrese el nombre a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", &datos[0]);
    printf("Ingrese el autor a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", &datos[1]);
    printf("Ingrese el genero a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", &datos[2]);
    printf("Ingrese el resumen a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", &datos[3]);
    
    while(true){
        printf("Desea que se busque por coincidencia exacta? (s/n): ");
        scanf(" %[^\n]s", &datos[4]);
        if (strcmp(datos[4], "s") == 0 || strcmp(datos[4], "n") == 0){
            break;
        }else{
            printf("Ingrese una opcion valida\n");
        }
    }

    while(true){
        printf("Desea que se busque por todos los rubros? (s/n): ");
        scanf(" %[^\n]s", &datos[5]);
        if (strcmp(datos[5], "s") == 0 || strcmp(datos[5], "n") == 0){
            break;
        }else{
            printf("Ingrese una opcion valida\n");
        }
    }
    printf("\n\n*********Iniciando busqueda*********\n\n");
    //aca se obtienen todos los nombres de los archivos
    
    //pseudocodigo del algoritmo
    //contador para mostrar el numero de coincidencias
    int n = 0;
    //si el campo 6 dice que se quiere por todos los rubros
        //por cada nombre de archivo
            //llamar funcion aux buscarTodasCoinc(..., datos[5]) para saber si se busca por palabra exacta o coincidencia
            //si la funcion retorna 1
                //se muestra el id, nombre y resumen del archivo
    //si el campo 6 dice que no se quiere por todos los rubros
        //por cada nombre de archivo
            //llamar funcion aux buscarCoinc(..., datos[5]) para saber si se busca por palabra exacta o coincidencia
            //si la funcion retorna 1
                //se muestra el id, nombre y resumen del archivo
    printf("Se encontraron %d coincidencias\n", n);
    free(texto);
}

/**
 * @brief funcion para hacer prestamo de un libro
 * 
 */
void prestamoEjemplar(){
    printf("indique su usuario: ");
    char* usuario = calloc(100, sizeof(char));
    scanf(" %[^\n]s", usuario);
    printf("indique el id del ejemplar: ");
    char* id = calloc(100, sizeof(char));
    scanf(" %[^\n]s", id);
    printf("\nEstimado usuario, la fecha de su prestamo sera situada desde hoy y hasta la fecha que indique\n");

    char* fechaPrestamo = fechaActual();
    char* fechaDevolucion = calloc(15, sizeof(char));
    while(true){
        printf("indique la fecha de devolucion en formato dd/mm/aaaa: ");
        scanf(" %[^\n]s", fechaDevolucion);
        if (esFechaValida(fechaDevolucion)){
            break;
        }else{
            printf("Ingrese una fecha valida\n");
        }

        //se valida que la fecha de devolucion sea mayor a la fecha actual
        int valido = compararFechas(fechaPrestamo, fechaDevolucion);
        if (valido == 1 || valido == 0){
            printf("La fecha de devolucion debe ser mayor a la fecha actual\n\n");
        }else{
            break;
        }
    }

    //validar disponibilidad del ejemplar
}


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
}

/**
 * @brief funcion que solicita datos especificos al usuario para buscar en los archivos
 * muestra todos los id nombre y resumen de los archivos que contengan los datos solicitados por aparte o juntos a la vez
 */ 
void busquedaAvanzada(listaLibros* l){
    char** datos = calloc(6, sizeof(char*));
    for (int i = 0; i < 6; i++){
        datos[i] = calloc(100, sizeof(char));

    }
    printf("Ingrese el nombre a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", datos[0]);
    printf("Ingrese el autor a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", datos[1]);
    printf("Ingrese el genero a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", datos[2]);
    printf("Ingrese el resumen a buscar (0 si no desea buscar por este rubro): ");
    scanf(" %[^\n]s", datos[3]);
    
    while(true){
        printf("Desea que se busque por coincidencia exacta? (s/n): ");
        scanf(" %[^\n]s", datos[4]);
        if (strcmp(datos[4], "s") == 0 || strcmp(datos[4], "n") == 0){
            break;
        }else{
            printf("Ingrese una opcion valida\n");
        }
    }

    while(true){
        printf("Desea que se busque por todos los rubros? (s/n): ");
        scanf(" %[^\n]s", datos[5]);
        if (strcmp(datos[5], "s") == 0 || strcmp(datos[5], "n") == 0){
            break;
        }else{
            printf("Ingrese una opcion valida\n");
        }
    }
    printf("\n\n*********Iniciando busqueda*********\n\n");
    
    int n = 0;
    Libro* aux = l->inicio;
    while (aux != NULL)
    {
        //si se quiere buscar por coincidencia exacta (usando strcmp)
        if(strcmp(datos[4], "s") == 0){
            //si se quiere buscar por todos los rubros (uso de &&)
            if(strcmp(datos[5], "s") == 0){
                if(strcmp(datos[0], aux->nombre) == 0 && strcmp(datos[1], aux->autor) == 0 && strcmp(datos[2], aux->genero) == 0 && strcmp(datos[3], aux->resumen) == 0){
                    printf("\nDetalles del Libro:\n");
                    printf("\tId: %d\n", aux->id);
                    printf("\tNombre:  %s\n", aux->nombre);
                    printf("\tResumen:  %s\n", aux->resumen);
                    n++;
                }
            }
            //si no se quiere buscar por todos los rubros (uso de ||)
            else{
                if(strcmp(datos[0], aux->nombre) == 0 || strcmp(datos[1], aux->autor) == 0 || strcmp(datos[2], aux->genero) == 0 || strcmp(datos[3], aux->resumen) == 0){
                    printf("\nDetalles del Libro:\n");
                    printf("\tId: %d\n", aux->id);
                    printf("\tNombre:  %s\n", aux->nombre);
                    printf("\tResumen:  %s\n", aux->resumen);
                    n++;
                }
            }
        }
        //si se quiere buscar por coincidencias (usando buscarCoincidencias)
        else{
            //si se quiere buscar por todos los rubros (uso de &&)
            if(strcmp(datos[5], "s") == 0){
                if(buscarCoincidencias(datos[0], aux->nombre) > 0 && buscarCoincidencias(datos[1], aux->autor) > 0 && buscarCoincidencias(datos[2], aux->genero) > 0 && buscarCoincidencias(datos[3], aux->resumen) > 0){
                    printf("\nDetalles del Libro:\n");
                    printf("\tId: %d\n", aux->id);
                    printf("\tNombre:  %s\n", aux->nombre);
                    printf("\tResumen:  %s\n", aux->resumen);
                    n++;
                }
            }
            //si no se quiere buscar por todos los rubros (uso de ||)
            else{
                if(buscarCoincidencias(datos[0], aux->nombre) > 0 || buscarCoincidencias(datos[1], aux->autor) > 0 || buscarCoincidencias(datos[2], aux->genero) > 0 || buscarCoincidencias(datos[3], aux->resumen) > 0){
                    printf("\nDetalles del Libro:\n");
                    printf("\tId: %d\n", aux->id);
                    printf("\tNombre:  %s\n", aux->nombre);
                    printf("\tResumen:  %s\n", aux->resumen);
                    n++;
                }
            }
        }
        aux = aux->sig;
    }
    
    printf("Se encontraron %d ejemplares con coincidencias\n", n);
    free (datos);
}

/**
 * @brief funcion para solicitar prestamo de un ejemplar
 * 
 * @param l lista de libros
 * @param u lista de usuarios
 * @param p lista de prestamos
 */
void prestamoEjemplar(listaLibros* l, listaUsuarios* u, listaPrestamos* p){
    printf("indique su id de usuario: ");
    char* usuario = calloc(100, sizeof(char));
    scanf(" %[^\n]s", usuario);
    printf("indique el id del ejemplar: ");
    int id;
    scanf(" %d", &id);
    
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
        if (valido != -1){
            printf("La fecha de devolucion debe ser mayor a la fecha actual\n\n");
        }else{
            break;
        }
    }

    //validar que el usuario exista
    Usuario* user = buscarUsuario(u, usuario);
    if (user == NULL){
        printf("El usuario no existe\n");
        return;
    }
    
    //validar disponibilidad del ejemplar
    Libro* aux = l->inicio;
    while (aux != NULL)
    {
        if (strcmp(aux->id, id) == 0)
        {
            if (aux->cantidad > 1)
            {
                aux->cantidad--;
                printf("El prestamo se ha realizado con exito\n");
                
                Prestamo* prestamo = calloc(1, sizeof(Prestamo));
                prestamo->id = p->tam + 1;
                prestamo->usuario = user->nombre;
                prestamo->nombreEjemplar = aux->nombre;
                prestamo->idEjemplar = aux->id;
                prestamo->fechaInicio = fechaPrestamo;
                prestamo->fechaFin = fechaDevolucion;
                prestamo->estado = 1; //activo
                prestamo->fechaDevolucion = "N/A";

                printf("Detalles del prestamo:\n");
                printf("\tId: %d\n", prestamo->id);
                printf("\tUsuario:  %s\n", prestamo->usuario);
                printf("\tNombre del ejemplar:  %s\n", prestamo->nombreEjemplar);
                printf("\tId del ejemplar:  %d\n", prestamo->idEjemplar);
                printf("\tFecha de inicio:  %s\n", prestamo->fechaInicio);
                printf("\tFecha de devolucion:  %s\n", prestamo->fechaFin);

                addPrestamo(p, prestamo);
                return;
            }
            else{
                printf("No hay ejemplares disponibles de este libro\n");
                return;
            }
        }
        aux = aux->sig;
    }
    printf("\n\nNo se encontro el ejemplar indicado\n\n");
    return;
}

/**
 * @brief funcion para devolver un ejemplar
 * El sistema pide el id del prestamo y la fecha de devolucion (capturada automaticamente)
 * @param l lista de libros
 * @param u lista de usuarios
 * @param p lista de prestamos
 */

/*
tabla de montos para calculo de prestamo
Duración préstamo|Tarifa día préstamo|Tarifa día tardía
1 a 7 días       |150                |75
8 a 15 días      |125                |50
16 días o más    |100                |25
*/
void devolverEjemplar(listaLibros* l, listaUsuarios* u, listaPrestamos* p){
    int idPrestamo;
    printf("indique el id del prestamo: ");
    scanf(" %d", &idPrestamo);
    char* fechaDevolucion = fechaActual();
    
    //validar que exista el prestamo
    Prestamo* prestamo = buscarPrestamo(p, idPrestamo);
    if (prestamo == NULL){
        printf("El prestamo no existe\n");
        return;
    }
    if (prestamo->estado == 0){
        printf("El prestamo ya ha sido devuelto\n");
        return;
    }

    //calcular monto a pagar
    int diasHabiles = calcularDiferenciaEnDias(prestamo->fechaInicio, prestamo->fechaFin);
    int diasEntrega = calcularDiferenciaEnDias(prestamo->fechaInicio, fechaDevolucion);
    
    if(diasEntrega == 0){
        printf("No puede devolver el libro el mismo dia que lo presto\n");
        return;
    }

    int monto = 0;
    if(diasHabiles >= 1 && diasHabiles <= 7){
        monto = 150 * diasEntrega;
        if(diasEntrega > diasHabiles){
            monto += 75 * (diasEntrega - diasHabiles);
        }
    }
    else if(diasHabiles >= 8 && diasHabiles <= 15){
        monto = 125 * diasEntrega;
        if(diasEntrega > diasHabiles){
            monto += 50 * (diasEntrega - diasHabiles);
        }
    }
    else if(diasHabiles >= 16){
        monto = 100 * diasEntrega;
        if(diasEntrega > diasHabiles){
            monto += 25 * (diasEntrega - diasHabiles);
        }
    }

    printf("El monto a pagar es de %d\n", monto);
    printf("Su prestamo ha sido devuelto con una tardia de %d dias\n", diasEntrega - diasHabiles);
    prestamo->estado = 0;
    prestamo->fechaDevolucion = fechaDevolucion;
    return;
}
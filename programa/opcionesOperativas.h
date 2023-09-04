#include "auxiliares.h"
#include "manejoJson.h"

void top3UsuariosMasPrestamos(listaPrestamos* l) {
    struct {
        char* usuario;
        int conteo;
    } conteosUsuarios[l->tam];

    // Inicializar los conteos en 0
    for (int i = 0; i < l->tam; i++) {
        conteosUsuarios[i].usuario = NULL;
        conteosUsuarios[i].conteo = 0;
    }

    Prestamo* aux = l->inicio;
    while (aux != NULL) {
        char* usuario = aux->usuario;

    }        
    int encontrado = 0;
    for (int i = 0; i < l->tam; i++) {
        if (conteosUsuarios[i].usuario != NULL && strcmp(conteosUsuarios[i].usuario, usuario) == 0) {
            conteosUsuarios[i].conteo++;
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        for (int i = 0; i < l->tam; i++) {
            if (conteosUsuarios[i].usuario == NULL) {
                conteosUsuarios[i].usuario = strdup(usuario);
                conteosUsuarios[i].conteo = 1;
                break;
            }
        }
    }

        aux = aux->sig;

    for (int i = 0; i < l->tam - 1; i++) {
        for (int j = i + 1; j < l->tam; j++) {
            if (conteosUsuarios[i].conteo < conteosUsuarios[j].conteo) {

                int tempConteo = conteosUsuarios[i].conteo;
                char* tempUsuario = conteosUsuarios[i].usuario;
                conteosUsuarios[i].conteo = conteosUsuarios[j].conteo;
                conteosUsuarios[i].usuario = conteosUsuarios[j].usuario;
                conteosUsuarios[j].conteo = tempConteo;
                conteosUsuarios[j].usuario = tempUsuario;
            }
        }
    }

    printf("Top 3 Usuarios con Más Préstamos:\n");
    for (int i = 0; i < 3 && conteosUsuarios[i].usuario != NULL; i++) {
        printf("%d. %s (%d préstamos)\n", i + 1, conteosUsuarios[i].usuario, conteosUsuarios[i].conteo);
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
            printf("\tNombre:  %s\n", aux->nombre);
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
        printf("Año: %d\n", &libro->anio);
        printf("Género:  %s\n", libro->genero);
        printf("Descripción:  %s\n", libro->resumen);
        printf("Disponibles: %d\n", libro->cantidad);
        addLibro(l, libro);
        
        printf("\n");
    }
    
    fclose(archivo);
}

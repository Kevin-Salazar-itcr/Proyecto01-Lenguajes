#include "opcionesGenerales.h"

/**
 * @brief Menu de opciones operativas
 *
 * @return true volver al menu principal
 * @return false se repite el menu
 */
bool opsOperativas(listaLibros *ll, listaUsuarios *lu, listaPrestamos *lp){
    char opcion;
    printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n********** *Menu de opciones* ***********\n");
    printf("\t1. Gestion de catalogo\n\t2. Gestion de usuarios\n\t3. Historial de prestamos\n");
    printf("\t4. Vencimiento de prestamos\n\t5. Estadisticas\n\t6. Volver\n");
    printf("Ingrese una opcion >>");
    scanf(" %c", &opcion);

    switch (opcion){
        case '1':{
            recuperarLibrosTxt(ll);
            break;
        }
        case '2':{
            int id = 0;
            char* nombre = calloc(20, sizeof(char));
            char* direccion = calloc(50, sizeof(char));
            printf("Ingrese el id del usuario: ");
            scanf(" %d", &id);
            printf("Ingrese el nombre del usuario: ");
            scanf(" %[^\n]s", nombre);
            printf("Ingrese la direccion del usuario: ");
            scanf(" %[^\n]s", direccion);

            Usuario* u = calloc(1, sizeof(Usuario));
            u->id = id;
            u->nombre = nombre;
            u->direccion = direccion;    

            addUsuario(lu, u);

            printf("Usuario agregado exitosamente\n");
            break;
        }
        case '3':{
	        mostrarPrestamosRango(lp);
            break;
        }
        case '4':{
	        printf("\ncaso 4\n");
            break;
        }
        case '5':{
            char opcion2 = '';
            while(opcion2 != 'd'){
                printf("a) Top 3 ejemplares mas prestados\n");
                printf("b) Top 3 usuarios con mas prestamos\n");
                printf("c) Top 5 de mes-anio con mayor monto recaudado\n");
                printf("d) Volver\n");
                printf("Seleccione una opcion>>");
                
                scanf(" %c", &opcion2);
                switch(opcion2){
                    case 'a':{
                        top3libros(lp, ll);
                        break;
                    }
                    case 'b':{
                        top3usuarios(lp, lu);
                        break;
                    }
                    case 'c':{
                        printf("Sin implementar\n");
                        break;
                    }
                    case 'd':{
                        system("clear");
                        break;
                    }
                    default:{
                        printf("\nOpcion no valida\n");
                        break;
                    }
                }
            }
            break;
        }
        case '6':{
            system("clear");
            return true;
        }
        default:{
            printf("\nOpcion no valida\n");
	        //En Linux no existe el system("pause") como en windows, se usa esto
            system("clear");
            break;
        }
    }
    return false;
}

/**
 * @brief Menu de opciones generales
 *
 * @return true volver al menu principal
 * @return false se repite el menu
 */
bool opsGenerales(listaLibros *ll, listaUsuarios *lu, listaPrestamos *lp){
    char opcion;
    printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n********** *Menu de opciones* ***********\n");
    printf("\t1. Búsqueda simple\n\t2. Búsqueda avanzada\n\t3. Prestamo de ejemplar\n\t4. Devolución de ejemplar\n\t5. Volver\n");
    printf("Ingrese una opcion >>");
    scanf(" %c", &opcion);

    switch (opcion){
        case '1':{
	        busquedaSimple(ll);
            break;
        }
        case '2':{
	        busquedaAvanzada(ll);
            break;
        }
        case '3':{
	        prestamoEjemplar(ll, lu, lp);
            break;
        }
        case '4':{
	        devolverEjemplar(ll, lu, lp);
            break;
        }
        case '5':{
            system("clear");
            return true;
        }
        default:{
            printf("\nOpcion no valida\n");
	        //En Linux no existe el system("pause") como en windows, se usa esto
             system("clear");
            break;
        }
    }
    return false;
}

/**
 * @brief Menu de opciones del programa
 * 
 * @return true se termina el programa
 * @return false se repite el menu
 */
bool menu(listaLibros *ll, listaUsuarios *lu, listaPrestamos *lp){
    char opcion;
    printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n********** *Menu de opciones* ***********\n");
    printf("\t1. Opciones operativas\n\t2. Opciones generales\n\t3. Salir\n");
    printf("Ingrese una opcion >>");
    scanf(" %c", &opcion);

    switch (opcion){
        case '1':{
	        bool final = false;
            while (!final){
                final = opsOperativas(ll, lu, lp);
            }
            break;
        }
        case '2':{
	        bool final = false;
            while (!final){
                final = opsGenerales(ll, lu, lp);
            }
            break;
        }
        case '3':{
            system("clear");
            printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n**********  * Hasta luego *  ***********\n");
            return true;
        }
        default:{
            printf("\nOpcion no valida\n");
	        //En Linux no existe el system("pause") como en windows, se usa esto
            system("clear");
            break;
        }
    }
    return false;
}

// main
int main(){
    listaUsuarios *lu = calloc(1, sizeof(listaUsuarios));
    listaLibros *ll = calloc(1, sizeof(listaLibros));
    listaPrestamos *lp = calloc(1, sizeof(listaPrestamos));

    // Cargar datos
    leerUsuarios(lu);
    printf("Usuarios cargados\n");
    leerLibros(ll);
    printf("Libros cargados\n");
    leerPrestamo(lp);
    printf("Prestamos cargados\n");

    bool fin = false;
    while (!fin){
        fin = menu(ll, lu, lp);
    }

    // Guardar datos
    guardarUsuariosJson(lu);
    printf("Usuarios guardados\n");
    guardarLibrosJson(ll);
    printf("Libros guardados\n");
    guardarPrestamosJson(lp);
    printf("Prestamos guardados\n");
    return 0;
}

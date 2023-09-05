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
    printf("\t1. Gestion de catalogo\n\t2. Gestion de usuarios 2\n\t3. Historial de prestamos\n");
    printf("\t4. Vencimiento de prestamos\n\t5. Estadisticas\n\t6. Volver\n");
    printf("Ingrese una opcion >>");
    scanf(" %c", &opcion);

    switch (opcion){
        case '1':{
            recuperarLibrosTxt(ll);
            break;
        }
        case '2':{
	        incluir_Usuario(lu);
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
            char opcion2;
            while(opcion2 != 'd'){
                printf("a) Top 3 ejemplares mas prestados\n");
                printf("b) Top 3 usuarios con mas prestamos\n");
                printf("c) Top 5 de mes-anio con mayor monto recaudado\n");
                printf("d) Volver\n");
                printf("Seleccione una opcion>>");
                
                scanf(" %c", &opcion2);
                switch(opcion2){
                    case 'a':{
                        top3libros(ll);
                        break;
                    }
                    case 'b':{
                        top3usuarios(lu);
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
	        devolucionEjemplar(ll, lu, lp);
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
    printf("\t1. Opciones operativas\n\t2. Opciones generales 2\n\t3. Salir\n");
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
    return 0;
}

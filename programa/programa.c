#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Menu de opciones
 *
 * @return true fin del programa
 * @return false se repite el menu
 */
bool menu(){
    char opcion;
    system("clear");
    printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n********** *Menu de opciones* ***********\n");
    printf("\t1. Gestion de catalogo\n\t2. Gestion de usuarios 2\n\t3. Historial de prestamos\n");
    printf("\t4. Vencimiento de prestamos\n\t5. Estadisticas\n\t6. Salir\n");
    printf("Ingrese una opcion >>");
    opcion = getchar();

    switch (opcion){
        case '1':{
	    printf("\ncaso 1\n");
            break;
        }
        case '2':{
	    printf("\ncaso 2\n");
            break;
        }
        case '3':{
	    printf("\ncaso 3\n");
            break;
        }
        case '4':{
	    printf("\ncaso 4\n");
            break;
        }
        case '5':{
	    printf("\ncaso 5\n");
            break;
        }
        case '6':{
            system("clear");
            printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n**********  * Hasta luego *  ***********\n");
            return true;
        }
        default:{
            printf("\nOpcion no valida\n");
	    //En Linux no existe el system("pause") como en windows, se usa esto
            char c;
            printf("Presione una tecla para continuar...\n");
            scanf("%c", &c);
            system("clear");
            break;
        }
    }
    return false;
}

// main
int main(){
    bool fin = false;
    while (!fin){
        fin = menu();
    }
    return 0;
}

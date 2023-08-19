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
    system("cls");
    printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n********** *Menu de opciones* ***********\n");
    printf("\t1. Gestion de catalogo\n\t2. Gestion de usuarios 2\n\t3. Historial de prestamos\n");
    printf("\t4. Vencimiento de prestamos\n\t5. Estadisticas\n\t6. Salir\n");
    printf("Ingrese una opcion >>");
    scanf("%c", &opcion);
    switch (opcion){
        case '1':{
            break;
        }
        case '2':{
            break;
        }
        case '3':{
            break;
        }
        case '4':{
            break;
        }
        case '5':{
            break;
        }
        case '6':{
            system("cls");
            printf("      o    ~~~^-< ### >-^~~~    o\n      (___/ Biblioteca V1.0 \\___)\n**********  * Hasta luego *  ***********\n");
            return true;
        }
        default:{
            printf("Opcion no valida\n");
            system("pause");
            system("cls");
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
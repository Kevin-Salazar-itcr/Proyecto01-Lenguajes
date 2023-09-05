#include "manejoJson.h"

int main(){
    listaUsuarios * lista = calloc(1, sizeof(listaUsuarios));
    leerUsuarios(lista);

    Usuario* u = calloc(1, sizeof(Usuario));
    u->nombre = "Juana";
    u->direccion = "Por alla";
    u->id = 11;
    addUsuario(lista, u);
    guardarUsuariosJson(lista);
    return 0;    
}




void prestamosPorVencer(listaPrestamos* l){
    printf("\nResultados | Prestamos por vencer en los siguientes 3 dias:\n");
    Prestamo* aux = l->inicio;
    while (aux != NULL)
    {
        //si el prestamo esta activo y faltan 3 dias o menos para que venza
        if (calcularDiferenciaEnDias(fechaActual(), l->fechaFin)<=3 && l->estado == 1){
            // identificador de préstamo, usuario, fecha de prestamo, nombre e identificador de ejemplar.
            printf("\nDetalles del Prestamo:\n");
            printf("\tPrestamo N°: %d\n", aux->id);
            printf("\tUsuario: (%d) %s\n", aux->idUsuario, aux->usuario);
            printf("\tFecha de prestamo:  %s\n", aux->fechaInicio);
            printf("\tNombre:  %s\n", aux->nombreEjemplar);
            printf("\tIdentificador:  %d\n\n", aux->idEjemplar);
        }
        aux = aux->sig;
    }
}
#include "manejoJson.h"

int main(){
    listaUsuarios * lista = calloc(1, sizeof(listaUsuarios));
    leerUsuarios(lista);

    addUsuario(lista, "Juana", "Por alla");
    addUsuario(lista, "Pedro", "Por alla");

    guardarUsuariosJson(lista);
    return 0;    
}
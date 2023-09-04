#include "manejoJson.h"

int main(){
    listaUsuarios * lista = calloc(1, sizeof(listaUsuarios));
    leerUsuarios(lista);

    addUsuario(lista, "Juan", "Por alla");
    addUsuario(lista, "Pedro", "Por alla");

    guardarUsuariosJson(lista);
    return 0;    
}
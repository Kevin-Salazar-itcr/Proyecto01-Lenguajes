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
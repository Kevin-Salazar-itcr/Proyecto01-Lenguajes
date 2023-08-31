#include <string.h> // strcmp
#include <stdlib.h> // malloc

typedef struct Libro {
    char nombre[50];
    char autor[50];
    int anio;
    char genero[50];
    char resumen[500];
    int cantidad;
    struct Libro* sig;
};

typedef struct listaLibros {
    Libro* inicio;
    int tam;
};

listaLibros* crearListaLibros(){
    listaLibros* lista = calloc(1, sizeof(listaLibros));
    lista->inicio = NULL;
    lista->tam = 0;
    return lista;
}

void addLibro(listaLibros* lista, Libro* libro){
    if(lista->inicio == NULL){
        lista->inicio = libro;
    }else{
        Libro* aux = lista->inicio;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = libro;
    }
    lista->tam++;
}

Libro* buscarLibro(listaLibros* lista, char* nombre){
    Libro* aux = lista->inicio;
    while(aux != NULL){
        if(strcmp(aux->nombre, nombre) == 0){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
//********************************************************************************
typedef struct Usuario{
  int id;
  char nombre[50];
  char direccion[100]; 
  struct Usuario* sig;
};

typedef struct listaUsuarios{
  Usuario* inicio;
  int tam;
};

listaUsuarios* crearListaUsuarios(){
  listaUsuarios* lista = calloc(1, sizeof(listaUsuarios));
  lista->inicio = NULL;
  lista->tam = 0;
  return lista;
}

void addUsuario(listaUsuarios* lista, Usuario* usuario){
    if(lista->inicio == NULL){
        lista->inicio = usuario;
    }else{
        Usuario* aux = lista->inicio;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = usuario;
    }
    lista->tam++;
}

Usuario* buscarUsuario(listaUsuarios* lista, int id){
    Usuario* aux = lista->inicio;
    while(aux != NULL){
        if(id == aux->id){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
//********************************************************************************
typedef struct Prestamo{
  int id;
  char* usuario;
  char* nombreEjemplar;
  int idEjemplar;
  char* fechaInicio; 
  char* fechaFin;
  int estado;
  char* fechaDevolucion;
  struct Prestamo* sig;
};

typedef struct listaPrestamos{
  Prestamo* inicio;
  int tam;
};

listaPrestamos* crearListaPrestamos(){
  listaPrestamos* lista = calloc(1, sizeof(listaPrestamos));
  lista->inicio = NULL;
  lista->tam = 0;
  return lista;
}

void addPrestamo(listaPrestamos* lista, Prestamo* prestamo){
    if(lista->inicio == NULL){
        lista->inicio = prestamo;
    }else{
        Prestamo* aux = lista->inicio;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = prestamo;
    }
    lista->tam++;
}

Prestamo* buscarPrestamo(listaPrestamos* lista, int id){
    Prestamo* aux = lista->inicio;
    while(aux != NULL){
        if(id == aux->id){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
//********************************************************************************
#include <string.h> // strcmp
#include <stdlib.h> // malloc

typedef struct Libro {
    int id;
    char* nombre;
    char* autor;
    int anio;
    char* genero;
    char* resumen;
    int cantidad;
    struct Libro* sig;
}Libro;

typedef struct listaLibros {
    Libro* inicio;
    int tam;
}listaLibros;

/**
 * @brief Crea una lista de libros
 * 
 * @return listaLibros* 
 */
listaLibros* crearListaLibros(){
    listaLibros* lista = calloc(1, sizeof(listaLibros));
    lista->inicio = NULL;
    lista->tam = 0;
    return lista;
}

/**
 * @brief Agrega un libro a la lista
 *
 * @param lista lista de libros
 * @param libro libro a agregar
 */
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

/**
 * @brief Busca un libro por nombre
 * 
 * @param lista lista de libros
 * @param nombre nombre a buscar
 * @return Libro* si se encuentra el libro, NULL si no se encuentra
 */
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

/**
 * @brief Busca un libro por id
 * 
 * @param lista lista de libros
 * @param id id a buscar
 * @return Libro* si se encuentra el libro, NULL si no se encuentra
 */
Libro* buscarLibroXid(listaLibros* lista, int id){
    Libro* aux = lista->inicio;
    while(aux != NULL){
        if(id == aux->id){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}
//********************************************************************************
typedef struct Usuario{
  int id;
  char *nombre;
  char *direccion; 
  struct Usuario* sig;
}Usuario;


typedef struct listaUsuarios{
  Usuario* inicio;
  int tam;
}listaUsuarios;

/**
 * @brief Crea una lista de usuarios
 * 
 * @return listaUsuarios* 
 */
listaUsuarios* crearListaUsuarios(){
  listaUsuarios* lista = calloc(1, sizeof(listaUsuarios));
  lista->inicio = NULL;
  lista->tam = 0;
  return lista;
}

/**
 * @brief Agrega un usuario a la lista
 *
 * @param lista lista de usuarios
 * @param usuario usuario a agregar
 */
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

/**
 * @brief Busca un usuario por nombre
 * 
 * @param lista lista de usuarios
 * @param nombre nombre a buscar
 * @return Usuario* si se encuentra el usuario, NULL si no se encuentra
 */
Usuario* buscarUsuario(listaUsuarios* lista, char* nombre){
    Usuario* aux = lista->inicio;
    while(aux != NULL){
        if(strcmp(aux->nombre, nombre) == 0){
            return aux;
        }
        aux = aux->sig;
    }
    return NULL;
}

/**
 * @brief Busca un usuario por id
 * 
 * @param lista lista de usuarios
 * @param id id a buscar
 * @return Usuario* si se encuentra el usuario, NULL si no se encuentra 
 */
Usuario* buscarUsuarioXid(listaUsuarios* lista, int id){
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
  int idUsuario;
  char* usuario;
  char* nombreEjemplar;
  int idEjemplar;
  char* fechaInicio; 
  char* fechaFin;
  int estado;
  char* fechaDevolucion;
  int monto;
  struct Prestamo* sig;
}Prestamo;

typedef struct listaPrestamos{
  Prestamo* inicio;
  int tam;
}listaPrestamos;

/**
 * @brief Crea una lista de prestamos
 * 
 * @return listaPrestamos* 
 */
listaPrestamos* crearListaPrestamos(){
  listaPrestamos* lista = calloc(1, sizeof(listaPrestamos));
  lista->inicio = NULL;
  lista->tam = 0;
  return lista;
}

/**
 * @brief Agrega un prestamo a la lista
 *
 * @param lista lista de prestamos
 * @param prestamo prestamo a agregar
 */
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

/**
 * @brief Busca un prestamo por id
 * 
 * @param lista lista de prestamos
 * @param id id a buscar
 * @return Prestamo* si se encuentra el prestamo, NULL si no se encuentra
 */
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
//struct auxiliar para opciones operativas
typedef struct NumeroAparicion {
  int numero;
  int apariciones;
} NumeroAparicion;

//struct auxiliar para opciones operativas
typedef struct Consulta{
    char* fecha;
    int monto;
} Consulta;
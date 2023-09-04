#include <stdio.h>
#include <json-c/json.h> //sudo apt install libjson-c-dev
#include "structs.h"
//como compilar en gcc
//gcc archivoPrincipal -ljson-c (eso ultimo tambien sirve en g++)

//**********************************************************************************************************************
//**********************************************************************************************************************
/**
 * @brief funcion para leer un archivo json y guardar los libros en una lista de libros
 * 
 * @param l lista de libros donde se guardaran los datos
 */
void leerLibros(listaLibros* l){
    FILE *fp;
    char buffer[2048];

    struct json_object *parsed_json; //objeto que contiene el json 
    struct json_object *obj; //objeto que contiene los datos del json (como el cursor que se mueve por el json)

    //datos que se quieren extraer del json (ej: id, nombre, etc)
    struct json_object *id;
    struct json_object *nombre;
    struct json_object *autor;
    struct json_object *anio;
    struct json_object *genero;
    struct json_object *resumen;
    struct json_object *cantidad;
    size_t n,i;

    fp = fopen("datos/libros.json", "r"); //abrir archivo en modo lectura
    fread(buffer, 2048, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    n = json_object_array_length(parsed_json);

    for(i = 0; i < n; i++){
            Libro* lib = calloc(1, sizeof(Libro));

            obj = json_object_array_get_idx(parsed_json, i);
            json_object_object_get_ex(obj, "id", &id); //extraer el id
            json_object_object_get_ex(obj, "nombre", &nombre); //extraer el nombre
            json_object_object_get_ex(obj, "autor", &autor); //extraer el autor
            json_object_object_get_ex(obj, "anio", &anio); //extraer el anio
            json_object_object_get_ex(obj, "genero", &genero); //extraer el genero
            json_object_object_get_ex(obj, "resumen", &resumen); //extraer el resumen
            json_object_object_get_ex(obj, "cantidad", &cantidad); //extraer la cantidad

            lib->id = json_object_get_int(id);
            strcpy(lib->nombre, json_object_get_string(nombre));
            strcpy(lib->autor, json_object_get_string(autor));
            lib->anio = json_object_get_int(anio);
            strcpy(lib->genero, json_object_get_string(genero));
            strcpy(lib->resumen, json_object_get_string(resumen));
            lib->cantidad = json_object_get_int(cantidad);
            addLibro(l, lib);
    }
}

/**
 * @brief funcion para leer un archivo json y guardar los usuarios en una lista de usuarios
 * 
 * @param l lista de usuarios donde se guardaran los datos
 */
void leerUsuarios(listaUsuarios* l){
    //los usuarios tienen id nombre y direccion
    FILE *fp;
    char buffer[2048];

    struct json_object *parsed_json; //objeto que contiene el json 
    struct json_object *obj; //objeto que contiene los datos del json (como el cursor que se mueve por el json)

    struct json_object *nombre;
    struct json_object *direccion;
    size_t n,i;

    fp = fopen("datos/usuarios.json", "r"); //abrir archivo en modo lectura
    fread(buffer, 2048, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    n = json_object_array_length(parsed_json);

    for(i = 0; i < n; i++){
            Usuario* user = calloc(1, sizeof(Usuario));

            obj = json_object_array_get_idx(parsed_json, i);
            json_object_object_get_ex(obj, "nombre", &nombre); //extraer el nombre
            json_object_object_get_ex(obj, "direccion", &direccion); //extraer la direccion

            addUsuario(l, json_object_get_string(nombre), json_object_get_string(direccion));
    }
}

/**
 * @brief funcion para leer un archivo json y guardar los prestamos en una lista de prestamos
 * 
 * @param l lista de prestamos donde se guardaran los datos
 */
void leerPrestamo(listaPrestamos* l){
    FILE *fp;
    char buffer[2048];

    struct json_object *parsed_json; //objeto que contiene el json 
    struct json_object *obj; //objeto que contiene los datos del json (como el cursor que se mueve por el json)

    //datos que se quieren extraer del json (ej: id, nombre, etc)
    struct json_object *id;
    struct json_object *usuario;
    struct json_object *nombreEjemplar;
    struct json_object *idEjemplar;
    struct json_object *fechaInicio;
    struct json_object *fechaFin;
    struct json_object *estado;
    struct json_object *fechaDevolucion;
    size_t n,i;

    fp = fopen("datos/prestamos.json", "r"); //abrir archivo en modo lectura
    fread(buffer, 2048, 1, fp);
    fclose(fp);

    parsed_json = json_tokener_parse(buffer);
    n = json_object_array_length(parsed_json);

    for(i = 0; i < n; i++){
        Prestamo* pres = calloc(1, sizeof(Prestamo));

        obj = json_object_array_get_idx(parsed_json, i);
        json_object_object_get_ex(obj, "id", &id); //extraer el id
        json_object_object_get_ex(obj, "usuario", &usuario); //extraer el usuario
        json_object_object_get_ex(obj, "nombreEjemplar", &nombreEjemplar); //extraer el nombreEjemplar
        json_object_object_get_ex(obj, "idEjemplar", &idEjemplar); //extraer el idEjemplar
        json_object_object_get_ex(obj, "fechaInicio", &fechaInicio); //extraer la fechaInicio
        json_object_object_get_ex(obj, "fechaFin", &fechaFin); //extraer la fechaFin
        json_object_object_get_ex(obj, "estado", &estado); //extraer el estado
        json_object_object_get_ex(obj, "fechaDevolucion", &fechaDevolucion); //extraer la fechaDevolucion

        pres->id = json_object_get_int(id);
        strcpy(pres->usuario, json_object_get_string(usuario));
        strcpy(pres->nombreEjemplar, json_object_get_string(nombreEjemplar));
        pres->idEjemplar = json_object_get_int(idEjemplar);
        strcpy(pres->fechaInicio, json_object_get_string(fechaInicio));
        strcpy(pres->fechaFin, json_object_get_string(fechaFin));
        pres->estado = json_object_get_int(estado);
        strcpy(pres->fechaDevolucion, json_object_get_string(fechaDevolucion));
    }
}    

//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************
//**********************************************************************************************************************

void guardarLibrosJson(listaLibros* l) { //puede editarse y recibir parametros para guardar en el json (ej un struct o lista de structs)
    struct json_object *json_array = json_object_new_array();

    Libro* aux = l->inicio;
    // Recorrer la lista de libros y guardarlos en el objeto json
    while(aux != NULL){
        struct json_object *obj = json_object_new_object();
        json_object_object_add(obj, "id", json_object_new_int(aux->id)); 
        json_object_object_add(obj, "nombre", json_object_new_string(aux->nombre)); 
        json_object_object_add(obj, "autor", json_object_new_string(aux->autor)); 
        json_object_object_add(obj, "anio", json_object_new_int(aux->anio)); 
        json_object_object_add(obj, "genero", json_object_new_string(aux->genero)); 
        json_object_object_add(obj, "resumen", json_object_new_string(aux->resumen)); 
        json_object_object_add(obj, "cantidad", json_object_new_int(aux->cantidad)); 

        json_object_array_add(json_array, obj);
    }
    
    const char *json_str = json_object_to_json_string(json_array); // Convertir a string el objeto json

    // Guardar o sobreescribir en un archivo .json
    FILE *file = fopen("datos/libros.json", "w");//guardar en un archivo .json en modo escritura
    if (file) {
        fprintf(file, "%s", json_str);
        fclose(file);
        printf("Archivo guardado correctamente'\n");
    } else {
        printf("Error al guardar.\n");
    }

    json_object_put(json_array); // Liberar memoria
}

void guardarUsuariosJson(listaUsuarios* l){
    struct json_object *json_array = json_object_new_array();

    Usuario* aux = l->inicio;
    // Recorrer la lista de libros y guardarlos en el objeto json
    while(aux != NULL){
        struct json_object *obj = json_object_new_object();
        json_object_object_add(obj, "id", json_object_new_int(aux->id)); 
        json_object_object_add(obj, "nombre", json_object_new_string(aux->nombre)); 
        json_object_object_add(obj, "direccion", json_object_new_string(aux->direccion)); 

        json_object_array_add(json_array, obj);
    }
    
    const char *json_str = json_object_to_json_string(json_array); // Convertir a string el objeto json

    // Guardar o sobreescribir en un archivo .json
    FILE *file = fopen("datos/usuarios.json", "w");//guardar en un archivo .json en modo escritura
    if (file) {
        fprintf(file, "%s", json_str);
        fclose(file);
        printf("Archivo guardado correctamente'\n");
    } else {
        printf("Error al guardar.\n");
    }

    json_object_put(json_array); // Liberar memoria
}

void guardarPrestamosJson(listaPrestamos* l){
    struct json_object *json_array = json_object_new_array();

    Prestamo* aux = l->inicio;
    // Recorrer la lista de libros y guardarlos en el objeto json
    while(aux != NULL){
        struct json_object *obj = json_object_new_object();
        json_object_object_add(obj, "id", json_object_new_int(aux->id)); 
        json_object_object_add(obj, "usuario", json_object_new_string(aux->usuario)); 
        json_object_object_add(obj, "nombreEjemplar", json_object_new_string(aux->nombreEjemplar)); 
        json_object_object_add(obj, "idEjemplar", json_object_new_int(aux->idEjemplar)); 
        json_object_object_add(obj, "fechaInicio", json_object_new_string(aux->fechaInicio)); 
        json_object_object_add(obj, "fechaFin", json_object_new_string(aux->fechaFin)); 
        json_object_object_add(obj, "estado", json_object_new_int(aux->estado)); 
        json_object_object_add(obj, "fechaDevolucion", json_object_new_string(aux->fechaDevolucion)); 

        json_object_array_add(json_array, obj);
    }
    
    const char *json_str = json_object_to_json_string(json_array); // Convertir a string el objeto json

    // Guardar o sobreescribir en un archivo .json
    FILE *file = fopen("datos/prestamos.json", "w");//guardar en un archivo .json en modo escritura
    if (file) {
        fprintf(file, "%s", json_str);
        fclose(file);
        printf("Archivo guardado correctamente'\n");
    } else {
        printf("Error al guardar.\n");
    }

    json_object_put(json_array); // Liberar memoria
}
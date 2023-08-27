#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h> //sudo apt install libjson-c-dev
//como compilar en gcc
//gcc archivoPrincipal -ljson-c (eso ultimo tambien sirve en g++)

/**
 * @brief Guarda un archivo .json con los datos que recibe como parametro
 * 
 * @param nombreArchivo el nombre del archivo a guardar (sin la extension .json)
 * hace falta otro parametro que seria el struct donde se guardaría la info del json
 */
void guardarJson(char* nombreArchivo) { //puede editarse y recibir parametros para guardar en el json (ej un struct o lista de structs)
    struct json_object *json_array = json_object_new_array();

    // Agregar objetos al array
    for (int i = 0; i < 4; i++) {
        struct json_object *obj = json_object_new_object();
        json_object_object_add(obj, "age", json_object_new_int(10+i+4)); //el id en cuestion
        json_object_object_add(obj, "name", json_object_new_string("yo")); //el o los datos que se quieren guardar
        //...         el o los datos que se quieren guardar
        json_object_array_add(json_array, obj);
    }

    const char *json_str = json_object_to_json_string(json_array); // Convertir a string el objeto json

    // Guardar en un archivo .json
    FILE *file = fopen(nombreArchivo+".json", "w");//guardar en un archivo .json en modo escritura
    if (file) {
        fprintf(file, "%s", json_str);
        fclose(file);
        printf("Archivo guardado correctamente'\n");
    } else {
        printf("Error al guardar.\n");
    }

    json_object_put(json_array); // Liberar memoria
}

//**********************************************************************************************************************

/**
 * @brief Lee un archivo .json y...
 * 
 * @param archivo el nombre del archivo a leer (sin la extension .json)
 * hace falta otro parametro que seria el struct donde se guardaría la info del json
 */
void leerJson(char* archivo) { //puede editarse y recibir parametros para guardar el json (ej un struct o lista de structs)
        FILE *fp;
        char buffer[1024];

        struct json_object *parsed_json; //objeto que contiene el json 
        struct json_object *obj; //objeto que contiene los datos del json (como el cursor que se mueve por el json)

        //datos que se quieren extraer del json (ej: id, nombre, etc)
        struct json_object *name;
        struct json_object *id;
        size_t n,i;

        fp = fopen(archivo+".json", "r"); //abrir archivo en modo lectura
        fread(buffer, 1024, 1, fp);
        fclose(fp);

        parsed_json = json_tokener_parse(buffer);
        n = json_object_array_length(parsed_json);

        for(i = 0; i<n; i++){
                obj = json_object_array_get_idx(parsed_json, i);
                json_object_object_get_ex(obj, "id", &id); //extraer el id
                json_object_object_get_ex(obj, "nombre", &name); //extraer el nombre
                //.. de la misma forma se pueden extraer los demas datos que se quieran

                printf("id: %d, nombre: %s\n", json_object_get_int(id), json_object_get_string(name));
                //en lugar de imprimir se puede guardar en una lista o struct para su posterior uso, recibiendo dicha lista o struct como parametro
        }
}
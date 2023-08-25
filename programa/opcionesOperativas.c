#include <stdio.h>
#include <string.h>
#include <structs.h>

struct Usuario incluir_Usuario()
{
    struct Usuario usuario;
    
    printf("Ingrese la identificacion del usuario: ");
    scanf("%d", &usuario.id);

    printf("Ingrese el nombre del usuario: ");
    scanf(" %s", usuario.nombre);
    printf("Ingrese la direccion del usuario: ");
    scanf(" %s", usuario.direccion);
    
    return usuario;
};


int recuperarLibrosTxt() {
    
    struct Libro Libros[100];
    
    int indiceLibros = 0;
    
    FILE *archivo = fopen("doc.txt", "r");
    char linea[200];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        
        struct Libro libro;
        
        char *palabra = strtok(linea, "|");
        strcpy(libro.nombre, palabra);
        
        palabra = strtok(NULL, "|");
        strcpy(libro.autor, palabra);
        
        palabra = strtok(NULL, "|");
        libro.anio = strtol(palabra, NULL, 10);
        
        palabra = strtok(NULL, "|");
        strcpy(libro.genero, palabra);
        
        palabra = strtok(NULL, "|");
        strcpy(libro.resumen, palabra);
        
        palabra = strtok(NULL, "|");
        libro.cantidad = strtol(palabra, NULL, 10);
        
        printf("Título: %s\n", libro.nombre);
        printf("Autor: %s\n", libro.autor);
        printf("Año: %d\n", libro.anio);
        printf("Género: %s\n", libro.genero);
        printf("Descripción: %s\n", libro.resumen);
        printf("Disponibles: %d\n", libro.cantidad);
        Libros[indiceLibros] = libro;
        
        printf("\n");
    }
    
    fclose(archivo);
    
    incluir_Usuario();
    
    return 0;
}

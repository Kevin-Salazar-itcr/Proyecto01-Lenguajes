#include <stdio.h>
#include <string.h>

struct Prestamo incluir_Prestamo()
{
    struct Prestamo Prestamo;
    
    printf("Ingrese el id del prestamo: ");
    scanf("%d", &Prestamo.id);
    printf("Ingrese el nombre del usuario: ");
    scanf("%s", Prestamo.usuario);
    printf("Ingrese el estado del prestamo: ");
    scanf("%d", &Prestamo.estado);
    printf("Ingrese el nombre del libro: ");
    scanf("%s", Prestamo.nombre);
    printf("Ingrese la fecha de inicio del prestamo: ");
    scanf("%s", Prestamo.fechaInicio);
    printf("Ingrese la fecha de fin del prestamo: ");
    scanf("%s", Prestamo.fechaFin);

    return Prestamo;

};


void mostrarPrestamosRango()
{

    char fechaInicio[11];
    char fechaFin[11];

    int indice = 0;

    printf("Ingrese la fecha de inicio: ");
    scanf("%s", fechaInicio);
    printf("Ingrese la fecha de fin: ");
    scanf("%s", fechaFin);

    for (int i = 0; i < indice; i++)
    {
        if (strcmp(prestamos[i].fechaPedido, fechaInicio) >= 0 && strcmp(prestamos[i].fechaRecibido, fechaFin) <= 0)
        {
            printf("\nDetalles del Prestamo:\n");
            printf("Id: %d\n", prestamos[i].id);
            printf("Usuario: %s\n", prestamos[i].usuario);
            printf("Estado: %d\n", prestamos[i].estado);
            printf("Nombre: %s\n", prestamos[i].nombre);
            printf("Fecha de inicio: %s\n", prestamos[i].fechaInicio);
            printf("Fecha de fin: %s\n", prestamos[i].fechaFin);

        }
    };

};


struct Prestamo incluir_Prestamo()
{
    struct Prestamo Prestamo;
    
    printf("Ingrese la identificacion del usuario: ");
    scanf("%d", &usuario.id);

    printf("Ingrese el nombre del usuario: ");
    scanf(" %s", usuario.nombre);
    printf("Ingrese la direccion del usuario: ");
    scanf(" %s", usuario.direccion);
    
    return usuario;
};





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
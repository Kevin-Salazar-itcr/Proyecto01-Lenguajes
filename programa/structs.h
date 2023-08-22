#include <stdio.h>

struct Libro {
    char nombre[50];
    char autor[50];
    int anio;
    char genero[50];
    char resumen[500];
    int cantidad;
};

struct Usuario{
  int id;
  char nombre[50];
  char direccion[100]; 
};

struct Prestamo{
  int id;
  char usuario[50];
  int estado; 
  char nombre[50];
  int idLibro;
  int tardia;
  int inicio;
  int fin;
};

 





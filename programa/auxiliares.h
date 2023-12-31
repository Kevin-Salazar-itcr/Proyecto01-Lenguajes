#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

/**
 * @brief funcion auxiliar para obtener el largo de una cadena
 * 
 * @param cadena cadena de caracteres
 * @return int el largo de la cadena
 */
int largo(char *cadena)
{
    int i = 0;
    while (cadena[i] != '\0')
    {
        i++;
    }
    return i;
}

/**
 * @brief funcion que busca coincidencias de un texto en un archivo
 * @param cadena texto donde se quiere buscar una coincidencia
 * @param coincidencia texto a buscar
 * @return la cantidad de coincidencias encontradas
 */
int buscarCoincidencias(char *cadena, char *coincidencia) {
    int largoCadena = largo(cadena);
    int largoCoincidencia = largo(coincidencia);
    
    int resultado = 0;
    int i = 0;  // Índice para recorrer la cadena original
    
    while (i < largoCadena)
    {
        int coincide = 1;  // Variable para verificar si hay coincidencia
        for (int k = 0; k < largoCoincidencia; k++)
        {
            if (cadena[i + k] != coincidencia[k])
            {
                coincide = 0;
                break;
            }
        }

        if (coincide)
        {
            resultado++;
            i += largoCoincidencia;
        }else{
            i++;
        }
    }

    return resultado;
}

/**
 * @brief funcion auxiliar para obtener la fecha actual
 * @return fecha actual en formato dd/mm/aaaa
 */
char* fechaActual(){
    time_t currentTime;
    struct tm *localTime;
    time(&currentTime);         // Obtiene el tiempo actual en segundos desde 1970
    localTime = localtime(&currentTime); // Convierte el tiempo en una estructura tm
    
    char* fecha = calloc(15, sizeof(char));
    sprintf(fecha, "%02d/%02d/%04d", localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900);
    return fecha;
}

/**
 * @brief funcion auxiliar para saber si una fecha es valida
 * 
 * @param cadena la cadena que contiene la fecha
 * @return true si la fecha es valida
 * @return false si la fecha no es valida
 */
bool esFechaValida(char *cadena) {
    int dia, mes, anio;
    if (sscanf(cadena, "%d/%d/%d", &dia, &mes, &anio) != 3) {
        return false; // No se pudieron obtener tres valores enteros
    }

    if (mes < 1 || mes > 12 || dia < 1) {
        return false; // Mes y día fuera de rangos válidos
    }

    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            return dia <= 31; // Meses con 31 días
        case 4: case 6: case 9: case 11:
            return dia <= 30; // Meses con 30 días
        case 2:
            if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0)) {
                return dia <= 29; // Año bisiesto, febrero tiene 29 días
            } else {
                return dia <= 28; // Febrero tiene 28 días
            }
        default:
            return false; // Mes no válido
    }
}

/**
 * @brief funcion auxiliar para comparar dos fechas
 * 
 * @param fecha1 la primera fecha
 * @param fecha2 la segunda fecha
 * @return int 0 si las fechas son iguales, 1 si la primera fecha es mayor, -1 si la segunda fecha es mayor
 */
int compararFechas(char* fecha1, char* fecha2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    // Dividir la cadena de fecha1 en día, mes y año
    sscanf(fecha1, "%d/%d/%d", &dia1, &mes1, &ano1);

    // Dividir la cadena de fecha2 en día, mes y año
    sscanf(fecha2, "%d/%d/%d", &dia2, &mes2, &ano2);

    // Comparar años
    if (ano1 > ano2) {
        return 1;
    } else if (ano1 < ano2) {
        return -1;
    }

    // Comparar meses si los años son iguales
    if (mes1 > mes2) {
        return 1;
    } else if (mes1 < mes2) {
        return -1;
    }

    // Comparar días si los años y meses son iguales
    if (dia1 > dia2) {
        return 1;
    } else if (dia1 < dia2) {
        return -1;
    }

    // Las fechas son iguales
    return 0;
}

/**
 * @brief funcion auxiliar para calcular la diferencia en dias entre dos fechas
 * 
 * @param fecha1 la primera fecha
 * @param fecha2 la segunda fecha
 * @return int la diferencia absoluta en dias entre las dos fechas
 */
int calcularDiferenciaEnDias(char* fecha1, char* fecha2) {
    struct tm tm1 = {0};
    struct tm tm2 = {0};

    if (strptime(fecha1, "%d/%m/%Y", &tm1) == NULL || strptime(fecha2, "%d/%m/%Y", &tm2) == NULL) {
        fprintf(stderr, "Error: Formato de fecha incorrecto.\n");
        return -1; // Error
    }

    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);

    if (time1 == -1 || time2 == -1) {
        fprintf(stderr, "Error: No se pudo convertir la fecha en tiempo.\n");
        return -1; // Error
    }

    // Calcular la diferencia en segundos y convertirla a días
    int diferenciaEnSegundos = abs((int)difftime(time1, time2));
    int diferenciaEnDias = diferenciaEnSegundos / (60 * 60 * 24);

    return diferenciaEnDias;
}
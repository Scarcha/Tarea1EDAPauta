#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Estructura de datos para almacenar las notas (cantidad variable) de un alumno. Pensé en usar esto pero no quise modificar lo que ya estaba hecho en las instrucciones
typedef struct struct_notas {
    int nota;
    struct struct_notas *siguiente;
} struct_notas;

// Estructura de datos para almacenar la información de un alumno
typedef struct {
    char *nombre;
    char *apellido1;
    char *apellido2;
    char *rol;
    int *notas;
    int cantidad_notas; // <-- Agregué esto
    int promedio;
} struct_alumnos;


// Estructura de datos para almacenar la lista enlazada de alumnos
typedef struct struct_lista_alumnos{
    struct_alumnos *alumno;
    struct struct_lista_alumnos *siguiente;
} struct_lista_alumnos;

// Estructura de datos para almacenar el árbol binario de alumnos
typedef struct struct_arbol_alumnos {
    struct_alumnos *alumno;
    struct struct_arbol_alumnos *izquierda;
    struct struct_arbol_alumnos *derecha;
} struct_arbol_alumnos;


/**
 * @brief Imprime la lista de alumnos en la consola.
 *
 * Esta función recorre la lista enlazada de alumnos apuntada por 'cabeza'
 * y muestra la información de cada alumno en la salida estándar.
 *
 * @param cabeza Puntero a la cabeza de la lista de alumnos.
 */
void imprimir_lista(struct_lista_alumnos *cabeza);
/**
 * @brief Ordena una lista enlazada de alumnos según el promedio de cada alumno.
 *
 * Esta función toma la cabeza de una lista enlazada de estructuras de alumnos y
 * la ordena en orden ascendente o descendente (según implementación) basado en el
 * promedio de cada alumno.
 *
 * @param cabeza Puntero a la cabeza de la lista enlazada de alumnos.
 */
void ordenar_lista_por_promedio(struct_lista_alumnos *cabeza);
struct_arbol_alumnos* insertar_en_arbol(struct_arbol_alumnos *raiz, struct_alumnos *alumno);
void imprimir_arbol(struct_arbol_alumnos *raiz);
void liberar_lista(struct_lista_alumnos *cabeza);
void liberar_arbol(struct_arbol_alumnos *raiz);
void guardar_lista_txt(struct_lista_alumnos *cabeza, const char *nombre_archivo);
void guardar_arbol_archivo(struct_arbol_alumnos *raiz, const char *nombre_archivo);
int contar_alumnos_lista(struct_lista_alumnos *cabeza);
int contar_alumnos_arbol(struct_arbol_alumnos *raiz);
void promedio_desviacion_lista(struct_lista_alumnos *cabeza);
void promedio_desviacion_arbol(struct_arbol_alumnos *raiz, int n_eval);
void promedio_final_lista(struct_lista_alumnos *cabeza);
void promedio_final_arbol(struct_arbol_alumnos *raiz);
struct_alumnos* buscar_por_rol_lista(struct_lista_alumnos *cabeza, const char *rol);
struct_alumnos* buscar_por_rol_arbol(struct_arbol_alumnos *raiz, const char *rol);
void imprimir_datos_alumno(struct_alumnos *alumno);
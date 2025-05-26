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
/**
 * Inserta un nodo de alumno en el árbol de alumnos.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos.
 * @param alumno Puntero a la estructura del alumno a insertar.
 * @return Puntero a la nueva raíz del árbol tras la inserción.
 */
struct_arbol_alumnos* insertar_en_arbol(struct_arbol_alumnos *raiz, struct_alumnos *alumno);
/**
 * @brief Imprime en consola los elementos del árbol de alumnos.
 *
 * Esta función recorre el árbol binario de alumnos apuntado por 'raiz'
 * e imprime la información de cada nodo en el orden especificado (por ejemplo, inorden).
 *
 * @param raiz Puntero a la raíz del árbol de alumnos (struct_arbol_alumnos*).
 */
void imprimir_arbol(struct_arbol_alumnos *raiz);
/**
 * @brief Libera la memoria ocupada por una lista enlazada de alumnos.
 *
 * Esta función recorre la lista enlazada de alumnos comenzando desde la cabeza
 * y libera la memoria de cada nodo, evitando fugas de memoria.
 *
 * @param cabeza Puntero al primer nodo de la lista de alumnos.
 */
void liberar_lista(struct_lista_alumnos *cabeza);
/**
 * @brief Libera la memoria ocupada por un árbol de alumnos.
 *
 * Esta función recorre el árbol de alumnos apuntado por 'raiz' y libera
 * recursivamente toda la memoria asignada a sus nodos.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos a liberar.
 */
void liberar_arbol(struct_arbol_alumnos *raiz);
/**
 * @brief Guarda la lista de alumnos en un archivo de texto.
 *
 * Esta función recorre la lista enlazada de alumnos y escribe sus datos en el archivo especificado.
 *
 * @param cabeza Puntero a la cabeza de la lista de alumnos.
 * @param nombre_archivo Nombre del archivo de texto donde se guardará la lista.
 */
void guardar_lista_txt(struct_lista_alumnos *cabeza, const char *nombre_archivo);
/**
 * @brief Guarda el árbol de alumnos en un archivo.
 *
 * Esta función recorre el árbol binario de alumnos apuntado por 'raiz' y guarda su contenido
 * en el archivo especificado por 'nombre_archivo'. El formato de almacenamiento depende de la
 * implementación de la función.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos.
 * @param nombre_archivo Nombre del archivo donde se guardará el árbol.
 */
void guardar_arbol_archivo(struct_arbol_alumnos *raiz, const char *nombre_archivo);
/**
 * @brief Cuenta la cantidad de alumnos en una lista enlazada.
 *
 * Esta función recorre la lista enlazada de alumnos comenzando desde la cabeza
 * y retorna el número total de nodos (alumnos) presentes en la lista.
 *
 * @param cabeza Puntero a la cabeza de la lista enlazada de alumnos.
 * @return int Número de alumnos en la lista.
 */
int contar_alumnos_lista(struct_lista_alumnos *cabeza);
/**
 * @brief Cuenta la cantidad de alumnos en un árbol de alumnos.
 *
 * Esta función recorre el árbol binario de alumnos apuntado por 'raiz' y retorna
 * el número total de nodos (alumnos) presentes en el árbol.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos (struct_arbol_alumnos).
 * @return int Número total de alumnos en el árbol.
 */
int contar_alumnos_arbol(struct_arbol_alumnos *raiz);
/**
 * Calcula y muestra el promedio y la desviación estándar de las calificaciones
 * de los alumnos en la lista enlazada proporcionada.
 *
 * @param cabeza Puntero a la cabeza de la lista enlazada de alumnos.
 */
void promedio_desviacion_lista(struct_lista_alumnos *cabeza);
/**
 * Calcula y muestra el promedio y la desviación estándar de las evaluaciones de los alumnos
 * almacenados en el árbol binario.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos (struct_arbol_alumnos).
 * @param n_eval Número de evaluaciones a considerar para el cálculo.
 */
void promedio_desviacion_arbol(struct_arbol_alumnos *raiz);
/**
 * @brief Calcula y muestra el promedio final de los alumnos en la lista.
 *
 * Esta función recorre la lista enlazada de alumnos apuntada por 'cabeza',
 * calcula el promedio final de cada alumno y lo muestra por pantalla.
 *
 * @param cabeza Puntero a la cabeza de la lista enlazada de alumnos.
 */
void promedio_final_lista(struct_lista_alumnos *cabeza);
/**
 * Calcula y muestra el promedio final de los alumnos almacenados en el árbol.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos (struct_arbol_alumnos).
 *
 * Esta función recorre el árbol de alumnos y calcula el promedio final de todos los alumnos.
 * El resultado puede ser mostrado por pantalla o utilizado para otros fines según la implementación.
 */
void promedio_final_arbol(struct_arbol_alumnos *raiz);
/**
 * Busca un alumno en una lista enlazada de alumnos por su número de rol.
 *
 * @param cabeza Puntero a la cabeza de la lista de alumnos.
 * @param rol Cadena de caracteres que representa el número de rol a buscar.
 * @return Puntero a la estructura del alumno si se encuentra, o NULL si no se encuentra.
 */
struct_alumnos* buscar_por_rol_lista(struct_lista_alumnos *cabeza, const char *rol);
/**
 * Busca un alumno en un árbol binario de alumnos por su número de rol.
 *
 * @param raiz Puntero a la raíz del árbol de alumnos.
 * @param rol Cadena de caracteres que representa el número de rol a buscar.
 * @return Puntero a la estructura struct_alumnos correspondiente al alumno encontrado,
 *         o NULL si no se encuentra ningún alumno con el rol especificado.
 */
struct_alumnos* buscar_por_rol_arbol(struct_arbol_alumnos *raiz, const char *rol);
/**
 * @brief Imprime los datos de un alumno en la salida estándar.
 *
 * Esta función recibe un puntero a una estructura de tipo struct_alumnos
 * y muestra en pantalla la información almacenada en dicha estructura.
 *
 * @param alumno Puntero a la estructura struct_alumnos que contiene los datos del alumno a imprimir.
 */
void imprimir_datos_alumno(struct_alumnos *alumno);
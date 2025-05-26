#include <string.h>
#include "funciones.h"

// Imprime contenido de la lista enlazada
void imprimir_lista(struct_lista_alumnos *cabeza) {
    struct_lista_alumnos *actual = cabeza;
    while (actual != NULL) {
        printf("Nombre: %s %s %s\n", 
            actual->alumno->nombre, 
            actual->alumno->apellido1, 
            actual->alumno->apellido2);
        printf("Rol: %s\n", actual->alumno->rol);

        printf("Notas: ");
        int i;
        for (i = 0; i < actual->alumno->cantidad_notas; i++) {
            printf("%d ", actual->alumno->notas[i]);
        }
        printf("\nPromedio: %d\n", actual->alumno->promedio);
        printf("----------------------\n");
        actual = actual->siguiente;
    }
}

// Ordena la lista enlazada de mayor a menor promedio 
void ordenar_lista_por_promedio(struct_lista_alumnos *cabeza) {
    struct_lista_alumnos *i;
    for (i = cabeza; i != NULL; i = i->siguiente) {
        struct_lista_alumnos *j;
        for (j = i->siguiente; j != NULL; j = j->siguiente) {
            if (i->alumno->promedio < j->alumno->promedio) {
                struct_alumnos *tmp = i->alumno;
                i->alumno = j->alumno;
                j->alumno = tmp;
            }
        }
    }
}

// Inserta un alumno en el árbol binario por promedio
struct_arbol_alumnos* insertar_en_arbol(struct_arbol_alumnos *raiz, struct_alumnos *alumno) {
    if (raiz == NULL) {
        struct_arbol_alumnos *nuevo = malloc(sizeof(struct_arbol_alumnos));
        nuevo->alumno = alumno;
        nuevo->izquierda = NULL;
        nuevo->derecha = NULL;
        return nuevo;
    }
    if (alumno->promedio < raiz->alumno->promedio) {
        raiz->izquierda = insertar_en_arbol(raiz->izquierda, alumno);
    } else {
        raiz->derecha = insertar_en_arbol(raiz->derecha, alumno);
    }
    return raiz;
}

// Impirme el árbol binario
void imprimir_arbol(struct_arbol_alumnos *raiz) {
    if (raiz == NULL) return;
    // Primero el subárbol derecho (mayores promedios)
    imprimir_arbol(raiz->derecha);

    // Imprimir datos del alumno
    printf("Nombre: %s %s %s\n", 
        raiz->alumno->nombre, 
        raiz->alumno->apellido1, 
        raiz->alumno->apellido2);
    printf("Rol: %s\n", raiz->alumno->rol);
    printf("Notas: ");
    int i;
    for (i = 0; i < raiz->alumno->cantidad_notas; i++) {
        printf("%d ", raiz->alumno->notas[i]);
    }
    printf("\nPromedio: %d\n", raiz->alumno->promedio);
    printf("----------------------\n");

    // Luego el subárbol izquierdo (menores promedios)
    imprimir_arbol(raiz->izquierda);
}

void liberar_lista(struct_lista_alumnos *cabeza) {
    struct_lista_alumnos *actual = cabeza;
    while (actual != NULL) {
        struct_lista_alumnos *siguiente = actual->siguiente;
        // Liberar campos de alumno
        free(actual->alumno->nombre);
        free(actual->alumno->apellido1);
        free(actual->alumno->apellido2);
        free(actual->alumno->rol);
        free(actual->alumno->notas);
        free(actual->alumno);
        free(actual);
        actual = siguiente;
    }
}

void liberar_arbol(struct_arbol_alumnos *raiz) {
    if (raiz == NULL) return;
    liberar_arbol(raiz->izquierda);
    liberar_arbol(raiz->derecha);
    // No liberar alumno aquí si ya lo liberaste en la lista
    free(raiz);
}

void guardar_lista_txt(struct_lista_alumnos *cabeza, const char *nombre_archivo) {
    FILE *f = fopen(nombre_archivo, "w");
    if (!f) return;
    struct_lista_alumnos *actual = cabeza;
    while (actual) {
        fprintf(f, "%s %s %s %s %d\n",
            actual->alumno->rol,
            actual->alumno->nombre,
            actual->alumno->apellido1,
            actual->alumno->apellido2,
            actual->alumno->promedio
        );
        actual = actual->siguiente;
    }
    fclose(f);
}

void guardar_arbol_txt(struct_arbol_alumnos *raiz, FILE *f) {
    if (!raiz) return;
    guardar_arbol_txt(raiz->derecha, f); // primero los mayores
    fprintf(f, "%s %s %s %s %d\n",
        raiz->alumno->rol,
        raiz->alumno->nombre,
        raiz->alumno->apellido1,
        raiz->alumno->apellido2,
        raiz->alumno->promedio
    );
    guardar_arbol_txt(raiz->izquierda, f);
}

void guardar_arbol_archivo(struct_arbol_alumnos *raiz, const char *nombre_archivo) {
    FILE *f = fopen(nombre_archivo, "w");
    if (!f) return;
    guardar_arbol_txt(raiz, f);
    fclose(f);
}

// Contar alumnos en la lista
int contar_alumnos_lista(struct_lista_alumnos *cabeza) {
    int count = 0;
    while (cabeza) {
        count++;
        cabeza = cabeza->siguiente;
    }
    return count;
}

// Contar alumnos en el árbol
int contar_alumnos_arbol(struct_arbol_alumnos *raiz) {
    if (!raiz) return 0;
    return 1 + contar_alumnos_arbol(raiz->izquierda) + contar_alumnos_arbol(raiz->derecha);
}

// Promedio y desviación estándar de cada evaluación en la lista
void promedio_desviacion_lista(struct_lista_alumnos *cabeza) {
    if (!cabeza) return;
    int n_eval = cabeza->alumno->cantidad_notas;
    double *suma = calloc(n_eval, sizeof(double));
    double *suma2 = calloc(n_eval, sizeof(double));
    int n = 0;
    struct_lista_alumnos *act;
    for (act = cabeza; act; act = act->siguiente) {
        int i;
        for (i = 0; i < n_eval; i++) {
            suma[i] += act->alumno->notas[i];
            suma2[i] += act->alumno->notas[i] * act->alumno->notas[i];
        }
        n++;
    }
    int i;
    for (i = 0; i < n_eval; i++) {
        double prom = suma[i] / n;
        double desv = sqrt(suma2[i]/n - prom*prom);
        printf("Evaluación %d: Promedio = %.2f, Desviación = %.2f\n", i+1, prom, desv);
    }
    free(suma); free(suma2);
}

// Promedio y desviación estándar de cada evaluación en el árbol
static void acum_eval_arbol(struct_arbol_alumnos *raiz, int n_eval, double *suma, double *suma2, int *n) {
    if (!raiz) return;
    acum_eval_arbol(raiz->izquierda, n_eval, suma, suma2, n);
    int i;
    for (i = 0; i < n_eval; i++) {
        suma[i] += raiz->alumno->notas[i];
        suma2[i] += raiz->alumno->notas[i] * raiz->alumno->notas[i];
    }
    (*n)++;
    acum_eval_arbol(raiz->derecha, n_eval, suma, suma2, n);
}
void promedio_desviacion_arbol(struct_arbol_alumnos *raiz, int n_eval) {
    double *suma = calloc(n_eval, sizeof(double));
    double *suma2 = calloc(n_eval, sizeof(double));
    int n = 0;
    acum_eval_arbol(raiz, n_eval, suma, suma2, &n);
    int i;
    for (i = 0; i < n_eval; i++) {
        double prom = suma[i] / n;
        double desv = sqrt(suma2[i]/n - prom*prom);
        printf("Evaluación %d: Promedio = %.2f, Desviación = %.2f\n", i+1, prom, desv);
    }
    free(suma); free(suma2);
}

// Promedio y desviación estándar del promedio final en la lista
void promedio_final_lista(struct_lista_alumnos *cabeza) {
    int n = 0;
    double suma = 0, suma2 = 0;
    struct_lista_alumnos *act;
    for (act = cabeza; act; act = act->siguiente) {
        suma += act->alumno->promedio;
        suma2 += act->alumno->promedio * act->alumno->promedio;
        n++;
    }
    double prom = suma / n;
    double desv = sqrt(suma2/n - prom*prom);
    printf("Promedio final: %.2f, Desviación: %.2f\n", prom, desv);
}

// Promedio y desviación estándar del promedio final en el árbol
static void acum_final_arbol(struct_arbol_alumnos *raiz, double *suma, double *suma2, int *n) {
    if (!raiz) return;
    acum_final_arbol(raiz->izquierda, suma, suma2, n);
    *suma += raiz->alumno->promedio;
    *suma2 += raiz->alumno->promedio * raiz->alumno->promedio;
    (*n)++;
    acum_final_arbol(raiz->derecha, suma, suma2, n);
}
void promedio_final_arbol(struct_arbol_alumnos *raiz) {
    double suma = 0, suma2 = 0;
    int n = 0;
    acum_final_arbol(raiz, &suma, &suma2, &n);
    double prom = suma / n;
    double desv = sqrt(suma2/n - prom*prom);
    printf("Promedio final: %.2f, Desviación: %.2f\n", prom, desv);
}

// Buscar por ROL en la lista
struct_alumnos* buscar_por_rol_lista(struct_lista_alumnos *cabeza, const char *rol) {
    while (cabeza) {
        if (strcmp(cabeza->alumno->rol, rol) == 0)
            return cabeza->alumno;
        cabeza = cabeza->siguiente;
    }
    return NULL;
}

// Buscar por ROL en el árbol
struct_alumnos* buscar_por_rol_arbol(struct_arbol_alumnos *raiz, const char *rol) {
    if (!raiz) return NULL;
    int cmp = strcmp(raiz->alumno->rol, rol);
    if (cmp == 0) return raiz->alumno;
    struct_alumnos *found = buscar_por_rol_arbol(raiz->izquierda, rol);
    if (found) return found;
    return buscar_por_rol_arbol(raiz->derecha, rol);
}

// Imprimir datos y notas de un alumno
void imprimir_datos_alumno(struct_alumnos *alumno) {
    if (!alumno) {
        printf("Alumno no encontrado.\n");
        return;
    }
    printf("Rol: %s\n", alumno->rol);
    printf("Nombre: %s %s %s\n", alumno->nombre, alumno->apellido1, alumno->apellido2);
    printf("Notas: ");
    int i;
    for (i = 0; i < alumno->cantidad_notas; i++) {
        printf("%d ", alumno->notas[i]);
    }
    printf("\nPromedio: %d\n", alumno->promedio);
}
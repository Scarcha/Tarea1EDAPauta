#include "main.h"


int main(int argc, char *argv[]) {
    FILE *file = fopen("texto2.txt", "r");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 0;
    }
    struct_lista_alumnos *cabeza = NULL;
    struct_lista_alumnos *actual = NULL;
    struct_lista_alumnos *nuevo = NULL;
    struct_arbol_alumnos *raiz = NULL; // Agrega esto antes del while
    char line[512];
    while (fgets(line, sizeof(line), file)) {
        nuevo = (struct_lista_alumnos *)malloc(sizeof(struct_lista_alumnos));
        nuevo->alumno = (struct_alumnos *)malloc(sizeof(struct_alumnos));
        nuevo->siguiente = NULL;

        char *ptr = line;

        // Leer rol
        char rol[9];
        sscanf(ptr, "%s", rol);
        nuevo->alumno->rol = strdup(rol);

        // Avanzar ptr después del rol
        ptr = strchr(ptr, ' ');
        if (!ptr) continue;
        ptr++;

        // Buscar comillas
        char *start = strchr(ptr, '"');
        char *end = start ? strchr(start + 1, '"') : NULL;
        if (!start || !end) continue;

        // Extraer nombre completo
        char nombre_completo[128];
        strncpy(nombre_completo, start + 1, end - start - 1);
        nombre_completo[end - start - 1] = '\0';

        // Separar nombre, apellido1, apellido2
        char *nombre = strtok(nombre_completo, " ");
        char *apellido1 = strtok(NULL, " ");
        char *apellido2 = strtok(NULL, " ");
        nuevo->alumno->nombre = strdup(nombre ? nombre : "");
        nuevo->alumno->apellido1 = strdup(apellido1 ? apellido1 : "");
        nuevo->alumno->apellido2 = strdup(apellido2 ? apellido2 : "");

        // Avanzar ptr después de las comillas
        ptr = end + 1;
        while (*ptr == ' ') ptr++; // Saltar espacios antes de las notas

        // Leer notas
        int *notas = NULL;
        int n_notas = 0;
        int capacidad = 0;
        int nota;
        while (sscanf(ptr, "%d", &nota) == 1) {
            if (n_notas == capacidad) {
            capacidad = capacidad == 0 ? 4 : capacidad * 2;
            notas = realloc(notas, capacidad * sizeof(int));
            }
            notas[n_notas++] = nota;
            // Avanzar ptr al siguiente número
            while (*ptr && *ptr != ' ') ptr++;
            while (*ptr == ' ') ptr++;
        }
        // Guardar notas en la estructura
        nuevo->alumno->notas = malloc(n_notas * sizeof(int));
        int i;
        for (i = 0; i < n_notas; i++) {
            nuevo->alumno->notas[i] = notas[i];
        }
        free(notas);
        nuevo->alumno->cantidad_notas = n_notas;

        // Calcular promedio
        int suma = 0;
        int i;
        for (i = 0; i < n_notas; i++) {
            suma += nuevo->alumno->notas[i];
        }
        nuevo->alumno->promedio = (n_notas > 0) ? suma / n_notas : 0;

        // Agregar a la lista enlazada
        if (cabeza == NULL) {
            cabeza = nuevo;
            actual = cabeza;
        } else {
            actual->siguiente = nuevo;
            actual = actual->siguiente;
        }

        // Agregar al árbol binario
        raiz = insertar_en_arbol(raiz, nuevo->alumno);
    }
    fclose(file);
    ordenar_lista_por_promedio(cabeza); 
    /*
    printf("Lista enlazada ordenada por promedio:\n");
    imprimir_lista(cabeza);
    printf("\nÁrbol binario de alumnos:\n");
    imprimir_arbol(raiz);
    */
    guardar_lista_txt(cabeza, "lista.txt");
    guardar_arbol_archivo(raiz, "arbol.txt");


    if (argc == 2) {
        if (strcmp(argv[1], "lista") == 0) {
            printf("Cantidad de alumnos (lista): %d\n", contar_alumnos_lista(cabeza));
            promedio_desviacion_lista(cabeza);
            promedio_final_lista(cabeza);
        } else if (strcmp(argv[1], "arbol") == 0) {
            printf("Cantidad de alumnos (arbol): %d\n", contar_alumnos_arbol(raiz));
            int n_eval = cabeza ? cabeza->alumno->cantidad_notas : 0;
            promedio_desviacion_arbol(raiz, n_eval);
            promedio_final_arbol(raiz);
        }
        else{printf("Comando no reconocido. Usa 'lista' o 'arbol'.\n");}
    }
    if (argc == 3) {
        if (strcmp(argv[1], "buscar_lista") == 0) {
            struct_alumnos *al = buscar_por_rol_lista(cabeza, argv[2]);
            imprimir_datos_alumno(al);
        } else if (strcmp(argv[1], "buscar_arbol") == 0) {
            struct_alumnos *al = buscar_por_rol_arbol(raiz, argv[2]);
            imprimir_datos_alumno(al);
        }
        else {
            printf("Comando no reconocido. Usa 'buscar_lista' o 'buscar_arbol'.\n");
        }
    }
    if(argc > 3) {
        printf("Demasiados argumentos. Usa 'lista', 'arbol', 'buscar_lista <rol>' o 'buscar_arbol <rol>'.\n");
    }

    liberar_lista(cabeza);
    liberar_arbol(raiz);
    
    return 0;
}
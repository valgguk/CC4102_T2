# Tarea 2: Diseño y Análisis de Algoritmos (CC4102 - 2025-1)
# Comparación de variantes del algoritmo de Kruskal


Integrantes:
- Valentina Ramírez 
- Aldo Luna
- Pablo Osorio

Este repositorio contiene la implementación y los scripts necesarios para comparar cuatro variantes del algoritmo de Kruskal:

1. **sort\_opti**: Kruskal con un arreglo ordenado de aristas y optimización de `find` (compresión de rutas y unión por tamaño).
2. **heap\_opti**: Kruskal con un heap clásico de aristas y optimización de `find`.
3. **sort\_no\_opti**: Kruskal con arreglo ordenado de aristas, sin optimización de `find`.
4. **heap\_no\_opti**: Kruskal con heap clásico, sin optimización de `find`.

## Requisitos

- Un compilador de C++ con soporte para **C++17** (por ejemplo, `g++` 7.0 o superior).
- Herramientas de compilación estándar: `make` o acceso a la línea de comandos.
- No se usan librerías externas más allá de la STL de C++.

> **Nota (Windows)**: Si usas Windows, se recomienda instalar MinGW-w64 (a través de MSYS2) o Visual Studio con soporte para C++17.

## Archivos en el proyecto

- `estructuras.h` / `estructuras.cpp`: Definición de las estructuras de nodo, arista y generación de grafos de prueba.
- `union_find.h` / `union_find.cpp`: Implementación del DSU (Disjoint Set Union) con compresión de rutas y unión por tamaño.
- `kruskal_con_find.h` / `kruskal_con_find.cpp`: Implementaciones optimizadas (con `find`) usando sort y heap.
- `kruskal_sin_opti.h` / `kruskal_sin_opti.cpp`: Implementaciones sin optimización de `find` (método sin compresión de rutas).
- `main.cpp`: Script principal que ejecuta los experimentos para \(N = 2^5,2^6,\dots,2^{12}\), realiza 5 corridas por caso y muestra tiempos promediados en CSV.

## Compilación

Abre una terminal en la carpeta raíz del proyecto y ejecuta:

```bash
# En Linux o MSYS2 (g++)
g++ -std=c++17 -O2 \
    estructuras.cpp \
    union_find.cpp \
    kruskal_con_find.cpp \
    kruskal_sin_opti.cpp \
    main.cpp \
    -o kruskal_all
```

```powershell
# En Windows con MinGW (PowerShell)
g++ -std=c++17 -O2 estructuras.cpp union_find.cpp kruskal_con_find.cpp kruskal_sin_opti.cpp main.cpp -o kruskal_all.exe
```

No se requieren opciones adicionales ni dependencias externas.

## Ejecución

Tras compilar, ejecuta el binario sin argumentos:

```bash
./kruskal_all      # Linux / MSYS2
kruskal_all.exe    # Windows
```

La salida será un CSV con las columnas:

```
N,sort_opti,heap_opti,sort_no_opti,heap_no_opti
32,0.00001952,0.00001098,0.00001802,0.00001134
64,...
... etc.
```

- **N**: número de nodos (\(2^5,2^6,\dots,2^{12}\)).
- Las demás columnas son los tiempos promedio (en segundos) de cada variante sobre 5 corridas.




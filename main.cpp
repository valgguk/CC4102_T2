// main.cpp
// Ejecuta experimentación de las cuatro variantes de Kruskal.

#include "estructuras.h"
#include "kruskal_con_find.h"
#include "kruskal_sin_opti.h"
#include "union_find.h"
#include <chrono>
#include <iostream>
#include <vector>

int main() {
    const int runs = 5;
    // Encabezado CSV: N, sort_opti, heap_opti, sort_no_opti, heap_no_opti
    std::cout << "N,sort_opti,heap_opti,sort_no_opti,heap_no_opti\n";

    for (int exp = 5; exp <= 12; ++exp) {
        int N = 1 << exp; // 2^exp nodos
        double total_sort_opti = 0;
        double total_heap_opti = 0;
        double total_sort_no = 0;
        double total_heap_no = 0;

        for (int r = 0; r < runs; ++r) {
            auto nodes = generate_nodes(N);
            auto edges = generate_edges(nodes);

            // 1) Sort + compresión de rutas
            {
                auto edges_copy = edges;
                auto t0 = std::chrono::high_resolution_clock::now();
                auto mst = kruskal_sort_opti(edges_copy, N);
                auto t1 = std::chrono::high_resolution_clock::now();
                total_sort_opti += std::chrono::duration<double>(t1 - t0).count();
            }
            // 2) Heap + compresión de rutas
            {
                auto t0 = std::chrono::high_resolution_clock::now();
                auto mst = kruskal_heap_opti(edges, N);
                auto t1 = std::chrono::high_resolution_clock::now();
                total_heap_opti += std::chrono::duration<double>(t1 - t0).count();
            }
            // 3) Sort sin optimización de find
            {
                auto edges_copy = edges;
                auto t0 = std::chrono::high_resolution_clock::now();
                auto mst = kruskal_sort(edges_copy, N);
                auto t1 = std::chrono::high_resolution_clock::now();
                total_sort_no += std::chrono::duration<double>(t1 - t0).count();
            }
            // 4) Heap sin optimización de find
            {
                auto t0 = std::chrono::high_resolution_clock::now();
                auto mst = kruskal_heap(edges, N);
                auto t1 = std::chrono::high_resolution_clock::now();
                total_heap_no += std::chrono::duration<double>(t1 - t0).count();
            }
        }
        // Calcular promedios
        double avg_sort_opti = total_sort_opti / runs;
        double avg_heap_opti = total_heap_opti / runs;
        double avg_sort_no = total_sort_no / runs;
        double avg_heap_no = total_heap_no / runs;

        // Salida CSV
        std::cout << N << ","
                  << avg_sort_opti << ","
                  << avg_heap_opti << ","
                  << avg_sort_no << ","
                  << avg_heap_no << "\n";
    }

    return 0;
}

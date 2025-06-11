#include "estructuras.h"
#include <random>
#include <algorithm>
#include <chrono>
#include <iostream>

bool Edge::operator<(const Edge& other) const {
    return weight > other.weight; // para min-heap
}

std::vector<Node> generate_nodes(int n) {
    std::vector<Node> nodes(n);
    std::mt19937_64 rng(std::random_device{}());
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < n; ++i)
        nodes[i] = {i, dist(rng), dist(rng)};

    return nodes;
}

double edge_weight(const Node& a, const Node& b) {
    double dx = a.x - b.x, dy = a.y - b.y;
    return dx * dx + dy * dy;
}

std::vector<Edge> generate_edges(std::vector<Node>& nodes) {
    std::vector<Edge> edges;
    int n = nodes.size();
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            edges.push_back({&nodes[i], &nodes[j], edge_weight(nodes[i], nodes[j])});
    return edges;
}

void construir_con_sort(std::vector<Edge>& edges) {
    auto start = std::chrono::high_resolution_clock::now();

    std::sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    });

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = end - start;
    std::cout << "Tiempo sort: " << duracion.count() << " segundos\n";
}

void construir_con_heap(std::vector<Edge>& edges) {
    auto start = std::chrono::high_resolution_clock::now();

    std::priority_queue<Edge> heap(edges.begin(), edges.end());

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duracion = end - start;
    std::cout << "Tiempo heap: " << duracion.count() << " segundos\n";
}

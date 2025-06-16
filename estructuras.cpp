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
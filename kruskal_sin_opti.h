#ifndef KRUSKAL_SIN_OPTI_H
#define KRUSKAL_SIN_OPTI_H

#include <vector>

// Union-Find SIN optimización de find
struct UnionFind {
    std::vector<int> parent, rank;

    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    //Versión SIN optimización de find (compresión de caminos)
    int find(int x) {
        while (parent[x] != x)
            x = parent[x];
        return x;
    }

    bool unite(int x, int y) {
        int rx = find(x), ry = find(y);
        if (rx == ry) return false;
        if (rank[rx] < rank[ry])
            parent[rx] = ry;
        else if (rank[rx] > rank[ry])
            parent[ry] = rx;
        else {
            parent[ry] = rx;
            rank[rx]++;
        }
        return true;
    }
};

#endif
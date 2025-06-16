// union_find.cpp
#include "union_find.h"

UnionFind::UnionFind(int n) : parent(n), size(n, 1) {
    for (int i = 0; i < n; ++i)
        parent[i] = i;
}

int UnionFind::find(int u) {
    if (parent[u] != u)
        parent[u] = find(parent[u]);
    return parent[u];
}

bool UnionFind::unite(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    if (size[u] < size[v])
        std::swap(u, v);
    parent[v] = u;
    size[u] += size[v];
    return true;
}

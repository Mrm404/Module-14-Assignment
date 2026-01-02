#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v;
};

int karger_min_cut(vector<Edge> edges, int vertices, int iterations = 100) {
    int minCut = INT_MAX;
    random_device rd;
    mt19937 gen(rd());

    for (int i = 0; i < iterations; i++) {
        vector<Edge> currentEdges = edges;
        vector<int> parent(vertices);

        for (int i = 0; i < vertices; i++)
            parent[i] = i;

        int remainingVertices = vertices;

        function<int(int)> find = [&](int x) {
            if (parent[x] != x)
                parent[x] = find(parent[x]);
            return parent[x];
        };

        while (remainingVertices > 2) {
            uniform_int_distribution<> dist(0, currentEdges.size() - 1);
            Edge e = currentEdges[dist(gen)];

            int u = find(e.u);
            int v = find(e.v);

            if (u == v)
                continue;

            parent[v] = u;
            remainingVertices--;
        }

        int cutEdges = 0;
        for (auto &e : currentEdges) {
            if (find(e.u) != find(e.v))
                cutEdges++;
        }

        minCut = min(minCut, cutEdges);
    }

    return minCut;
}

int main() {
    int vertices = 4;

    vector<Edge> edges = {
        {0, 1}, {0, 2}, {0, 3},
        {1, 2}, {2, 3}, {1, 3}
    };

    int result = karger_min_cut(edges, vertices, 200);
    cout << "Minimum Cut: " << result << endl;

    return 0;
}

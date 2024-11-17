#include <bits/stdc++.h>
using namespace std;

// Disjoint Set (Union-Find) implementation
class DisjointSet {
public:
    vector<int> parent, rank;

    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]); // Path compression
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }
};

// Kruskal's Algorithm
vector<tuple<int, int, int>> kruskal(int n, vector<tuple<int, int, int>>& edges, vector<vector<tuple<int, int, int>>>& steps) {
    sort(edges.begin(), edges.end(), [](const tuple<int, int, int>& a, const tuple<int, int, int>& b) {
        return get<2>(a) < get<2>(b);
    });

    DisjointSet ds(n);
    vector<tuple<int, int, int>> mst;
    int mstWeight = 0;

    for (size_t i = 0; i < edges.size(); i++) {
        int u = get<0>(edges[i]);
        int v = get<1>(edges[i]);
        int weight = get<2>(edges[i]);

        if (ds.find(u) != ds.find(v)) {
            ds.unionSets(u, v);
            mst.push_back(edges[i]);
            mstWeight += weight;

            // Save the current step
            steps.push_back({edges[i]});
        }
    }

    return mst;
}

// Main function
int main() {
    vector<tuple<int, int, int>> edges = {
        {0, 1, 4}, {0, 7, 8}, {1, 2, 8}, {1, 7, 11}, {2, 3, 7},
        {2, 8, 2}, {2, 5, 4}, {3, 4, 9}, {3, 5, 14}, {4, 5, 10},
        {5, 6, 2}, {6, 7, 1}, {6, 8, 6}, {7, 8, 7}
    };
    int numVertices = 9;

    vector<vector<tuple<int, int, int>>> steps;
    vector<tuple<int, int, int>> mst = kruskal(numVertices, edges, steps);

    // Vertex map for readability
    vector<char> vertexMap = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i'};

    // Print step-by-step MST construction
    cout << "Step-by-step MST construction:\n";
    for (size_t i = 0; i < steps.size(); i++) {
        cout << "Step " << i + 1 << ": Added edge {";
        for (size_t j = 0; j < steps[i].size(); j++) {
            int u = get<0>(steps[i][j]);
            int v = get<1>(steps[i][j]);
            int w = get<2>(steps[i][j]);
            cout << "(" << vertexMap[u] << ", " << vertexMap[v] << ", " << w << ")";
        }
        cout << "}\n";
    }

    // Print final MST
    cout << "\nFinal MST:\n";
    for (size_t i = 0; i < mst.size(); i++) {
        int u = get<0>(mst[i]);
        int v = get<1>(mst[i]);
        int w = get<2>(mst[i]);
        cout << "(" << vertexMap[u] << ", " << vertexMap[v] << ", " << w << ")\n";
    }

    return 0;
}


/*
OUTPUT:
Step-by-step MST construction:
Step 1: Added edge {(g, h, 1)}
Step 2: Added edge {(c, i, 2)}
Step 3: Added edge {(f, g, 2)}
Step 4: Added edge {(a, b, 4)}
Step 5: Added edge {(c, f, 4)}
Step 6: Added edge {(c, d, 7)}
Step 7: Added edge {(a, h, 8)}
Step 8: Added edge {(d, e, 9)}

Final MST:
(g, h, 1)
(c, i, 2)
(f, g, 2)
(a, b, 4)
(c, f, 4)
(c, d, 7)
(a, h, 8)
(d, e, 9)
*/
#include <bits/stdc++.h>
using namespace std;

bool dfs(unordered_map<string, vector<string>> &graph, const string &node, const string &target, unordered_set<string> &visited) {
    if (node == target) {
        cout << "Found target node: " << node << endl;
        return true;
    }

    visited.insert(node);
    for (const string &neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            if (dfs(graph, neighbor, target, visited)) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"cricket_pants", {"cricket_shirt", "cricket_shoes"}},
        {"cricket_socks", {"cricket_shoes"}},
        {"cricket_shirt", {"cricket_cap", "cricket_belt"}},
        {"cricket_cap", {"cricket_gloves"}},
        {"cricket_belt", {"cricket_pads"}},
        {"cricket_shoes", {}},
        {"cricket_gloves", {"cricket_helmet"}},
        {"cricket_pads", {"cricket_helmet"}},
        {"cricket_helmet", {}}
    };

    unordered_set<string> visited;
    string start_node = "cricket_pants";
    string target_node = "cricket_helmet";

    cout << "Target node: " << target_node << endl;
    cout << "Starting node: " << start_node << endl;

    bool found = dfs(graph, start_node, target_node, visited);

    if (!found) {
        cout << "Target node not found in the graph." << endl;
    }

    return 0;
}

/*
OUTPUT:
Target node: cricket_helmet
Starting node: cricket_pants
Found target node: cricket_helmet
*/
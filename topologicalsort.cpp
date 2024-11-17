#include <bits/stdc++.h>
using namespace std;

void dfs_topological_sort(unordered_map<string, vector<string>> &graph, const string &node, unordered_set<string> &visited, stack<string> &stack) {
    visited.insert(node);
    for (const string &neighbor : graph[node]) {
        if (visited.find(neighbor) == visited.end()) {
            dfs_topological_sort(graph, neighbor, visited, stack);
        }
    }
    stack.push(node);
}

vector<string> topological_sort(unordered_map<string, vector<string>> &graph) {
    unordered_set<string> visited;
    stack<string> stack;

    for (const auto &pair : graph) {
        if (visited.find(pair.first) == visited.end()) {
            dfs_topological_sort(graph, pair.first, visited, stack);
        }
    }

    vector<string> result;
    while (!stack.empty()) {
        result.push_back(stack.top());
        stack.pop();
    }

    return result;
}

int main() {
    unordered_map<string, vector<string>> graph = {
        {"cricket_pants", {"cricket_shoes", "cricket_belt"}},
        {"cricket_socks", {"cricket_shoes"}},
        {"cricket_shirt", {"cricket_cap", "cricket_belt"}},
        {"cricket_cap", {"cricket_gloves"}},
        {"cricket_belt", {"cricket_pads"}},
        {"cricket_shoes", {}},
        {"cricket_watch", {}},
        {"cricket_gloves", {"cricket_helmet"}},
        {"cricket_pads", {"cricket_helmet"}},
        {"cricket_helmet", {}}
    };

    vector<string> result = topological_sort(graph);

    cout << "Topological Order: ";
    for (const string &node : result) {
        cout << node << " -> ";
    }
    cout << endl;

    return 0;
}


/*
OUTPUT:
Topological Order: cricket_pants -> cricket_socks -> cricket_watch -> cricket_shirt -> cricket_cap -> cricket_shoes -> cricket_gloves -> cricket_belt -> cricket_pads -> cricket_helmet -> 
*/
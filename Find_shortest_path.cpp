#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, weight;
};

vector<vector<Edge>> graph;
vector<int> dist, parent;

void dijkstra(int source) {
    int n = graph.size();
    dist.assign(n, INT_MAX);
    parent.assign(n, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int currDist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if (currDist > dist[node]) continue;

        for (Edge edge : graph[node]) {
            int nextNode = edge.to;
            int weight = edge.weight;

            if (dist[node] + weight < dist[nextNode]) {
                dist[nextNode] = dist[node] + weight;
                parent[nextNode] = node;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }
}

void generateDOTFile(string filename, int nodes) {
    ofstream file(filename);
    file << "graph G {\n";

    for (int i = 0; i < nodes; i++) {
        for (Edge edge : graph[i]) {
            if (i < edge.to) { // Avoid duplicate edges
                file << "  " << i << " -- " << edge.to << " [label=\"" << edge.weight << "\"];\n";
            }
        }
    }
    file << "}\n";
    file.close();
}

int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges: ";
    cin >> nodes >> edges;

    graph.resize(nodes);

    cout << "Enter edges (from to weight):\n";
    for (int i = 0; i < edges; i++) {
        int from, to, weight;
        cin >> from >> to >> weight;
        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight}); 
    }

    int source;
    cout << "Enter source node: ";
    cin >> source;

    dijkstra(source);

    cout << "Shortest distances from node " << source << ":\n";
    for (int i = 0; i < nodes; i++) {
        cout << "To " << i << " -> " << (dist[i] == INT_MAX ? -1 : dist[i]) << "\n";
    }

    
    generateDOTFile("graph.dot", nodes);
    cout << "Graph visualization file generated as graph.dot!\n";
    cout << "Use Graphviz to generate an image (Example: dot -Tpng graph.dot -o graph.png)\n";

    return 0;
}

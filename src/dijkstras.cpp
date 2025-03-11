#include "dijkstras.h"
using namespace std;


struct Node {       //  Need to have this to match pseduo code implementation
    int vertex;
    int distance;
    Node(int v, int d) : vertex(v), distance(d) {}
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF);
    previous.assign(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    pq.push(Node(source, 0));
    distance[source] = 0;

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();
        int u = current.vertex;

        if (visited[u]) 
            continue;
        
        visited[u] = true;

        for (const auto& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    
    vector<int> reversed_path;
    for (int i = path.size() - 1; i >= 0; --i) {
        reversed_path.push_back(path[i]);
    }   
    return reversed_path;
}



void print_path(const vector<int>& v, int total) {
    int size = v.size();
    
    for (int i = 0; i < size; i++) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}

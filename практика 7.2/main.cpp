#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int src, dest, weight;
    Edge(int s, int d, int w) : src(s), dest(d), weight(w) {}
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

class Graph {
    int V;
    vector<Edge> edges;

public:
    Graph(int V) : V(V) {}

    void addEdge(int src, int dest, int weight) {
        edges.emplace_back(src, dest, weight);
    }

    int find(int parent[], int i) {
        if (parent[i] != i)
            parent[i] = find(parent, parent[i]);
        return parent[i];
    }

    void unionSets(int parent[], int rank[], int x, int y) {
        int rootX = find(parent, x);
        int rootY = find(parent, y);

        if (rank[rootX] < rank[rootY])
            parent[rootX] = rootY;
        else if (rank[rootX] > rank[rootY])
            parent[rootY] = rootX;
        else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }

    void kruskalMST() {
        sort(edges.begin(), edges.end(), compare);

        vector<Edge> result;
        int parent[V + 1];
        int rank[V + 1];

        for (int i = 1; i <= V; ++i) {
            parent[i] = i;
            rank[i] = 0;
        }

        for (Edge& edge : edges) {
            int root1 = find(parent, edge.src);
            int root2 = find(parent, edge.dest);

            if (root1 != root2) {
                result.push_back(edge);
                unionSets(parent, rank, root1, root2);
            }
        }

        cout << "Минимальное остовное дерево:\n";
        for (const Edge& e : result) {
            cout << e.src << " - " << e.dest << " : " << e.weight << endl;
        }
    }
};

int main() {
    int V = 5;
    Graph graph(V);

    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(1, 5, 10);
    graph.addEdge(2, 5, 6);
    graph.addEdge(2, 4, 3);
    graph.addEdge(3, 5, 7);
    graph.addEdge(3, 4, 4);
    graph.addEdge(4, 5, 11);

    graph.kruskalMST();

    return 0;
}


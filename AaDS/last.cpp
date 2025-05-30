#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

struct Node {
    int vertex;
    vector<int> edges;
};

class Graph {
    bool directed;
    vector<Node> nodes;
    unordered_map<int, int> vertex_index; // Маппинг вершина -> индекс в nodes

    int find_index(int v) {
        auto it = vertex_index.find(v);
        return (it != vertex_index.end()) ? it->second : -1;
    }

    void update_index() {
        vertex_index.clear();
        for(int i = 0; i < nodes.size(); i++) {
            vertex_index[nodes[i].vertex] = i;
        }
    }

public:
    Graph(bool dir = true) : directed(dir) {}

    void add_vertex(int v) {
        if(vertex_index.find(v) != vertex_index.end()) return;
        nodes.push_back({v, {}});
        vertex_index[v] = nodes.size() - 1;
    }

    void add_edge(int u, int v) {
        add_vertex(u);
        add_vertex(v);

        int idx_u = find_index(u);
        nodes[idx_u].edges.push_back(v);

        if(!directed && u != v) {
            int idx_v = find_index(v);
            nodes[idx_v].edges.push_back(u);
        }
    }

    void remove_vertex(int v) {
        auto it = vertex_index.find(v);
        if(it == vertex_index.end()) return;

        int idx = it->second;
        nodes.erase(nodes.begin() + idx);
        vertex_index.erase(v);
        update_index(); // Обновляем маппинг индексов

        for(auto& node : nodes) {
            auto& edges = node.edges;
            edges.erase(remove(edges.begin(), edges.end(), v), edges.end());
        }
    }

    void remove_edge(int u, int v) {
        int idx_u = find_index(u);
        if(idx_u != -1) {
            auto& edges = nodes[idx_u].edges;
            edges.erase(remove(edges.begin(), edges.end(), v), edges.end());
        }

        if(!directed) {
            int idx_v = find_index(v);
            if(idx_v != -1) {
                auto& edges = nodes[idx_v].edges;
                edges.erase(remove(edges.begin(), edges.end(), u), edges.end());
            }
        }
    }

    void print() {
        for(auto& node : nodes) {
            cout << node.vertex << " -> ";
            for(int n : node.edges)
                cout << n << " ";
            cout << endl;
        }
    }

    vector<int> dfs(int start) {
        vector<int> visited;
        stack<int> s;
        unordered_set<int> processed;

        int idx = find_index(start);
        if(idx != -1) {
            s.push(start);
            processed.insert(start);
        }

        while(!s.empty()) {
            int current = s.top();
            s.pop();
            visited.push_back(current);

            idx = find_index(current);
            for(auto it = nodes[idx].edges.rbegin(); it != nodes[idx].edges.rend(); ++it) {
                int neighbor = *it;
                if(processed.find(neighbor) == processed.end() && vertex_index.find(neighbor) != vertex_index.end()) {
                    s.push(neighbor);
                    processed.insert(neighbor);
                }
            }
        }
        return visited;
    }

    vector<int> bfs(int start) {
        vector<int> visited;
        queue<int> q;
        unordered_set<int> processed;

        int idx = find_index(start);
        if(idx != -1) {
            q.push(start);
            processed.insert(start);
        }

        while(!q.empty()) {
            int current = q.front();
            q.pop();
            visited.push_back(current);

            idx = find_index(current);
            for(int neighbor : nodes[idx].edges) {
                if(processed.find(neighbor) == processed.end() && vertex_index.find(neighbor) != vertex_index.end()) {
                    q.push(neighbor);
                    processed.insert(neighbor);
                }
            }
        }
        return visited;
    }

    vector<int> unreachable_vertices(int start) {
        unordered_set<int> reachable;
        vector<int> visited = this->bfs(start);
        for(int v : visited) reachable.insert(v);

        vector<int> unreachable;
        for(auto& node : nodes) {
            if(reachable.find(node.vertex) == reachable.end()) {
                unreachable.push_back(node.vertex);
            }
        }
        return unreachable;
    }

    static Graph read_from_file(const string& filename) {
        ifstream file(filename);
        if(!file) throw runtime_error("Ошибка открытия файла");

        string dir;
        file >> dir;
        bool directed = (dir == "directed");

        Graph g(directed);
        int u, v;
        while(file >> u >> v) {
            g.add_edge(u, v);
        }
        return g;
    }
};

int main() {
    try {
        Graph g = Graph::read_from_file("graph.txt");

        cout << "Исходный граф:\n";
        g.print();

        cout << "\nDFS от 1: ";
        for(int v : g.dfs(1)) cout << v << " ";

        cout << "\nBFS от 1: ";
        for(int v : g.bfs(1)) cout << v << " ";

        cout << "\nНедостижимые от 1: ";
        for(int v : g.unreachable_vertices(1)) cout << v << " ";

        g.remove_edge(1, 2);
        g.remove_vertex(3);

        cout << "\n\nПосле изменений:\n";
        g.print();

        cout << "\nDFS от 1: ";
        for(int v : g.dfs(1)) cout << v << " ";

        cout << "\nBFS от 1: ";
        for(int v : g.bfs(1)) cout << v << " ";

        cout << "\nНедостижимые от 1: ";
        for(int v : g.unreachable_vertices(1)) cout << v << " ";

    } catch(const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}
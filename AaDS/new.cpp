#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int vertex;
    vector<int> edges;
};

class Graph {
    bool directed;
    vector<Node> nodes;

    int find_index(int v) {
        for(int i = 0; i < nodes.size(); i++)
            if(nodes[i].vertex == v) return i;
        return -1;
    }

public:
    Graph(bool dir = true) : directed(dir) {}

    void add_vertex(int v) {
        if(find_index(v) == -1)
            nodes.push_back({v, {}});
    }

    void add_edge(int u, int v) {
        add_vertex(u);
        add_vertex(v);

        int idx = find_index(u);
        nodes[idx].edges.push_back(v);

        if(!directed && u != v) {
            idx = find_index(v);
            nodes[idx].edges.push_back(u);
        }
    }

    void remove_vertex(int v) {
        for(int i = 0; i < nodes.size(); i++) {
            if(nodes[i].vertex == v) {
                nodes.erase(nodes.begin() + i);
                break;
            }
        }

        for(auto& node : nodes) {
            for(int i = 0; i < node.edges.size(); i++) {
                if(node.edges[i] == v) {
                    node.edges.erase(node.edges.begin() + i);
                    i--;
                }
            }
        }
    }

    void remove_edge(int u, int v) {
        int idx = find_index(u);
        if(idx != -1) {
            for(int i = 0; i < nodes[idx].edges.size(); i++) {
                if(nodes[idx].edges[i] == v) {
                    nodes[idx].edges.erase(nodes[idx].edges.begin() + i);
                    break;
                }
            }
        }

        if(!directed) {
            idx = find_index(v);
            if(idx != -1) {
                for(int i = 0; i < nodes[idx].edges.size(); i++) {
                    if(nodes[idx].edges[i] == u) {
                        nodes[idx].edges.erase(nodes[idx].edges.begin() + i);
                        break;
                    }
                }
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
        vector<bool> processed(nodes.size(), false);

        int idx = find_index(start);
        if(idx != -1) {
            s.push(start);
            processed[idx] = true;
        }

        while(!s.empty()) {
            int current = s.top();
            s.pop();
            visited.push_back(current);

            idx = find_index(current);
            for(int i = nodes[idx].edges.size()-1; i >= 0; i--) {
                int neighbor = nodes[idx].edges[i];
                int neighbor_idx = find_index(neighbor);
                if(neighbor_idx != -1 && !processed[neighbor_idx]) {
                    s.push(neighbor);
                    processed[neighbor_idx] = true;
                }
            }
        }
        return visited;
    }

    vector<int> bfs(int start) {
        vector<int> visited;
        queue<int> q;
        vector<bool> processed(nodes.size(), false);

        int idx = find_index(start);
        if(idx != -1) {
            q.push(start);
            processed[idx] = true;
        }

        while(!q.empty()) {
            int current = q.front();
            q.pop();
            visited.push_back(current);

            idx = find_index(current);
            for(int neighbor : nodes[idx].edges) {
                int neighbor_idx = find_index(neighbor);
                if(neighbor_idx != -1 && !processed[neighbor_idx]) {
                    q.push(neighbor);
                    processed[neighbor_idx] = true;
                }
            }
        }
        return visited;
    }

    static Graph read_from_file(const string& filename) {
        ifstream file(filename);
        if(!file) throw runtime_error("Ошибка открытия файла");

        string dir;
        file >> dir;
        bool directed = (dir == "directed");

        Graph g(directed);
        int u, v;
        while(file >> u >> v)
            g.add_edge(u, v);

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

        g.remove_edge(1, 2);
        g.remove_vertex(3);

        cout << "\n\nПосле изменений:\n";
        g.print();

    } catch(const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}

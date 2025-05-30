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
    unordered_map<int, int> vertex_index;

    int find_index(int v) {
        auto it = vertex_index.find(v);
        return (it != vertex_index.end()) ? it->second : -1;
    }

    void update_index() {
        vertex_index.clear();
        for (int i = 0; i < nodes.size(); i++) {
            vertex_index[nodes[i].vertex] = i;
        }
    }

public:
    Graph(bool dir = true) : directed(dir) {}

    void add_vertex(int v) {
        if (vertex_index.find(v) != vertex_index.end()) return;
        nodes.push_back({v, {}});
        vertex_index[v] = nodes.size() - 1;
    }

    void add_edge(int u, int v) {
        add_vertex(u);
        add_vertex(v);

        int idx_u = find_index(u);
        nodes[idx_u].edges.push_back(v);

        if (!directed && u != v) {
            int idx_v = find_index(v);
            nodes[idx_v].edges.push_back(u);
        }
    }

    void remove_vertex(int v) {
        auto it = vertex_index.find(v);
        if (it == vertex_index.end()) return;

        int idx = it->second;
        nodes.erase(nodes.begin() + idx);
        vertex_index.erase(v);
        update_index();

        for (auto& node : nodes) {
            auto& edges = node.edges;
            edges.erase(remove(edges.begin(), edges.end(), v), edges.end());
        }
    }

    void remove_edge(int u, int v) {
        int idx_u = find_index(u);
        if (idx_u != -1) {
            auto& edges = nodes[idx_u].edges;
            edges.erase(remove(edges.begin(), edges.end(), v), edges.end());
        }

        if (!directed) {
            int idx_v = find_index(v);
            if (idx_v != -1) {
                auto& edges = nodes[idx_v].edges;
                edges.erase(remove(edges.begin(), edges.end(), u), edges.end());
            }
        }
    }

    void print() {
        for (auto& node : nodes) {
            cout << node.vertex << " -> ";
            for (int n : node.edges)
                cout << n << " ";
            cout << endl;
        }
    }

    vector<int> dfs(int start) {
        vector<int> visited;
        stack<int> s;
        unordered_set<int> processed;

        int idx = find_index(start);
        if (idx != -1) {
            s.push(start);
            processed.insert(start);
        }

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            visited.push_back(current);

            idx = find_index(current);
            for (auto it = nodes[idx].edges.rbegin(); it != nodes[idx].edges.rend(); ++it) {
                int neighbor = *it;
                if (processed.find(neighbor) == processed.end() && vertex_index.find(neighbor) != vertex_index.end()) {
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
        if (idx != -1) {
            q.push(start);
            processed.insert(start);
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            visited.push_back(current);

            idx = find_index(current);
            for (int neighbor : nodes[idx].edges) {
                if (processed.find(neighbor) == processed.end() && vertex_index.find(neighbor) != vertex_index.end()) {
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
        for (int v : visited) reachable.insert(v);

        vector<int> unreachable;
        for (auto& node : nodes) {
            if (reachable.find(node.vertex) == reachable.end()) {
                unreachable.push_back(node.vertex);
            }
        }
        return unreachable;
    }

    static Graph read_from_file(const string& filename) {
        ifstream file(filename);
        if (!file) throw runtime_error("Ошибка открытия файла");

        string dir;
        file >> dir;
        bool directed = (dir == "directed");

        Graph g(directed);
        int u, v;
        while (file >> u >> v) {
            g.add_edge(u, v);
        }
        return g;
    }
};

// === Меню ===
void print_menu() {
    cout << "\n=== МЕНЮ ===\n";
    cout << "1. Загрузить граф из файла\n";
    cout << "2. Добавить вершину\n";
    cout << "3. Добавить ребро\n";
    cout << "4. Удалить вершину\n";
    cout << "5. Удалить ребро\n";
    cout << "6. Печать графа\n";
    cout << "7. DFS (обход в глубину)\n";
    cout << "8. BFS (обход в ширину)\n";
    cout << "9. Недостижимые вершины\n";
    cout << "0. Выход\n";
    cout << "Выберите команду: ";
}

int main() {
    Graph g;
    int choice;

    while (true) {
        print_menu();
        cin >> choice;

        if (choice == 0) break;

        int v, u;
        string filename;

        switch (choice) {
            case 1:
                cout << "Введите имя файла: ";
                cin >> filename;
                try {
                    g = Graph::read_from_file(filename);
                    cout << "Граф успешно загружен.\n";
                } catch (exception& e) {
                    cerr << "Ошибка: " << e.what() << endl;
                }
                break;
            case 2:
                cout << "Введите вершину: ";
                cin >> v;
                g.add_vertex(v);
                break;
            case 3:
                cout << "Введите ребро (u v): ";
                cin >> u >> v;
                g.add_edge(u, v);
                break;
            case 4:
                cout << "Введите вершину для удаления: ";
                cin >> v;
                g.remove_vertex(v);
                break;
            case 5:
                cout << "Введите ребро для удаления (u v): ";
                cin >> u >> v;
                g.remove_edge(u, v);
                break;
            case 6:
                g.print();
                break;
            case 7:
                cout << "Начать DFS с вершины: ";
                cin >> v;
                for (int x : g.dfs(v)) cout << x << " ";
                cout << endl;
                break;
            case 8:
                cout << "Начать BFS с вершины: ";
                cin >> v;
                for (int x : g.bfs(v)) cout << x << " ";
                cout << endl;
                break;
            case 9:
                cout << "Введите стартовую вершину: ";
                cin >> v;
                for (int x : g.unreachable_vertices(v)) cout << x << " ";
                cout << endl;
                break;
            default:
                cout << "Неверная команда. Попробуйте снова.\n";
        }
    }

    cout << "Выход из программы.\n";
    return 0;
}
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Graph {
    bool directed;
    unordered_map<int, vector<int>> adjacencyList;

public:
    Graph(bool dir = true) : directed(dir) {}

    void add_vertex(int v) {
        if (adjacencyList.find(v) == adjacencyList.end()) {
            adjacencyList[v] = vector<int>();
        }
    }

    void add_edge(int u, int v) {
        add_vertex(u);
        add_vertex(v);
        adjacencyList[u].push_back(v);
        if (!directed && u != v) {
            adjacencyList[v].push_back(u);
        }
    }

    void remove_vertex(int v) {
        adjacencyList.erase(v);
        for (auto& pair : adjacencyList) {
            auto& neighbors = pair.second;
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
        }
    }

    void remove_edge(int u, int v) {
        if (adjacencyList.find(u) != adjacencyList.end()) {
            auto& neighbors = adjacencyList[u];
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), v), neighbors.end());
        }
        if (!directed && adjacencyList.find(v) != adjacencyList.end()) {
            auto& neighbors = adjacencyList[v];
            neighbors.erase(remove(neighbors.begin(), neighbors.end(), u), neighbors.end());
        }
    }

    void print() {
        for (const auto& pair : adjacencyList) {
            cout << pair.first << " -> ";
            for (int neighbor : pair.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    vector<int> dfs(int start) {
        vector<int> visited;
        stack<int> s;
        unordered_set<int> processed;

        if (adjacencyList.find(start) != adjacencyList.end()) {
            s.push(start);
            processed.insert(start);
        }

        while (!s.empty()) {
            int current = s.top();
            s.pop();
            visited.push_back(current);

            for (int neighbor : adjacencyList[current]) {
                if (processed.find(neighbor) == processed.end()) {
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

        if (adjacencyList.find(start) != adjacencyList.end()) {
            q.push(start);
            processed.insert(start);
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            visited.push_back(current);

            for (int neighbor : adjacencyList[current]) {
                if (processed.find(neighbor) == processed.end()) {
                    q.push(neighbor);
                    processed.insert(neighbor);
                }
            }
        }
        return visited;
    }

    vector<int> unreachable(int start) {
        unordered_set<int> reachable;
        queue<int> q;

        if (adjacencyList.find(start) != adjacencyList.end()) {
            q.push(start);
            reachable.insert(start);
        }

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            for (int neighbor : adjacencyList[current]) {
                if (reachable.find(neighbor) == reachable.end()) {
                    reachable.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }

        vector<int> result;
        for (const auto& pair : adjacencyList) {
            if (reachable.find(pair.first) == reachable.end()) {
                result.push_back(pair.first);
            }
        }
        return result;
    }

    static Graph read_from_file(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Cannot open file");
        }

        bool directed;
        string dir;
        file >> dir;
        directed = (dir == "directed");

        Graph g(directed);
        int u, v;
        while (file >> u >> v) {
            g.add_edge(u, v);
        }
        return g;
    }
};

int main() {
    try {
        Graph g = Graph::read_from_file("graph.txt");

        cout << "Исходный граф:" << endl;
        g.print();

        cout << "\nDFS начиная с 1: ";
        for (int v : g.dfs(1)) cout << v << " ";

        cout << "\nBFS начиная с 1: ";
        for (int v : g.bfs(1)) cout << v << " ";

        cout << "\nНедостижимые из 1: ";
        for (int v : g.unreachable(1)) cout << v << " ";

        g.remove_edge(1, 2);
        g.remove_vertex(3);

        cout << "\n\nПосле изменений:" << endl;
        g.print();

    } catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
    return 0;
}

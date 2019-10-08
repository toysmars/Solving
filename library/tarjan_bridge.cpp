// https://en.wikipedia.org/wiki/Bridge_(graph_theory)#Tarjan's_bridge-finding_algorithm

#include <vector>
using namespace std;

struct Edge {
    int u;
    int v;
};

class Graph {
public:
    Graph(int num_v) : _num_v(num_v) {}

    int numVertices() const { return _num_v; }

    const vector<Edge>& edges() const {
        return _edges;
    }

    void addEdge(int u, int v) {
        _edges.push_back({u, v});
    }

    vector<vector<int>> adjacentList() const {
        vector<vector<int>> res(_num_v);
        for (auto edge : _edges) {
            res[edge.u].push_back(edge.v);
            res[edge.v].push_back(edge.u);
        }
        return res;
    }

private:
    int _num_v;
    vector<Edge> _edges;
};

class DisjointSet {
public:
    DisjointSet(int n) {
        for (int i = 0; i < n; ++i) {
            s.push_back(i);
            r.push_back(0);
        }
    }
    int findSet(int x) {
        if (s[x] != x) {
            s[x] = findSet(s[x]);
        }
        return s[x];
    }
    void unionSet(int x, int y) {
        int sx = findSet(x);
        int sy = findSet(y);
        if (sx == sy) {
            return;
        }
        if (r[sx] < r[sy]) {
            swap(sx, sy);
        }
        s[sy] = sx;
        if (r[sx] == r[sy]) {
            r[sx] += 1;
        }
    }
private:
    vector<int> s;
    vector<int> r;
};

class MinimumSpanningTree {
public:
    Graph minimumSpanningTree(const Graph& graph) {
        int n = graph.numVertices();
        DisjointSet ds(n);
        Graph mst(n);
        for (auto edge : graph.edges()) {
            if (ds.findSet(edge.u) != ds.findSet(edge.v)) {
                ds.unionSet(edge.u, edge.v);
                mst.addEdge(edge.u, edge.v);
            }
        }
        return mst;
    }
};

class BridgeDetector {
public:
    vector<Edge> bridges(const Graph& graph) {
        MinimumSpanningTree mst_util;
        Graph mst = mst_util.minimumSpanningTree(graph);
        
        _graph_adjacent_list = graph.adjacentList();
        _mst_adjacent_list = mst.adjacentList();

        int n = mst.numVertices();
        _visited = vector<bool>(n);
        _preorders = vector<int>(n);
        _preorder = 0;
        for (int u = 0; u < n; ++u) {
            if (!_visited[u]) {
                preorder(u, -1);
            }
        }
        _visited = vector<bool>(n);
        _nd = vector<int>(n);
        _l = vector<int>(n);
        _h = vector<int>(n);
        _p = vector<int>(n);
        for (int u = 0; u < n; ++u) {
            if (!_visited[u]) {
                traverse(u, -1);
            }
        }
        vector<Edge> res;
        for (int u = 0; u < n; ++u) {
            if (_p[u] != -1 && _l[u] == _preorders[u] && _h[u] < _preorders[u] + _nd[u]) {
                res.push_back({_p[u], u});
            }
        }
        return res;
    }

private:
    void preorder(int u, int p) {
        if (_visited[u]) return;
        _visited[u] = true;
        _preorders[u] = _preorder++;
        for (auto v : _mst_adjacent_list[u]) {
            if (v == p) continue;
            preorder(v, u);
        }
    }
    void traverse(int u, int p) {
        if (_visited[u]) return;
        _visited[u] = true;
        _p[u] = p;
        _nd[u] = 1;
        _l[u] = _preorders[u];
        _h[u] = _preorders[u];
        
        for (auto v : _graph_adjacent_list[u]) {
            if (v == p) continue;
            _l[u] = min(_l[u], _preorders[v]);
            _h[u] = max(_h[u], _preorders[v]);
        }
        for (auto v : _mst_adjacent_list[u]) {
            if (v == p) continue;
            traverse(v, u);
            _nd[u] += _nd[v];
            _l[u] = min(_l[u], _l[v]);
            _h[u] = max(_h[u], _h[v]);
        }
    }

private:
    vector<bool> _visited;
    vector<int> _preorders;
    vector<int> _nd;
    vector<int> _l;
    vector<int> _h;
    vector<int> _p;
    vector<vector<int>> _graph_adjacent_list;
    vector<vector<int>> _mst_adjacent_list;
    int _preorder;
};

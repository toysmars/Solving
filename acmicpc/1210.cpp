// acmicpc 1210
//
// maxflow
// mincut

#include <cstdio>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

#define INF INT_MAX

struct Edge {
    int u;
    int v;
    int cap;
    int flow;
    Edge* dual;
    
    Edge(int u, int v, int cap) : u(u), v(v), cap(cap), flow(0) {}

    static pair<Edge*, Edge*> createEdgeAndDual(int u, int v, int cap) {
        Edge* uv = new Edge(u, v, cap);
        Edge* vu = new Edge(v, u, 0);
        
        uv->dual = vu;
        vu->dual = uv;

        return make_pair(uv, vu);
    }

    int residual() { return cap - flow; }

    void augment(int amount) {
        flow += amount;
        dual->flow -= amount;
    }

};

class MaxFlow {
  public:
    MaxFlow(int n, int source, int sink) : _n(n), _g(n), _source(source), _sink(sink), _flow(0) {}
    
    ~MaxFlow() {
        for (auto edge_list : _g) {
            for (auto edge : edge_list) {
                delete edge;
            }
        }
    }

    vector<vector<Edge*>> graph() { return _g; }

    int flow() { return _flow; }

    void addEdge(int u, int v, int cap) {
        auto edges = Edge::createEdgeAndDual(u, v, cap);
        auto uv = edges.first;
        auto vu = edges.second;
        _g[uv->u].push_back(uv);
        _g[vu->u].push_back(vu);
    }

    int maximumFlow() {
        while (tryAugment() > 0);
        return flow();
    }
    
    vector<Edge*> findMinCut() {
        vector<Edge*> res;
        _visit = vector<bool>(_n);
        dfsForMinCut(_source);
        for (auto edges : _g) {
            for (auto e : edges) {
                if (_visit[e->u] && !_visit[e->v] && e->cap > 0) {
                    res.push_back(e);
                }
            }
        }
        return res;
    }

  private:
    vector<Edge*> findAugmentPath() {
        vector<Edge*> path;
        vector<Edge*> from(_n);
        queue<int> q;
        q.push(_source);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (auto e : _g[u]) {
                if (e->residual() > 0 && from[e->v] == NULL) {
                    q.push(e->v);
                    from[e->v] = e;
                }
            }
        }
        buildPath(path, from, _source, _sink);
        return path;
    }

    int tryAugment() {
        auto path = findAugmentPath();
        auto volume = pathVolume(path);
        for (auto e : path) e->augment(volume);
        _flow += volume;
        return volume;
    }

    int pathVolume(const vector<Edge*>& path) {
        if (path.size() == 0) return 0;
        int volume = INF;
        for (auto e : path) volume = min(volume, e->residual());
        return volume;
    }
    
    void buildPath(vector<Edge*>& path, const vector<Edge*>& from, int s, int v) {
        if (v != s && from[v] != NULL) {
            buildPath(path, from, s, from[v]->u);
            path.push_back(from[v]);
        }
    }


    void dfsForMinCut(int u) {
        if (_visit[u]) {
            return;
        }
        _visit[u] = true;
        for (auto e : _g[u]) {
            if (e->residual() > 0) {
                dfsForMinCut(e->v);
            }
        }
    }

  private:
    int _n;
    int _source;
    int _sink;
    int _flow;
    vector<vector<Edge*>> _g;
    vector<bool> _visit;
};


int main() {
    int V, E, Source, Sink;
    scanf("%d%d", &V, &E);
    scanf("%d%d", &Source, &Sink);

    MaxFlow mf(2 * V + 2, Source, Sink + V);

    for (int u = 1; u <= V; ++u) {
        int cap;
        scanf("%d", &cap);
        mf.addEdge(u, V + u, cap);
    }

    for (int ei = 0; ei < E; ++ei) {
        int u, v;
        scanf("%d%d", &u, &v);
        mf.addEdge(V + u, v, INF);
        mf.addEdge(V + v, u, INF);
    }
    mf.maximumFlow();
    vector<int> res;
    for (auto e : mf.findMinCut()) {
        res.push_back(e->u);
    }
    sort(res.begin(), res.end());
    for (auto u : res) {
        printf("%d ", u);
    }
    printf("\n");
    
    return 0;
}

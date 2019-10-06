class Graph {
public:
    Graph(int n) : n(n), edges(n), visited(n), finished(n) {}

    void addEdge(int v1, int v2) {
        edges[v1].push_back(v2);
    }

    vector<int> getSorted() {
        vector<pair<int, int>> a;
        for (int i = 0; i < n; ++i) {
            a.emplace_back(finished[i], i);
        }
        sort(a.rbegin(), a.rend());
        vector<int> res;
        for (int i = 0; i < n; ++i) {
            res.push_back(a[i].second);
        }
        return res;
    }

    // topological sort, return true when a cycle is detected.
    bool tsort() {
        visitCount = 0;
        finishCount = 0;
        for (int v = 0; v < n; ++v) {
            if (dfs(v)) return true;
        }
        return false;
    }
private:
    bool dfs(int v) {
        if (finished[v] > 0) return false;
        if (visited[v] > 0) return true;
        
        
        visited[v] = ++visitCount;

        for (int v2 : edges[v]) {
            if (dfs(v2)) return true;
        }

        finished[v] += ++finishCount;
        return false;
    }

private:
    int n;
    vector<vector<int>> edges;
    vector<int> visited;
    vector<int> finished;
    int visitCount;
    int finishCount;
};

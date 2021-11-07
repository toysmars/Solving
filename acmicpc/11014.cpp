// acmicpc 11014
//
// bipartite matching
//
// For a graph G,
// Let I(G) to be the number of independent set, and
// Let C(G) to be the number of vertex cover, then
// |V| = I(G) + C(G)
// When the graph G is a bipartite graph,
// Let M(G) to be the number of maximum mathcing, then
// C(G) = M(G), thus
// |V| = I(G) + M(G), therefore
// I(G) = |V| - M(G)

#include <bits/stdc++.h>
using namespace std;

class BipartiteGraph {
  public:
    BipartiteGraph(int left_size, int right_size)
      : _l_size(left_size), _r_size(right_size), _g(left_size) {
    }

    void addEdge(int li, int ri) {
        _g[li].push_back(ri);
    }

    int maximumMatching() {
        int matches = 0;
        _l_match = vector<int>(_l_size, -1);
        _r_match = vector<int>(_r_size, -1);
        for (int li = 0; li < _l_size; ++li) {
            _visited = vector<bool>(_l_size, false);
            if (augment(li)) {
                ++matches;
            }
        }
        return matches;
    }

  private:
    bool augment(int li) {
        if (_visited[li]) {
            return false;
        }
        _visited[li] = true;
        for (int ri : _g[li]) {
            if (_r_match[ri] == -1 || augment(_r_match[ri])) {
                _l_match[li] = ri;
                _r_match[ri] = li;
                return true;
            }
        }
        return false;
    }

  private:
    int _l_size;
    int _r_size;
    vector<vector<int>> _g;
    vector<int> _l_match;
    vector<int> _r_match;
    vector<bool> _visited;
};

int toNodeId(int n, int y, int x) {
    return n * (x / 2) + y;
}

char C[81][81];
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; ++i) {
            scanf("%s", C[i]);
        }
        BipartiteGraph bg(n * ((m + 1) / 2), n * (m / 2));
        int nodes = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                nodes += C[i][j] == '.';
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; j += 2) {
                if (C[i][j] == 'x') continue;
                if (i > 0 && j > 0 && C[i-1][j-1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i-1, j-1));
                if (j > 0 && C[i][j-1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i, j-1));
                if (i < n-1 && j > 0 && C[i+1][j-1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i+1, j-1));
                if (i > 0 && j < m-1 && C[i-1][j+1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i-1, j+1));
                if (j < m-1 && C[i][j+1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i, j+1));
                if (i < n-1 && j < m-1 && C[i+1][j+1] =='.')
                    bg.addEdge(toNodeId(n, i, j), toNodeId(n, i+1, j+1));
            }
        }
        int matches = bg.maximumMatching();
        printf("%d\n", nodes - matches);
    }
    return 0;
}

// acmicpc 9495
// 
// bipartite matching

#include <cstdio>
#include <vector>
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

int N;
char B[51][51];
int A[51][51];

int dy[] = { 0, 1, 0, -1 };
int dx[] = { -1 ,0, 1, 0 };

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; ++i) {
        scanf("%s", B[i]);
    }
    int whitec = 0;
    int emptyc = 0;
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (B[y][x] == 'o') {
                A[y][x] = whitec++;
            } else if (B[y][x] == '.') {
                A[y][x] = emptyc++;
            }
        }
    }
    BipartiteGraph bg(whitec, emptyc);
    for (int y = 0; y < N; ++y) {
        for (int x = 0; x < N; ++x) {
            if (B[y][x] == 'o') {
                for (int k = 0; k < 4; ++k) {
                    int ny = y + dy[k];
                    int nx = x + dx[k];
                    if (ny < 0 || ny >= N || nx < 0 || nx >= N) continue;
                    if (B[ny][nx] == '.') {
                        bg.addEdge(A[y][x], A[ny][nx]);
                    }
                }
            }
        }
    }
    printf("%d\n", whitec + emptyc - bg.maximumMatching());
    
    return 0;
}


// bipartite matching
// 이분매칭
// Examples:
//  * https://www.acmicpc.net/problem/3295
//  * https://www.acmicpc.net/problem/9295
//  * https://www.acmicpc.net/problem/11014
//  * https://www.acmicpc.net/problem/14216

#include <bits/stdc++.h>
using namespace std;

struct BipartiteMatch {
    BipartiteMatch(int left_size, int right_size)
      : _l_size(left_size), _r_size(right_size), _g(left_size) {
    }

    void addEdge(int li, int ri) {
        _g[li].push_back(ri);
    }

    int solve() {
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

    int _l_size;
    int _r_size;
    vector<vector<int>> _g;
    vector<int> _l_match;
    vector<int> _r_match;
    vector<bool> _visited;
};

class Comparator {
public:
    Comparator(const string& s) : str(s) {}
    bool operator()(int a, int b) {
        return str[a] < str[b];
    }
private:
    string str;
};

// Solve suffix array using Manber Myers algorithm
// https://dl.acm.org/citation.cfm?id=320176.320218
class SuffixArraySolver {
public:
    void solve(const string& str) {
        int n = str.size();
        pos = vector<int>(n);
        rank = vector<int>(n);
        
        vector<int> count(n);
        vector<int> next(n);
        vector<bool> bh(n);
        vector<bool> b2h(n);

        // initial value for pos
        for (int i = 0; i < n; ++i) {
            pos[i] = i;
        }
        Comparator comparator(str);
        sort(pos.begin(), pos.end(), comparator);

        // initial value for bh and b2h;
        for (int i = 0; i < n; ++i) {
            bh[i] = i == 0 || str[pos[i]] != str[pos[i - 1]];
            b2h[i] = false;
        }

        // interate over h = [1, 2, 4, 8, ..., 2^k, ...]
        for (int h = 1; h < n; h <<= 1) {
            // buckets
            int i = 0;
            int j = 0;
            int buckets = 0;
            while (i < n) {
                j = i + 1;
                while (j < n && !bh[j]) {
                    ++j;
                }
                i = next[i] = j;
                ++buckets;
            }
            if (buckets == n) {
                break;
            }
            // ranks
            for (int i = 0; i < n; i = next[i]) {
                count[i] = 0;
                for (int j = i; j < next[i]; ++j) {
                    rank[pos[j]] = i ;
                }
            }
            // 2h based on h
            count[rank[n - h]] += 1;
            b2h[rank[n - h]] = true;
            for (int i = 0; i < n; i = next[i]) {
                for (int j = i; j < next[i]; ++j) {
                    int d = pos[j] - h;
                    if (d >= 0) {
                        rank[d] += count[rank[d]]++;
                        b2h[rank[d]] = true;
                    }
                }
                for (int j = i; j < next[i]; ++j) {
                    int d = pos[j] - h;
                    if (d >= 0 && b2h[rank[d]]) {
                        for (int k = rank[d] + 1; k < n && !bh[k] && b2h[k]; ++k) {
                            b2h[k] = false;
                        }
                    }
                }
            }
            for (int i = 0; i < n; ++i) {
                pos[rank[i]] = i;
                bh[i] = bh[i] || b2h[i];
            }
        }
        for (int i = 0; i < n; ++i) {
            rank[pos[i]] = i;
        }
    }

    const vector<int>& getSuffixArray() {
        return pos;
    }

    const vector<int>& getRank() {
        return rank;
    }

private:
    vector<int> pos;
    vector<int> rank;
};

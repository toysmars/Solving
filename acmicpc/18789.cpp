// acmicpc 18789
//
// SA
// Simulated annealing

#include <bits/stdc++.h>
using namespace std;

const int R = 8;
const int C = 14;
const int MAX_N = 8140;
int T[R][C];
int Best[R][C];
bool V[MAX_N + 10];

vector<pair<int, int>> Pos;

const int MAX_QSIZE = 50000;
pair<pair<short, short>, int> Q[MAX_QSIZE];
int qr, qf;

void bfs(int y, int x) {
    qf = 0;
    qr = 0;
    Q[qr++] = make_pair(make_pair(y, x), T[y][x]);
    for (int k = 0; k < 3; ++k) {
        int qsize = qr - qf;
        while (qsize--) {
            auto it = Q[qf++];
            int cy = it.first.first;
            int cx = it.first.second;
            int v = it.second;
            if (v <= MAX_N) {
                V[v] = true;
            }
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dy == 0 && dx == 0) continue;
                    int ny = cy + dy;
                    int nx = cx + dx;
                    if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
                    Q[qr++] = make_pair(make_pair(ny, nx), 10 * it.second + T[ny][nx]);
                }
            }
        }
    }
    while (qf < qr) {
        int v = Q[qf++].second;
        if (v <= MAX_N) {
            V[v] = true;
        }
    }
}

int Judge() {
    memset(V, 0, sizeof(V));
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            bfs(y, x);
        }
    }
    int ans = 0;
    for (int x = 1; x <= MAX_N; ++x) {
        ans += V[x];
    }
    return ans;
}

void WriteCurrent(bool isBest) {
    const char* filename = isBest ? "best.txt" : "current.txt";
    auto score = Judge();
    auto fout = fopen(filename, "w");
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            fprintf(fout, "%d", T[y][x]);
        }
        fprintf(fout, "\n");
    }
    fprintf(fout, "\n%d\n", score);
    fclose(fout);
}

int BestScore;
int JudgeAndUpdateBest(int opt) {
    int score = Judge();
    if (score > BestScore) {
        BestScore = score;
        printf("BEST %d with opt=%d\n", BestScore, opt);
        WriteCurrent(true);
    }
    return score;
}

void SA_oneOpt() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> disY(0, R - 1);
    uniform_int_distribution<int> disX(0, C - 1);
    uniform_int_distribution<int> disV(0, 9);
    uniform_int_distribution<int> disT(0, 1000000);

    vector<pair<int, int>> tp[4];
    double tr[4] = { 0.25, 0.25, 0.25, 0.25 };
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            int tier = min({y, R - y - 1, x, C - x - 1});
            tp[tier].emplace_back(y, x);
        }
    }
    int tc[4] = {0};

    int baseScore = Judge();

    int epoch = 0;
    int saturation = 0;
    int epochCycle = 400;
    double sa_t = 0.5;
    double sa_k = 0.05;

    while (BestScore < MAX_N) {
        int rt = disT(gen);
        int tier = 0;
        double ts = tr[0];
        while (ts * 1000000 < rt) ts += tr[++tier];
        tier = min(3, tier);
        tc[tier]++;

        int ti = disT(gen) % tp[tier].size();

        int ry = tp[tier][ti].first;
        int rx = tp[tier][ti].second;
        int rv = disV(gen);
        if (T[ry][rx] == rv) continue;

        int ov = T[ry][rx];
        T[ry][rx] = rv;
        int newScore = JudgeAndUpdateBest(1);

        if (newScore >= baseScore || exp((newScore - baseScore) * sa_k / sa_t) * 1000000 > disT(gen)) {
            if (newScore > baseScore) {
                WriteCurrent(false);
                saturation = 0;
            }
            baseScore = newScore;
        } else {
            T[ry][rx] = ov;
            saturation++;
        }

        if (epoch++ >= epochCycle) {
            sa_t *= 0.995;
            sa_k -= 0.00001;
            epochCycle *= 1.003;
            epoch = 0;
            tr[0] = min(0.60, tr[0] + 0.0015);
            tr[2] = max(0.10, tr[2] - 0.0005);
            tr[3] = max(0.05, tr[3] - 0.001);

            printf("score: %d, base:%d, temperature: %lf, k: %lf, pscore: %lf\n", newScore, baseScore, sa_t, sa_k, exp((newScore - baseScore) * sa_k / sa_t) * 1000000);
            //printf("%d %d %d %d %lf\n", tc[0], tc[1], tc[2], tc[3], tr[0] + tr[1] + tr[2] + tr[3]);
        }
        if (saturation >= 15 * epochCycle) {
            sa_t += 0.08;
            saturation = 0;
            epochCycle = 400;
            tr[0] = 0.25;
            tr[1] = 0.25;
            tr[2] = 0.25;
            tr[3] = 0.25;
        }
        if (sa_k < 0.0001) {
            sa_k = 0.01;
        }
    }
}

int main() {
    for (int y = 0; y < R; ++y) {
        char line[15];
        scanf("%s", line);
        for (int x = 0; x < C; ++x) {
            T[y][x] = line[x] - '0';
            Pos.emplace_back(y, x);
        }
    }

    printf("Initial Score: %d\n", JudgeAndUpdateBest(0));

    SA_oneOpt();

    return 0;
}

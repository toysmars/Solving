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

bool Find(int v) {
    qf = 0;
    qr = 0;
    for (int y = 0; y < R; ++y) {
        for (int x = 0; x < C; ++x) {
            if (T[y][x] == v % 10) {
                Q[qr++] = make_pair(make_pair(y, x), T[y][x]);
            }
        }
    }
    while (qr - qf) {
        v /= 10;
        if (v == 0) {
            return true;
        }
        int qsize = qr - qf;
        while (qsize--) {
            auto it = Q[qf++];
            int cy = it.first.first;
            int cx = it.first.second;
            int cv = it.second;
            for (int dy = -1; dy <= 1; ++dy) {
                for (int dx = -1; dx <= 1; ++dx) {
                    if (dy == 0 && dx == 0) continue;
                    int ny = cy + dy;
                    int nx = cx + dx;
                    if (ny < 0 || ny >= R || nx < 0 || nx >= C) continue;
                    if (T[ny][nx] == v % 10) {
                        Q[qr++] = make_pair(make_pair(ny, nx), 10 * cv + T[ny][nx]);
                    }
                }
            }
        }
    }
    return false;
}

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

    int baseScore = Judge();

    int epoch = 0;
    int saturation = 0;
    const int epochCycle = 2000;
    double sa_t = 0.5;
    double sa_k = 0.05;

    while (BestScore < MAX_N) {
        int ry = disY(gen);
        int rx = disX(gen);
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

        if (++epoch % epochCycle == 0) {
            sa_t *= 0.995;
            sa_k -= 0.00001;

            printf("score: %d, base:%d, temperature: %lf, k: %lf, pscore: %lf\n", newScore, baseScore, sa_t, sa_k, exp((newScore - baseScore) * sa_k / sa_t) * 1000000 );
            fflush(stdout);
        }
        if (saturation >= 5 * epochCycle) {
            sa_t += 0.05;
            saturation = 0;
        }
        if (sa_k < 0.0001) {
            sa_k = 0.01;
        }
    }
}

int main() {

    auto fin = fopen("current.txt", "r");
    for (int y = 0; y < R; ++y) {
        char line[15];
        fscanf(fin, "%s", line);
        for (int x = 0; x < C; ++x) {
            T[y][x] = line[x] - '0';
            Pos.emplace_back(y, x);
        }
    }
    fclose(fin);

    printf("Initial Score: %d\n", JudgeAndUpdateBest(0));

    SA_oneOpt();

    return 0;
}

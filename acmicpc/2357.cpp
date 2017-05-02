// https://www.acmicpc.net/problem/2357
// * Segment Tree
// * RMQ
// * update and query

import java.util.*;
import java.util.function.*;

class RMQ<T> {
    public RMQ(int n, BiFunction<Optional<T>, Optional<T>, Optional<T>> f) {
        this.n = n;
        this.t = new ArrayList<Optional<T>>();
        this.f = f;
        for (int i = 0; i <= 4 * n; ++i) {
            this.t.add(Optional.empty());
        }
    }

    public void update(int i, T x) {
        update(i, x, 1, 1, n + 1);
    }

    private Optional<T> update(int i, T x, int idx, int l, int r) {
        if (l > i || r <= i || l >= r) {
            return Optional.empty();
        }
        int len = r - l;
        if (len == 1) {
            this.t.set(idx, Optional.of(x));
            return t.get(idx);
        }
        Optional<T> res1 = update(i, x, idx * 2 + 0, l, l + len / 2);
        Optional<T> res2 = update(i, x, idx * 2 + 1, l + len / 2, r);
        t.set(idx, this.f.apply(t.get(idx), this.f.apply(res1, res2)));
        return t.get(idx);
    }

    public Optional<T> query(int ql, int qr) {
        return query(ql, qr, 1, 1, n + 1);
    }

    private Optional<T> query(int ql, int qr, int idx, int l, int r) {
        if (l >= qr || r <= ql || l >= r) {
            return Optional.empty();
        }
        if (ql <= l && qr >= r) {
            return this.t.get(idx);
        }
        int len = r - l;
        Optional<T> res1 = query(ql, qr, idx * 2 + 0, l, l + len / 2);
        Optional<T> res2 = query(ql, qr, idx * 2 + 1, l + len / 2, r);
        return this.f.apply(res1, res2);
    }

    private int n;
    private ArrayList<Optional<T>> t;
    private BiFunction<Optional<T>, Optional<T>, Optional<T>> f;
}

class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int n = scanner.nextInt();
        int m = scanner.nextInt();
        RMQ<Integer> rmq1 = new RMQ<Integer>(n, (a, b) -> {
            if (a.isPresent() && b.isPresent()) {
                return Optional.of(Math.min(a.get(), b.get()));
            } else if (a.isPresent()) {
                return a;
            } else if (b.isPresent()) {
                return b;
            } else {
                return Optional.empty();
            }
        });
        RMQ<Integer> rmq2 = new RMQ<Integer>(n, (a, b) -> {
            if (a.isPresent() && b.isPresent()) {
                return Optional.of(Math.max(a.get(), b.get()));
            } else if (a.isPresent()) {
                return a;
            } else if (b.isPresent()) {
                return b;
            } else {
                return Optional.empty();
            }
        });
        for (int i = 1; i <= n; ++i) {
            int x = scanner.nextInt();
            rmq1.update(i, x);
            rmq2.update(i, x);
        }
        for (int i = 0; i < m; ++i) {
            int a = scanner.nextInt();
            int b = scanner.nextInt();
            System.out.printf("%d %d\n", rmq1.query(a, b + 1).get(), rmq2.query(a, b + 1).get());
        }
    }
}

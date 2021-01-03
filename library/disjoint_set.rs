struct DisjointSet {
    s: Vec<usize>,
    r: Vec<usize>,
}

impl DisjointSet {
    pub fn new(n: usize) -> Self {
        Self {
            s: (0..n).collect::<Vec<_>>(),
            r: vec![0; n]
        }
    }
    pub fn find(&mut self, x: usize) -> usize {
        if self.s[x] != x {
            self.s[x] = self.find(self.s[x]);
        }
        self.s[x]
    }
    pub fn union(&mut self, x: usize, y: usize) {
        let sx = self.find(x);
        let sy = self.find(y);
        if sx == sy {
            return;
        }
        let (sh, sl) = if self.r[sx] > self.r[sy] {
            (sx, sy)
        } else {
            (sy, sx)
        };
        self.s[sl] = sh;
        if self.r[sh] == self.r[sl] {
            self.r[sh] += 1;
        }
    }
}

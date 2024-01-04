use core::ops::Index;
use rand::thread_rng;
use rand::RngCore;
use std::fmt;


// like c, use row-major order
pub type NeuronVector = Vec<bool>;
pub struct ConnectionMatrix {
    m: usize,
    n: usize,
    array: Vec<f64>
}

impl ConnectionMatrix {
    pub fn new(m: usize, n: usize) -> Self {
        let mut rng = thread_rng();
        let mut tmp = Vec::<f64>::with_capacity(n * m);
        for i in 0..n * m {
            tmp.push(rng.next_u64() as f64);
        }
        Self {
            m,
            n,
            array: tmp 
        }
    }
    pub fn rows(&self) -> Vec<Vec<f64>> {
        let mut res = vec![vec![0.0; self.n]; self.m];
        for i in 0..self.array.len() {
            let row: usize = i / self.m;
            let col: usize = i % self.m;
            res[row][col] = self.array[i];
        }
        res
    }
    pub fn cols(&self) -> Vec<Vec<f64>> {
        let mut res = vec![vec![0.0; self.m]; self.n];
        for i in 0..self.array.len() {
            let row: usize = i / self.m;
            let col: usize = i % self.m;
            res[col][row] = self.array[i];
        }
        res
    }
}
        
// first index -- get the array of cols for each row
impl Index<usize> for ConnectionMatrix {
    type Output = [f64];
    fn index(&self, index: usize) -> &Self::Output {
        let beg = self.n * index;
        let end = self.n + beg;
        &self.array[beg..end]
        }
}
// second index -- just index into that

// pretty-print for debugging
impl fmt::Debug for ConnectionMatrix {
    fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
        writeln!(f, "\nm={} row x n={} col matrix", self.m, self.n).ok();
        for row in 0..self.m {
            write!(f, "\t").ok();
            for col in 0..self.n {
                write!(f, " {}", self[row][col]).ok();
                }
            write!(f, "\n").ok();
            }
        Ok(())
    }
}

pub fn nv_row_dot(row : &[f64], v : &[bool]) -> Option<f64> {
    if row.len() != v.len() {return None}
    let mut total = 0f64;
    for i in 0..row.len() {
        total += row[i] * v[i] as u8 as f64;
    }
    Some(total)
}

pub fn activation(strength: f64) -> bool {
    return true
}

// multiply v x a
pub fn apply_connections(a: ConnectionMatrix, v: NeuronVector) -> Option<NeuronVector> {
    if a.m != v.len() { return None }
    let mut res = Vec::<bool>::with_capacity(a.m);
    for row in a.rows() {
        let dot = nv_row_dot(&row, &v);
        dbg!(&dot);
        let res = activation(dot);
        dbg!(&res);

    }
    Some(res)
}



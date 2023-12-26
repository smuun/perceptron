use core::ops::Index;

// basic matrices and matrix math

// mxn matrix: m rows, n cols
// like c, use row-major order

const DIMS 
pub struct Matrix {
    m: usize,
    n: usize,
    array: [f64; 4096]
}

// first index -- get the array of cols for each row
impl Index<usize> for Matrix {
    type Output = [f64; Matrix::n];
    fn index(&self, index: usize) -> &Self::Output {
        let beg = self.n * index;
        let end = self.n + beg;
        &self.array[beg..end]
        }
}

// second index -- get the number at row, column

use core::ops::Index;
use std::ops::{Add, Div, Mul, Sub, Rem}; 
use std::marker::Copy;
use std::cmp::{PartialEq, PartialOrd};

// basic matrices and matrix math

// mxn matrix: m rows, n cols
// like c, use row-major order

type MatrixElement = T where T:
    Add
    + Div
    + Mul
    + Sub
    + Rem
    + Copy
    + PartialEq
    + PartialOrd;

pub struct Matrix<T>
// restrict to number types
where T: 
    Add
    + Div
    + Mul
    + Sub
    + Rem
    + Copy
    + PartialEq
    + PartialOrd
{
    m: usize,
    n: usize,
    array: Vec<T>
}

impl Matrix<T> {
        pub fn new(m: usize, n: usize) -> Self {
            Self {
                m,
                n,
                data: vec![0f64, n * m]
            }
    }
}

// first index -- get the array of cols for each row
impl<T> Index<usize> for Matrix<T> {
    type Output = [T];
    fn index(&self, index: usize) -> &Self::Output {
        let beg = self.n * index;
        let end = self.n + beg;
        &self.array[beg..end]
        }
}
// second index -- just index into that

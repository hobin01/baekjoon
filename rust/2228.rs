use std::io::{stdin, Read};
use std::fmt::Write;
use std::cmp::{max, min};

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();

    let n = input.next().unwrap().parse::<usize>().unwrap();
    let m = input.next().unwrap().parse::<usize>().unwrap();
    
    let mut contains: Vec<Vec<i32>> = vec![vec![i32::MIN; m+1]; n+1];
    let mut not_contains: Vec<Vec<i32>> = vec![vec![i32::MIN; m+1]; n+1];

    for i in 0..(n+1) {
        contains[i][0] = 0;
        not_contains[i][0] = 0;
    }

    for i in 1..(n+1) {
        let num = input.next().unwrap().parse::<i32>().unwrap();

        let tmp = (i+1)/2;
        let interval = min(m, tmp);
        for j in 1..(interval+1) {
            contains[i][j] = max(contains[i-1][j], not_contains[i-1][j-1]) + num;
            not_contains[i][j] = max(contains[i-1][j], not_contains[i-1][j]);
        }
    }

    let res = max(contains[n][m], not_contains[n][m]);
    print!("{}", res);
}

// ref : https://ddiyeon.tistory.com/62
use std::cmp::max;
use std::io::{stdin, Read};
use std::fmt::Write;

// 0,1,2,...,m 에 대한 permutation
// ex. m=2 => 012,021,102,120,201,210
// start : 0, end : m, v : vector for permutation, res : result of permutation
fn permutation(start: usize, end: usize, v: &mut Vec<usize>, res: &mut Vec<Vec<usize>>) {
    if start == end {
        res.push(v.clone());
    } else {
        for i in start..end {
            v.swap(start, i);
            permutation(start+1, end, v, res);
            v.swap(start, i);
        }
    }
}

fn calc(v: &mut Vec<i32>, perm: &Vec<usize>, opers: &Vec<char>) -> i32 {
    let mut order: Vec<(usize, usize)> = Vec::new();
    for (idx, val) in perm.iter().enumerate() {
        order.push((*val, idx));
    }
    order.sort();

    let mut visited: Vec<bool> = vec![false; v.len()];

    for val in order.iter() {
        let mut idx = (*val).1;
        let oper_idx = idx;
        
        while visited[idx] {
            idx -= 1;
        }

        let num1 = v[idx];
        let num2 = v[oper_idx + 1];

        let op = opers[oper_idx];
        match op {
            '+' => v[idx] = num1 + num2,
            '-' => v[idx] = num1 - num2,
            '*' => v[idx] = num1 * num2,
            _   => v[idx] = 0
        }

        visited[oper_idx + 1] = true;
    }

    let result = v[0];
    result
}

fn main() {

    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();

    let n = input.next().unwrap().parse::<usize>().unwrap();
    let expr = input.next().unwrap().parse::<String>().unwrap();

    // v : vector for permutation
    // expr_v : expr nums to vector
    // res : vector of result of permutation
    let mut v: Vec<usize> = Vec::new();
    let mut expr_v: Vec<i32> = Vec::new();
    let mut opers: Vec<char> = Vec::new();
    let mut perm_v: Vec<Vec<usize>> = Vec::new();

    let start = 0usize;
    let end = n / 2;

    for i in 0..end {
        v.push(i)
    }

    permutation(start, end, &mut v, &mut perm_v);

    for c in expr.chars() {
        if c >= '0' && c <= '9' {
            let num = c as i32;
            let zero = '0' as i32;
            expr_v.push(num - zero);
        } else {
            opers.push(c);
        }
    }

    let mut expr_tmp = expr_v.clone();
    let mut result = calc(&mut expr_tmp, &perm_v[0], &opers);

    for perm in perm_v.iter() {
        let mut expr_tmp = expr_v.clone();
        result = max(result, calc(&mut expr_tmp, perm, &opers));
    }

    writeln!(output, "{}", result).unwrap();
    print!("{}", output);
}

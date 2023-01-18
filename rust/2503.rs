use std::io::{stdin, Read};
use std::fmt::Write;

fn check(vec: &mut Vec<usize>, num: usize, s: usize, b: usize) {

    let a1 = num / 100;
    let b1 = (num - a1 * 100) / 10;
    let c1 = num % 10;

    let mut removed: Vec<usize> = Vec::new();

    for i in 0..vec.len() {
        let a2 = (vec[i]) / 100;
        let b2 = (vec[i] - a2 * 100) / 10;
        let c2 = (vec[i]) % 10;

        let mut strike: usize = 0;
        let mut ball: usize = 0;

        // strike 체크
        if a1 == a2 {
            strike += 1;
        } 
        if b1 == b2 {
            strike += 1;
        }
        if c1 == c2 {
            strike += 1;
        }

        // ball 체크
        if a2 == b1 || a2 == c1 {
            ball += 1;
        }
        if b2 == a1 || b2 == c1 {
            ball += 1;
        }
        if c2 == a1 || c2 == b1 {
            ball += 1;
        }

        if strike == s && ball == b {
            removed.push(vec[i]);
        }
    }

    vec.clear();
    for r in removed {
        vec.push(r);
    }
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();

    let mut vec: Vec<usize> = Vec::new();
    for i in 0usize..1000 {
        let a = i / 100;
        let b = (i - a * 100) / 10;
        let c = i % 10;
        if a == 0 || b == 0 || c == 0 {
            continue;
        }
        if a == b || b == c || c == a {
            continue;
        }
        vec.push(i);
    }

    let n: usize = input.next().unwrap();
    for _ in 0..n {
        let num = input.next().unwrap();
        let strike = input.next().unwrap();
        let ball = input.next().unwrap();

        check(&mut vec, num, strike, ball);
    }

    writeln!(output, "{}", vec.len()).unwrap();
    print!("{}", output);
}
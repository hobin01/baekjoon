use std::io::{stdin, Read};
use std::fmt::Write;

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();
    let n = input.next().unwrap().parse::<u32>().unwrap();
    let mut vec: Vec<u32> = vec![0; n as usize];

    for i in 0..n {
        let num = input.next().unwrap().parse::<u32>().unwrap();
        vec[i as usize] = num;
    }

    // 올라가는 거 체크 
    let mut vec1: Vec<u32> = vec![0; n as usize];
    vec1[0] = 1;
    for i in 1..(n as usize) {
        if vec[i] >= vec[i-1] {
            vec1[i] = vec1[i-1] + 1;
        } else {
            vec1[i] = 1;
        }
    }

    // 내려가는 거 체크
    let mut vec2: Vec<u32> = vec![0; n as usize];
    vec2[0] = 1;
    for i in 1..(n as usize) {
        if vec[i] <= vec[i-1] {
            vec2[i] = vec2[i-1] + 1;
        } else {
            vec2[i] = 1;
        }
    }

    let res1 = vec1.iter().max().unwrap();
    let res2 = vec2.iter().max().unwrap();

    print!("{}", std::cmp::max(*res1, *res2));
}

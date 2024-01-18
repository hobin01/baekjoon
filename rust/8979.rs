use std::io::{stdin, Read};
use std::fmt::Write;
use std::cmp::Ordering;

#[derive(Debug)]
struct Medal {
    country: u32,
    gold: u32,
    silver: u32,
    bronze: u32,
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();
    
    let n = input.next().unwrap().parse::<u32>().unwrap();
    let k = input.next().unwrap().parse::<u32>().unwrap();

    let mut vec: Vec<Medal> = Vec::new();
    for i in 1..(n+1) {
        let c = input.next().unwrap().parse::<u32>().unwrap();
        let g = input.next().unwrap().parse::<u32>().unwrap();
        let s = input.next().unwrap().parse::<u32>().unwrap();
        let b = input.next().unwrap().parse::<u32>().unwrap();

        vec.push(Medal{country: c, gold: g, silver: s, bronze: b});
    }

    vec.sort_by(|a, b| {
        a.gold.partial_cmp(&b.gold).unwrap_or(Ordering::Equal)
        .then_with(|| a.silver.cmp(&b.silver))
        .then_with(|| a.bronze.cmp(&b.bronze))
    });

    let mut idx: u32 = 0;
    for i in 0..n {
        let c = vec[i as usize].country;
        if c == k {
            idx = i;
            break;
        }
    }

    let idx = idx as usize;
    let mut res = 0 as u32;
    for i in (0..n).rev() {
        let j = i as usize;
        if (vec[idx].gold == vec[j].gold) && (vec[idx].silver == vec[j].silver) && (vec[idx].bronze == vec[j].bronze) {
            res = n - i;
            break;
        }
    }

    print!("{}", res);
}

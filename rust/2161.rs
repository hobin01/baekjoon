use std::fmt::Write;
use std::io::{stdin, Read};

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();
    let mut output = String::new();
    
    let n: usize = input.next().unwrap();
    let mut vec: Vec<usize> = Vec::new();
    for i in 1..(n+1) {
        vec.push(i);
    }

    let mut cnt = n;
    loop {
        output.push_str(&vec[0].to_string());
        output.push_str(" ");
        vec.remove(0);
        cnt -= 1;
        if cnt == 0 {
            break;
        }

        let num = vec[0];
        vec.push(num);
        vec.remove(0);
    }

    println!("{}", output);
}
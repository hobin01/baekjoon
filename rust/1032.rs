use std::fmt::Write;
use std::io::{stdin, Read};

fn check(vec: Vec<String>) -> String {
    let mut result = String::new();

    let first = vec[0].as_bytes();
    let first_size = first.len();
    let vec_size = vec.len();

    for i in 0..first_size {
        
        let mut chk = true;
        for j in 1..vec_size {
            let s = vec[j].as_bytes();
            if first[i] != s[i] {
                chk = false;
                break;
            }
        }

        if chk == false {
            result.push('?');
        } else {
            result.push(first[i] as char);
        }
    }

    result
}

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();
    let mut output = String::new();
    
    let N: String = input.next().unwrap();
    let N: usize = N.parse().unwrap();

    let mut vec: Vec<String> = Vec::new();
    vec = input.by_ref().take(N).collect();
    
    let result = check(vec);
    writeln!(output, "{}", result).unwrap();
    print!("{}", output);
}
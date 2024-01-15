use std::io::{stdin, Read};
use std::fmt::Write;

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();

    let n = input.next().unwrap().parse::<i32>().unwrap();

    let mut vec = Vec::new();

    for _ in 0..n {
        let num = input.next().unwrap().parse::<i32>().unwrap();
        vec.push(num);
    }

    let num = input.next().unwrap().parse::<i32>().unwrap();

    let mut res = 0;
    for v in vec {
        if v == num {
            res += 1;
        }
    }

    writeln!(output, "{}", res).unwrap();
    print!("{}", output);
}

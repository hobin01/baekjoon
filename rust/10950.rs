use std::io::{stdin, Read};
use std::fmt::Write;

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();
    let t: i32 = input.next().unwrap();
    for _ in 0..t {
        let a = input.next().unwrap();
        let b = input.next().unwrap();
        writeln!(output, "{}", a + b).unwrap();
    }

    print!("{}", output);
}
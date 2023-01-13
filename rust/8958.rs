use std::io::{stdin, Read};
use std::fmt::Write;

fn ox(s: &str) -> i32 {
    let mut result: i32 = 0;
    let mut cnt: i32 = 0;

    for c in s.chars() {
        if c == 'O' {
            cnt += 1;
            result += cnt;
        }
        else {
            cnt = 0;
        }
    }

    result
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();
    let t: String = input.next().unwrap();
    let n = t.parse().unwrap();

    for _ in 0..n {
        let s = input.next().unwrap();
        let result = ox(s.as_str());
        writeln!(output, "{}", result).unwrap();
    }

    print!("{}", output);
}

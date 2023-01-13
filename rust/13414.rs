use std::io::{stdin, Read};
use std::fmt::Write;
use std::collections::BTreeMap;

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();

    let K: String = input.next().unwrap();
    let k: usize = K.parse().unwrap();
    let L = input.next().unwrap();
    let l: usize = L.parse().unwrap();

    let mut map = BTreeMap::new();

    for i in 0..l {
        let num: String = input.next().unwrap();
        map.insert(num, i);
    }

    let mut tmp = BTreeMap::new();
    for (k, v) in map {
        tmp.insert(v, k);
    }

    let mut cnt: usize = 0;
    for (key, val) in tmp {
        if cnt == k {
            break;
        }
        cnt += 1;
        writeln!(output, "{}", val).unwrap();
    }

    print!("{}", output);
}
use std::io::{stdin, Read};
use std::fmt::Write;

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let mut input = input.split_ascii_whitespace().map(str::parse).flatten();
    let mut output = String::new();

    let K: i32 = input.next().unwrap();

    // 가장 긴 가로변에 붙은 세로변 길이 차 = 작은 사각형 세로
    // 가장 긴 세로변에 붙은 가로 변 길이 차 = 작은 사각형 길이
    // 사각형 2개 넓이 차 * K = 답

    let mut vec: Vec<(i32, i32)> = Vec::new();

    for _ in 0..6 {
        let dir = input.next().unwrap();
        let len = input.next().unwrap();
        vec.push((dir, len));
    }

    // 가장 긴 변 길이, index
    let mut w : i32 = 0;
    let mut idx_w: i32 = 0;
    let mut h: i32 = 0;
    let mut idx_h:i32 = 0;

    for i in 0..6 {
        let dir = *&vec[i].0;
        let len = *&vec[i].1;

        if dir == 1 || dir == 2 {
            if w < len {
                w = len;
                idx_w = i as i32;
            }
        } else {
            if h < len {
                h = len;
                idx_h = i as i32;
            }
        }
    }

    let w_left: usize = ((idx_w - 1 + 6) % 6) as usize;
    let w_right: usize = ((idx_w + 1 + 6) % 6) as usize;
    let h_left: usize = ((idx_h - 1 + 6) % 6) as usize;
    let h_right: usize = ((idx_h + 1 + 6) % 6) as usize;
    let mut diff: (i32, i32) = (*&vec[w_left].1 - *&vec[w_right].1, *&vec[h_left].1 - *&vec[h_right].1);

    diff = (diff.0.abs(), diff.1.abs());

    let result = ((w * h) - (diff.0 * diff.1)) * K;
    println!("{result}");
}
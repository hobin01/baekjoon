use std::fmt::Write;
use std::io::{stdin, Read};
use std::cmp::max;

fn out(y: i32, x: i32, n: i32) -> bool {
    let result = y < 0 || x < 0 || y >= n || x >= n;
    result 
}

fn calc(v: &mut Vec<Vec<usize>>, y: i32, x: i32, n: i32) -> usize {
    let mut result: usize = 0;

    // up, down, left, right
    let nys = [y - 1, y + 1, y, y];
    let nxs = [x, x, x - 1, x + 1];

    for i in 0..4 {
        let ny = nys[i];
        let nx = nxs[i];

        if !out(ny, nx, n) {
            let cy: usize = y as usize;
            let cx: usize = x as usize;
            let ny: usize = ny as usize;
            let nx: usize = nx as usize;
            let nn: usize = n as usize;

            let tmp = v[cy][cx];
            v[cy][cx] = v[ny][nx];
            v[ny][nx] = tmp;

            // check row
            let mut cnt: usize = 1;
            for j in 0..(nn - 1) {
                if v[cy][j] == v[cy][j + 1] {
                    cnt += 1;
                } else {
                    cnt = 1;
                }
                result = max(result, cnt);
            }

            // check column
            cnt = 1;
            for j in 0..(nn - 1) {
                if v[j][cx] == v[j + 1][cx] {
                    cnt += 1;
                } else {
                    cnt = 1;
                }
                result = max(result, cnt);
            }

            // to origin
            let tmp = v[cy][cx];
            v[cy][cx] = v[ny][nx];
            v[ny][nx] = tmp;
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
    let n: i32 = N.parse().unwrap();

    // 빨간 C - 0, 파랑 P - 1, 초로 Z - 2, 노란 Y -3
    let mut vec: Vec<Vec<usize>> = Vec::new();
    for _ in 0..n {
        let s = input.next().unwrap();
        let mut tmp: Vec<usize> = Vec::new();

        for c in (&s).chars() {
            let num = match c {
                'C' => 0,
                'P' => 1,
                'Z' => 2,
                'Y' => 3,
                _ => 4,
            };

            tmp.push(num);
        }

        vec.push(tmp);
    }

    let mut result = 0;
    for i in 0..n {
        for j in 0..n {
            result = max(result, calc(&mut vec, i, j, n));
        }
    }

    writeln!(output, "{}", result).unwrap();
    print!("{}", output);

}
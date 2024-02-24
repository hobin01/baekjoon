use std::io::{stdin, Read};
use std::fmt::Write;
use std::collections::VecDeque;
use std::cmp::min;

// 다른 곳과 이어지지 않은 애들
// 바닥 or 다른 클러스터 닿일 때까지 떨어짐
// 모양은 안 바뀜
// 미네랄 부신 다음 bfs로 각 클러스터 재구성
// 맨 밑의 미네랄 기준으로 바닥에 없으면 
// 한 칸 씩 내려가면서 바닥 or 다른 클러스터 만날 때까지 내림
// 위에거 반복

// 좌우상하
const DX: &[i32] = &[-1, 1, 0, 0];
const DY: &[i32] = &[0, 0, -1, 1];

fn bfs((sy, sx): (i32, i32), map: &mut Vec<Vec<char>>, visited: &mut Vec<Vec<bool>>) -> Vec<(usize, usize)> {
    // bfs 탐색으로 얻은 클러스터 목록
    let mut res : Vec<(usize, usize)> = Vec::new();

    let r = map.len();
    let c = map[0].len();

    let mut queue: VecDeque<(i32, i32)> = VecDeque::new();
    queue.push_back((sy, sx));
    res.push((sy as usize, sx as usize));

    loop {
        if queue.is_empty() {
            break;
        }

        let y = queue.front().unwrap().0;
        let x = queue.front().unwrap().1;
        queue.pop_front();

        visited[y as usize][x as usize] = true;

        for i in 0..4 as usize {
            let ny = y + DY[i];
            let nx = x + DX[i];

            // 맵 벗어난 케이스
            if ny < 0 || nx < 0 {
                continue;
            }

            let ny = ny as usize;
            let nx = nx as usize;

            // 맵 벗어난 케이스
            if ny >= r || nx >= c {
                continue;
            }

            // 이미 방문함
            if visited[ny][nx] {
                continue;
            }

            // . 인 케이스
            if map[ny][nx] == '.' {
                visited[ny][nx] = true;
                continue;
            }

            // x이면서 방문 아직 안 한 나머지 경우
            queue.push_back((ny as i32, nx as i32));
            res.push((ny, nx));
            visited[ny][nx] = true;
        }        
    }

    res
}

fn clustering(map: &mut Vec<Vec<char>>) -> Vec<Vec<(usize, usize)>> {
    // res : 클러스터 목록 (ele : 각 미네랄 위치)
    let mut res : Vec<Vec<(usize, usize)>> = Vec::new();
    
    let r = map.len();
    let c = map[0].len();

    let mut visited: Vec<Vec<bool>> = vec![vec![false; c]; r];

    for y in (0..r).rev() {
        for x in (0..c).rev() {
            if map[y][x] == '.' || visited[y][x] {
                continue;
            }

            let cluster = bfs((y as i32, x as i32), map, &mut visited);
            res.push(cluster);
        }
    }

    res
}

fn game(map: &mut Vec<Vec<char>>, stick: usize, loc: usize) {
    // stick : 부서질 높이, loc : 왼, 오른 구분
    let r = map.len();
    let c = map[0].len();

    // stick 위치 미네랄 부시기 
    // 왼쪽 던지기
    if loc % 2 == 0 {
        for i in 0..c {
            if map[stick][i] == 'x' {
                map[stick][i] = '.';
                break;
            }
        }
    }
    // 오른쪽 던지기
    else {
        for i in (0..c).rev() {
            if map[stick][i] == 'x' {
                map[stick][i] = '.';
                break;
            }
        }
    }

    // 미네랄 부신 다음 클러스터 계산
    let clusters = clustering(map);

    for cluster in clusters.iter() {
        // 클러스터 첫 번째가 바닥에 있는 경우 
        if (*cluster)[0].0 == (r-1) {
            continue;
        }

        // 내려가야 하는 경우
        // 밑의 값이 . 인 애들 
        let mut minerals : Vec<(usize, usize)> = Vec::new();
        for mineral in cluster.iter() {
            let y = (*mineral).0;
            let x = (*mineral).1;

            // 이미 바닥에 붙은 경우
            if (y+1) >= r {
                continue;
            }

            // 떨어지는 경우
            if map[y+1][x] == '.' {
                minerals.push((y, x));
            }
        }

        // minerals에 있는 것 중 내려가는 최소값만큼 전부 내리기
        // 최대 100칸
        let mut cnt = 123 as usize;
        for mineral in minerals.iter() {
            let mut tmp = 1 as usize;
            let y = (*mineral).0;
            let x = (*mineral).1;
            loop {
                // 바닥까지 간 경우
                if (y + tmp) == (r-1){
                    cnt = min(cnt, tmp);
                    break;
                }

                // 다른 미네랄 만나는 경우 
                if map[y + tmp + 1][x] == 'x' && !cluster.contains(&(y + tmp + 1, x)) {
                    cnt = min(cnt, tmp);
                    break;
                }

                tmp += 1;
            }
        }

        // cnt만큼 전부 내리기 
        let tmp = cluster.clone();
        for pos in tmp.iter() {
            map[(*pos).0][(*pos).1] = '.';
        }
        for pos in cluster.iter() {
            map[(*pos).0 + cnt][(*pos).1] = 'x';
        }
    }
}

fn main() {

    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();
    let r = input.next().unwrap().parse::<usize>().unwrap();
    let _c = input.next().unwrap().parse::<usize>().unwrap();
    let mut map: Vec<Vec<char>> = vec![Vec::new(); r];
    for i in 0..r {
        let line = input.next().unwrap().parse::<String>().unwrap();
        for ch in line.chars() {
            map[i].push(ch);
        }
    }

    let t = input.next().unwrap().parse::<usize>().unwrap();
    let mut sticks : Vec<usize> = vec![0; t];
    for i in 0..t {
        let s = input.next().unwrap().parse::<usize>().unwrap();
        sticks[i] = r-s;
    }

    for (loc, stick) in sticks.iter().enumerate() {
        game(&mut map, *stick, loc);
    }

    for line in map.iter() {
        for ch in (*line).iter() {
            write!(output, "{}", *ch).unwrap();
        }
        writeln!(output, "").unwrap();
    }

    print!("{}", output);
}


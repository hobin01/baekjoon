use std::io::{stdin, Read};
use std::fmt::Write;
use std::collections::VecDeque;

// 처음 입력 순으로 위상 정렬용 그래프 만들기
// i < j => i -> j 로 연결 (< 는 순위 비교, 해당되는 모든 노드 연결)
// 새로 받은 입력에 대해서 기존 엣지와의 연결 관계 끊고 새로 연결
// IMPOSSIBLE : 사이클 발생 시

fn init_graph(last_year: &Vec<usize>, relatives: &Vec<(usize, usize)>, in_degree: &mut Vec<usize>, edges: &mut Vec<Vec<usize>>, last_grades: &Vec<usize>) {
    let n: usize = last_year.len();

    in_degree.resize(n+1, 0usize);
    edges.resize(n+1, Vec::new());

    for i in 0..(n-1) {
        for j in (i+1)..n {
            let num = last_year[j];
            in_degree[num] += 1;
            edges[last_year[i]].push(num);
        }
    }

    // 새 입력 처리
    for val in relatives.iter() {
        let num1 = (*val).0;
        let num2 = (*val).1;
        
        let gr1 = last_grades[num1];
        let gr2 = last_grades[num2];

        if gr1 < gr2 {
            in_degree[num2] -= 1;
            in_degree[num1] += 1;

            let idx_num2 = edges[num1].iter().position(|x| *x == num2).unwrap();
            edges[num1].remove(idx_num2);
            edges[num2].push(num1)
        } else {
            in_degree[num1] -= 1;
            in_degree[num2] += 1;

            let idx_num1 = edges[num2].iter().position(|x| *x == num1).unwrap();
            edges[num2].remove(idx_num1);
            edges[num1].push(num2);
        }
    }
}

fn dfs(node: usize, edges: &Vec<Vec<usize>>, visited: &mut Vec<usize>) -> bool {
    // visited : i번 노드 방문 여부
    // 0 : 아직 체크 X, 1 : 사이클 있음, 2 : 사이클 없음 (다 돌아봄)

    // 방문한 곳 다시 옴 : 사이클
    if visited[node] == 1 {
        return true;
    }
    if visited[node] == 2 {
        return false;
    }

    visited[node] = 1;
    for next_node in edges[node].iter() {
        if dfs(*next_node, edges, visited) {
            return true;
        }
    }

    visited[node] = 2;
    false
}

fn has_cycle(edges: &Vec<Vec<usize>>) -> bool {
    let n = edges.len();
    let mut visited = vec![0usize; n];

    // 0번은 제외
    for i in 1..n {
        if visited[i] == 0 && dfs(i, edges, &mut visited) {
            return true;
        }
    }

    false
}

fn topological_sort(in_degree: &mut Vec<usize>, edges: &Vec<Vec<usize>>, this_year: &mut Vec<usize>) {
    let mut deq: VecDeque<usize> = VecDeque::new();

    for (idx, deg) in in_degree.iter().enumerate() {
        // 0은 제외
        if idx == 0 {
            continue;
        }
        if *deg == 0 {
            deq.push_back(idx);
        }
    }

    loop {
        if deq.is_empty() {
            break;
        }

        let node = deq.pop_front().unwrap();
        this_year.push(node);

        for next_node in edges[node].iter() {
            in_degree[*next_node] -= 1;

            // 작년 순위와 비교 후 정렬하여 큐에 넣기
            if in_degree[*next_node] == 0 {
                deq.push_back(*next_node);
            }
        }
    }
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();

    let t = input.next().unwrap().parse::<usize>().unwrap();
    
    // 입력으로 받는 값들
    let mut last_year: Vec<usize> = Vec::new();
    let mut relatives: Vec<(usize, usize)> = Vec::new();

    // 처리해줄 값들
    let mut in_degree: Vec<usize> = Vec::new();
    let mut edges: Vec<Vec<usize>> = Vec::new();

    // 결과 값
    let mut this_year: Vec<usize> = Vec::new();

    // index에 등수 저장 
    // last_grades[5] = 5번의 등수
    let mut last_grades: Vec<usize> = Vec::new();

    for _ in 0..t {

        last_year.clear();
        in_degree.clear();
        edges.clear();
        relatives.clear();
        this_year.clear();
        last_grades.clear();

        let n = input.next().unwrap().parse::<usize>().unwrap();
        for _ in 0..n {
            let num = input.next().unwrap().parse::<usize>().unwrap();
            last_year.push(num);
        }

        let m = input.next().unwrap().parse::<usize>().unwrap();

        // m = 0 이면 동일한 값
        if m == 0 {
            for val in last_year.iter() {
                write!(output, "{} ", *val).unwrap();
            }
            writeln!(output, "").unwrap();
            continue;
        }

        for _ in 0..m {
            let num1 = input.next().unwrap().parse::<usize>().unwrap();
            let num2 = input.next().unwrap().parse::<usize>().unwrap();
            relatives.push((num1, num2));
        }

        last_grades.resize(n+1, 0);
        for (idx, val) in last_year.iter().enumerate() {
            last_grades[*val] = idx;
        }

        // 그래프 생성
        init_graph(&last_year, &relatives, &mut in_degree, &mut edges, &last_grades);

        // 사이클 체크
        let chk = has_cycle(&edges);
        if chk {
            writeln!(output, "IMPOSSIBLE").unwrap();
            continue;
        }

        // 위상 정렬
        topological_sort(&mut in_degree, &edges, &mut this_year);

        for i in 0..n {
            write!(output, "{} ", this_year[i]).unwrap();
        }
        writeln!(output, "").unwrap();
    }

    print!("{}", output);
}

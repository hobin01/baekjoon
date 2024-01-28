use std::io::{stdin, Read};
use std::fmt::Write;
use std::collections::{BinaryHeap, HashMap};
use std::cmp::Reverse;

// n : 노드 개수, start : 시작점, graph : 그래프 정보
// return : 거리 정보 
fn dijkstra(n: usize, start: usize, graph: HashMap<usize, Vec<(usize, usize)>>) -> Vec<usize> {
    // 거리 초기화
    let mut dist: Vec<usize> = Vec::new();
    let mut visited: Vec<bool> = Vec::new();
    for _ in 0..n {
        dist.push(usize::MAX);
        visited.push(false);
    }

    // 우선순위 큐 : Reverse로 min heap 으로 동작시킴
    // pq 원소 : (거리, 노드)
    let mut pq: BinaryHeap<Reverse<(usize, usize)>> = BinaryHeap::new();
    pq.push(Reverse((0usize, start)));
    visited[start] = true;

    // 우선순위 큐 + 다익스트라 
    while !pq.is_empty() {
        let ele = pq.pop().unwrap().0;
        let cost = ele.0;
        let node = ele.1;

        if let Some(v) = graph.get(&node) {
            for ele in v.iter() {
                let next_node = (*ele).0;
                let next_cost = cost + (*ele).1;

                if visited[next_node] {
                    continue;
                }

                if next_cost < dist[next_node] {
                    dist[next_node] = next_cost;
                    pq.push(Reverse((next_cost, next_node)));
                }
            }
        }
    }

    dist
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();
    
    let n = input.next().unwrap().parse::<usize>().unwrap();
    let m = input.next().unwrap().parse::<usize>().unwrap();
    let k = input.next().unwrap().parse::<usize>().unwrap();
    let x = input.next().unwrap().parse::<usize>().unwrap() - 1;

    // 문제 상 거리 항상 1
    let mut graph: HashMap<usize, Vec<(usize, usize)>> = HashMap::new();
    for _ in 0..m {
        let a = input.next().unwrap().parse::<usize>().unwrap() - 1;
        let b = input.next().unwrap().parse::<usize>().unwrap() - 1;

        if !graph.contains_key(&a) {
            graph.insert(a, vec![]);
        } 
        if let Some(v) = graph.get_mut(&a) {
            v.push((b, 1usize));
        }
    }

    // 계산 
    let dist = dijkstra(n, x, graph);
    let mut res: Vec<usize> = Vec::new();

    for i in 0..dist.len() {
        if dist[i] == k {
            res.push(i+1);
        }
    }

    if res.len() == 0 {
        writeln!(output, "{}", -1).unwrap();
    } else {
        for r in res.iter() {
            writeln!(output, "{}", *r).unwrap();
        }
    }

    print!("{}", output);
}

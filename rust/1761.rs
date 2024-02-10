use std::io::{stdin, Read};
use std::fmt::Write;
use std::mem;

// ref : https://everenew.tistory.com/95

const HEIGHT: usize = 20;
const MAX_NODES: usize = 40001;

fn find_parent(
    parent: usize, node: usize, depth: usize, dist: i32, 
    depth_vec: &mut Vec<usize>, 
    parent_vec: &mut Vec<Vec<usize>>, 
    distance_vec: &mut Vec<Vec<i32>>,
    tree: &Vec<Vec<(usize, i32)>>
) 
{
    depth_vec[node] = depth;
    parent_vec[node][0] = parent;
    distance_vec[node][0] = dist;

    for child_node in tree[node].iter() {
        let child = (*child_node).0;
        let d = (*child_node).1;
        if child != parent {
            find_parent(node, child, depth + 1, d, depth_vec, parent_vec, distance_vec, tree);
        }
    }
}

fn dist_nodes(
    node1: &mut usize, node2: &mut usize,
    depth_vec: &Vec<usize>, 
    parent_vec: &Vec<Vec<usize>>, 
    distance_vec: &Vec<Vec<i32>>
) -> i32 {
    let mut res: i32 = 0;

    let depth_node1 = depth_vec[*node1];
    let depth_node2 = depth_vec[*node2];
    if depth_node1 != depth_node2 {
        if depth_node1 < depth_node2 {
            mem::swap(node1, node2);
        }

        let mut diff: usize = depth_vec[*node1] - depth_vec[*node2];
        let mut idx :usize = 0;
        loop {
            if diff == 0 {
                break;
            }

            if (diff % 2) == 1 {
                res += distance_vec[*node1][idx];
                *node1 = parent_vec[*node1][idx];
            }

            idx += 1;
            diff /= 2;
        }
    }

    if *node1 != *node2 {
        for k in (0..HEIGHT).rev() {
            if parent_vec[*node1][k] != 0 {
                if parent_vec[*node1][k] != parent_vec[*node2][k] {
                    res += distance_vec[*node1][k];
                    res += distance_vec[*node2][k];
                    *node1 = parent_vec[*node1][k];
                    *node2 = parent_vec[*node2][k];
                }
            }
        }

        res += distance_vec[*node1][0];
        res += distance_vec[*node2][0];
    }

    res 
}

fn main() {
    let mut input = String::new();
    let mut output = String::new();
    stdin().read_to_string(&mut input).unwrap();

    let mut input = input.split_ascii_whitespace();

    let n = input.next().unwrap().parse::<usize>().unwrap();

    let mut depth_vec: Vec<usize> = vec![0usize; MAX_NODES];
    let mut parent_vec: Vec<Vec<usize>> = vec![vec![0usize; HEIGHT]; MAX_NODES];
    let mut distance_vec: Vec<Vec<i32>> = vec![vec![0; HEIGHT]; MAX_NODES];
    let mut tree: Vec<Vec<(usize, i32)>> = vec![Vec::new(); MAX_NODES];

    for _ in 0..(n-1) {
        let node1 = input.next().unwrap().parse::<usize>().unwrap();
        let node2 = input.next().unwrap().parse::<usize>().unwrap();
        let dist = input.next().unwrap().parse::<i32>().unwrap();

        tree[node1].push((node2, dist));
        tree[node2].push((node1, dist));
    }

    find_parent(0, 1, 0, 0, &mut depth_vec, &mut parent_vec, &mut distance_vec, &tree);

    for k in 1..HEIGHT {
        for idx in 2..(n+1) {
            if parent_vec[idx][k-1] != 0 {
                parent_vec[idx][k] = parent_vec[parent_vec[idx][k-1]][k-1];
                distance_vec[idx][k] = distance_vec[idx][k-1] + distance_vec[parent_vec[idx][k-1]][k-1];
            }
        }
    }

    let m = input.next().unwrap().parse::<usize>().unwrap();
    for _ in 0..m {
        let mut node1 = input.next().unwrap().parse::<usize>().unwrap();
        let mut node2 = input.next().unwrap().parse::<usize>().unwrap();
        let res = dist_nodes(&mut node1, &mut node2, &depth_vec, &parent_vec, &distance_vec);

        writeln!(output, "{}", res).unwrap();
    }

    print!("{}", output);
}

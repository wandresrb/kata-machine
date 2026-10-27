use std::collections::VecDeque;

use crate::types::WeightedAdjacencyMatrix;

pub fn bfs(graph: &WeightedAdjacencyMatrix, source: usize, needle: usize) -> Option<Vec<usize>> {
    let mut seen = vec![false; graph.len()];
    let mut prev: Vec<Option<usize>> = vec![None; graph.len()];
    let mut queue = VecDeque::from([source]);
    seen[source] = true;

    while let Some(cur) = queue.pop_front() {
        if cur == needle {
            break;
        }
        for (to, &weight) in graph[cur].iter().enumerate() {
            if weight != 0 && !seen[to] {
                seen[to] = true;
                prev[to] = Some(cur);
                queue.push_back(to);
            }
        }
    }

    if !seen[needle] {
        return None;
    }
    let mut path = vec![needle];
    let mut cur = needle;
    while let Some(p) = prev[cur] {
        path.push(p);
        cur = p;
    }
    path.reverse();
    Some(path)
}

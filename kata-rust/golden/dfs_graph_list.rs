use crate::types::WeightedAdjacencyList;

pub fn dfs(graph: &WeightedAdjacencyList, source: usize, needle: usize) -> Option<Vec<usize>> {
    let mut seen = vec![false; graph.len()];
    let mut path = Vec::new();
    walk(graph, source, needle, &mut seen, &mut path).then_some(path)
}

fn walk(
    graph: &WeightedAdjacencyList,
    cur: usize,
    needle: usize,
    seen: &mut [bool],
    path: &mut Vec<usize>,
) -> bool {
    if seen[cur] {
        return false;
    }
    seen[cur] = true;
    path.push(cur);
    if cur == needle {
        return true;
    }
    for edge in &graph[cur] {
        if walk(graph, edge.to, needle, seen, path) {
            return true;
        }
    }
    path.pop();
    false
}

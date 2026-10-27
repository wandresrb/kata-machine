mod common;

use kata::code::bfs_graph_matrix::bfs;

#[test]
fn bfs_graph_matrix() {
    let graph = common::matrix2();
    assert_eq!(bfs(&graph, 0, 6), Some(vec![0, 1, 4, 5, 6]));
    assert_eq!(bfs(&graph, 6, 0), None);
}

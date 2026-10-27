mod common;

use kata::code::bfs_graph_list::bfs;

#[test]
fn bfs_graph_list() {
    let graph = common::list2();
    assert_eq!(bfs(&graph, 0, 6), Some(vec![0, 1, 4, 5, 6]));
    assert_eq!(bfs(&graph, 6, 0), None);
}

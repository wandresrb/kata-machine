mod common;

use kata::code::dfs_graph_list::dfs;

#[test]
fn dfs_graph_list() {
    let graph = common::list2();
    assert_eq!(dfs(&graph, 0, 6), Some(vec![0, 1, 4, 5, 6]));
    assert_eq!(dfs(&graph, 6, 0), None);
}

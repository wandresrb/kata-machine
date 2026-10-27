mod common;

use kata::code::dijkstra_list::dijkstra_list;

#[test]
fn dijkstra_list_test() {
    assert_eq!(dijkstra_list(0, 6, &common::list1()), vec![0, 1, 4, 5, 6]);
}

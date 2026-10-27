mod common;

use kata::code::bt_bfs::bfs;

#[test]
fn bt_bfs() {
    let tree = common::tree();
    assert!(bfs(&tree, 45));
    assert!(bfs(&tree, 7));
    assert!(!bfs(&tree, 69));
}

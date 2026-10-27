mod common;

use kata::code::dfs_on_bst::dfs;

#[test]
fn dfs_on_bst() {
    let tree = common::tree();
    assert!(dfs(&tree, 45));
    assert!(dfs(&tree, 7));
    assert!(!dfs(&tree, 69));
}

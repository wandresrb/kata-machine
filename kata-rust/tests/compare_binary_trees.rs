mod common;

use kata::code::compare_binary_trees::compare;

#[test]
fn compare_binary_trees() {
    let tree = common::tree();
    let tree2 = common::tree2();
    assert!(compare(Some(&tree), Some(&tree)));
    assert!(!compare(Some(&tree), Some(&tree2)));
}

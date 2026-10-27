use std::cmp::Ordering;

use crate::types::BinaryNode;

pub fn dfs(head: &BinaryNode<i32>, needle: i32) -> bool {
    let mut cur = Some(head);
    while let Some(node) = cur {
        cur = match needle.cmp(&node.value) {
            Ordering::Equal => return true,
            Ordering::Less => node.left.as_deref(),
            Ordering::Greater => node.right.as_deref(),
        };
    }
    false
}

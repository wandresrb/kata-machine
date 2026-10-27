use std::collections::VecDeque;

use crate::types::BinaryNode;

pub fn bfs(head: &BinaryNode<i32>, needle: i32) -> bool {
    let mut queue = VecDeque::from([head]);
    while let Some(node) = queue.pop_front() {
        if node.value == needle {
            return true;
        }
        queue.extend(node.left.as_deref());
        queue.extend(node.right.as_deref());
    }
    false
}

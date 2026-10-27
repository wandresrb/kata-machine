use crate::types::BinaryNode;

pub fn pre_order_search(head: &BinaryNode<i32>) -> Vec<i32> {
    let mut path = Vec::new();
    walk(Some(head), &mut path);
    path
}

fn walk(node: Option<&BinaryNode<i32>>, path: &mut Vec<i32>) {
    let Some(n) = node else { return };
    path.push(n.value);
    walk(n.left.as_deref(), path);
    walk(n.right.as_deref(), path);
}

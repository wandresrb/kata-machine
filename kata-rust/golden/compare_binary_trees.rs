use crate::types::BinaryNode;

pub fn compare(a: Option<&BinaryNode<i32>>, b: Option<&BinaryNode<i32>>) -> bool {
    match (a, b) {
        (None, None) => true,
        (Some(a), Some(b)) => {
            a.value == b.value
                && compare(a.left.as_deref(), b.left.as_deref())
                && compare(a.right.as_deref(), b.right.as_deref())
        }
        _ => false,
    }
}

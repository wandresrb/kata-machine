mod common;

use kata::code::singly_linked_list::SinglyLinkedList;

#[test]
fn singly_linked_list() {
    let mut list = SinglyLinkedList::new();
    common::test_list(&mut list);
}

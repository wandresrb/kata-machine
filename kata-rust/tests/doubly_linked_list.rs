mod common;

use kata::code::doubly_linked_list::DoublyLinkedList;

#[test]
fn doubly_linked_list() {
    let mut list = DoublyLinkedList::new();
    common::test_list(&mut list);
}

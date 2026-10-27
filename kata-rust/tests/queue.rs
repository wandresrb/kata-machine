use kata::code::queue::Queue;

#[test]
fn queue() {
    let mut list = Queue::new();

    list.enqueue(5);
    list.enqueue(7);
    list.enqueue(9);

    assert_eq!(list.deque(), Some(5));
    assert_eq!(list.len(), 2);

    list.enqueue(11);
    assert_eq!(list.deque(), Some(7));
    assert_eq!(list.deque(), Some(9));
    assert_eq!(list.peek(), Some(11));
    assert_eq!(list.deque(), Some(11));
    assert_eq!(list.deque(), None);
    assert_eq!(list.len(), 0);

    // just wanted to make sure that I could not blow up myself when i remove
    // everything
    list.enqueue(69);
    assert_eq!(list.peek(), Some(69));
    assert_eq!(list.len(), 1);
}

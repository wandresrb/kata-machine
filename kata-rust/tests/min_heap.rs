use kata::code::min_heap::MinHeap;

#[test]
fn min_heap() {
    let mut heap = MinHeap::new();

    assert_eq!(heap.len(), 0);

    heap.insert(5);
    heap.insert(3);
    heap.insert(69);
    heap.insert(420);
    heap.insert(4);
    heap.insert(1);
    heap.insert(8);
    heap.insert(7);

    assert_eq!(heap.len(), 8);
    assert_eq!(heap.delete(), Some(1));
    assert_eq!(heap.delete(), Some(3));
    assert_eq!(heap.delete(), Some(4));
    assert_eq!(heap.delete(), Some(5));
    assert_eq!(heap.len(), 4);
    assert_eq!(heap.delete(), Some(7));
    assert_eq!(heap.delete(), Some(8));
    assert_eq!(heap.delete(), Some(69));
    assert_eq!(heap.delete(), Some(420));
    assert_eq!(heap.len(), 0);
}

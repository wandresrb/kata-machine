use kata::code::stack::Stack;

#[test]
fn stack() {
    let mut list = Stack::new();

    list.push(5);
    list.push(7);
    list.push(9);

    assert_eq!(list.pop(), Some(9));
    assert_eq!(list.len(), 2);

    list.push(11);
    assert_eq!(list.pop(), Some(11));
    assert_eq!(list.pop(), Some(7));
    assert_eq!(list.peek(), Some(5));
    assert_eq!(list.pop(), Some(5));
    assert_eq!(list.pop(), None);

    // just wanted to make sure that I could not blow up myself when i remove
    // everything
    list.push(69);
    assert_eq!(list.peek(), Some(69));
    assert_eq!(list.len(), 1);
}

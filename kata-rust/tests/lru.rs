use kata::code::lru::Lru;

#[test]
fn lru() {
    let mut lru: Lru<String, i32> = Lru::new(3);
    let key = String::from;

    assert_eq!(lru.get(&key("foo")), None);
    lru.update(key("foo"), 69);
    assert_eq!(lru.get(&key("foo")), Some(69));

    lru.update(key("bar"), 420);
    assert_eq!(lru.get(&key("bar")), Some(420));

    lru.update(key("baz"), 1337);
    assert_eq!(lru.get(&key("baz")), Some(1337));

    lru.update(key("ball"), 69420);
    assert_eq!(lru.get(&key("ball")), Some(69420));
    assert_eq!(lru.get(&key("foo")), None);
    assert_eq!(lru.get(&key("bar")), Some(420));
    lru.update(key("foo"), 69);
    assert_eq!(lru.get(&key("bar")), Some(420));
    assert_eq!(lru.get(&key("foo")), Some(69));

    // shouldn't of been deleted, but since bar was get'd, bar was added to the
    // front of the list, so baz became the end
    assert_eq!(lru.get(&key("baz")), None);
}

use kata::code::map::Map;

#[test]
fn map() {
    let mut map: Map<String, i32> = Map::new();
    let key = String::from;

    map.set(key("foo"), 55);
    assert_eq!(map.size(), 1);
    map.set(key("fool"), 75);
    assert_eq!(map.size(), 2);
    map.set(key("foolish"), 105);
    assert_eq!(map.size(), 3);
    map.set(key("bar"), 69);
    assert_eq!(map.size(), 4);

    assert_eq!(map.get(&key("bar")), Some(69));
    assert_eq!(map.get(&key("blaz")), None);

    map.delete(&key("barblabr"));
    assert_eq!(map.size(), 4);

    map.delete(&key("bar"));
    assert_eq!(map.size(), 3);
    assert_eq!(map.get(&key("bar")), None);
}

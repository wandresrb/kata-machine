use kata::code::linear_search_list::linear_search;

#[test]
fn linear_search_list() {
    let foo = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
    assert!(linear_search(&foo, 69));
    assert!(!linear_search(&foo, 1336));
    assert!(linear_search(&foo, 69420));
    assert!(!linear_search(&foo, 69421));
    assert!(linear_search(&foo, 1));
    assert!(!linear_search(&foo, 0));
}

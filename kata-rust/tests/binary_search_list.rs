use kata::code::binary_search_list::bs_list;

#[test]
fn binary_search_list() {
    let foo = [1, 3, 4, 69, 71, 81, 90, 99, 420, 1337, 69420];
    assert!(bs_list(&foo, 69));
    assert!(!bs_list(&foo, 1336));
    assert!(bs_list(&foo, 69420));
    assert!(!bs_list(&foo, 69421));
    assert!(bs_list(&foo, 1));
    assert!(!bs_list(&foo, 0));
}

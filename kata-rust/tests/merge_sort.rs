use kata::code::merge_sort::merge_sort;

#[test]
fn merge_sort_test() {
    let mut arr = [9, 3, 7, 4, 69, 420, 42];
    merge_sort(&mut arr);
    assert_eq!(arr, [3, 4, 7, 9, 42, 69, 420]);
}

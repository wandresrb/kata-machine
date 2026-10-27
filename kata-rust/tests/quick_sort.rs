use kata::code::quick_sort::quick_sort;

#[test]
fn quick_sort_test() {
    let mut arr = [9, 3, 7, 4, 69, 420, 42];
    quick_sort(&mut arr);
    assert_eq!(arr, [3, 4, 7, 9, 42, 69, 420]);
}

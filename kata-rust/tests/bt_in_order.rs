mod common;

use kata::code::bt_in_order::in_order_search;

#[test]
fn bt_in_order() {
    assert_eq!(
        in_order_search(&common::tree()),
        vec![5, 7, 10, 15, 20, 29, 30, 45, 50, 100]
    );
}

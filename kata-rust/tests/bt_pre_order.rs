mod common;

use kata::code::bt_pre_order::pre_order_search;

#[test]
fn bt_pre_order() {
    assert_eq!(
        pre_order_search(&common::tree()),
        vec![20, 10, 5, 7, 15, 50, 30, 29, 45, 100]
    );
}

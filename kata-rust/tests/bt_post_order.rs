mod common;

use kata::code::bt_post_order::post_order_search;

#[test]
fn bt_post_order() {
    assert_eq!(
        post_order_search(&common::tree()),
        vec![7, 5, 15, 10, 29, 45, 30, 100, 50, 20]
    );
}

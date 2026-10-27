mod common;

use kata::code::array_list::ArrayList;

#[test]
fn array_list() {
    let mut list = ArrayList::with_capacity(3);
    common::test_list(&mut list);
}

use std::time::{SystemTime, UNIX_EPOCH};

use kata::code::two_crystal_balls::two_crystal_balls;

/// Pseudo-random index in `[0, 10000)` (no crates allowed, so seed from the clock).
fn random_idx() -> usize {
    let nanos = SystemTime::now()
        .duration_since(UNIX_EPOCH)
        .expect("clock before 1970")
        .subsec_nanos();
    nanos as usize % 10_000
}

#[test]
fn two_crystal_balls_test() {
    let idx = random_idx();
    let mut data = vec![false; 10_000];
    data[idx..].fill(true);

    assert_eq!(two_crystal_balls(&data), Some(idx), "idx = {idx}");
    assert_eq!(two_crystal_balls(&vec![false; 821]), None);
}

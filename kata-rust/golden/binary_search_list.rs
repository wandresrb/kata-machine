use std::cmp::Ordering;

pub fn bs_list(haystack: &[i32], needle: i32) -> bool {
    let (mut lo, mut hi) = (0, haystack.len());
    while lo < hi {
        let mid = lo + (hi - lo) / 2;
        match haystack[mid].cmp(&needle) {
            Ordering::Equal => return true,
            Ordering::Less => lo = mid + 1,
            Ordering::Greater => hi = mid,
        }
    }
    false
}
